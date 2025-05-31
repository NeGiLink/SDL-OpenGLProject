#include "BaseScene.h"
#include "GameFunctions.h"

BaseScene::BaseScene(GameWinMain* winMain)
	: mWinMain(winMain)
	, mAudioSystem(nullptr)
	, mPhysWorld(nullptr)
	, mUpdatingActors(false)
	, mFixed_Delta_Time(0.02f)
	, mPlayer(nullptr)
	, mMainCamera(nullptr)
	, mHUD(nullptr)
	, mFixedTimeAccumulator(0.0f)
{
}

void BaseScene::Shutdown()
{
	InputSystem::Shutdown();
}

bool BaseScene::Initialize()
{
	if (!InputSystem::Initialize())
	{
		SDL_Log("Failed to initialize input system");
		return false;
	}

	// Audio Systemを作成
	mAudioSystem = new AudioSystem(this);
	if (!mAudioSystem->Initialize())
	{
		SDL_Log("Failed to initialize audio system");
		mAudioSystem->Shutdown();
		delete mAudioSystem;
		mAudioSystem = nullptr;
		return false;
	}

	// Physics Worldを作成
	mPhysWorld = new PhysWorld(this);
	return true;
}

bool BaseScene::InputUpdate()
{
	InputSystem::PrepareForUpdate();

	InputSystem::Update();

	return true;
}

bool BaseScene::FixedUpdate()
{
	float deltaTime = Time::gDeltaTime;
	mFixedTimeAccumulator += deltaTime;

	// 複数回 FixedUpdate が必要な場合に備える
	while (mFixedTimeAccumulator >= mFixed_Delta_Time)
	{
		//Rigidbody などの物理処理をここで呼ぶ
		
		for (auto actor : mActors)
		{
			actor->FixedUpdate(Time::gDeltaTime);
		}

		mPhysWorld->SweepAndPruneXYZ();

		mFixedTimeAccumulator -= mFixed_Delta_Time;
	}

	return true;
}

bool BaseScene::Update()
{
	//特定のシーンに読み込まれたオブジェクトやコンポーネントを
	// まとめて処理する部分
	if (GameStateClass::mGameState == GamePlay)
	{
		// Update all actors
		mUpdatingActors = true;
		for (auto actor : mActors)
		{
			actor->Update(Time::gDeltaTime);
		}
		mUpdatingActors = false;

		// 保留中のアクターをmActorsに移動します
		for (auto pending : mPendingActors)
		{
			pending->ComputeWorldTransform(NULL);
			mActors.emplace_back(pending);
		}
		mPendingActors.clear();

		// Add any dead actors to a temp vector
		vector<ActorObject*> deadActors;
		for (auto actor : mActors)
		{
			if (actor->GetState() == ActorObject::EDead)
			{
				deadActors.emplace_back(actor);
			}
		}

		// Delete dead actors (which removes them from mActors)
		for (auto actor : deadActors)
		{
			delete actor;
		}
	}

	// Update audio system
	mAudioSystem->Update(Time::gDeltaTime);

	// Update UI screens
	for (auto ui : mUIStack)
	{
		if (ui->GetState() == Canvas::EActive)
		{
			ui->Update(Time::gDeltaTime);
		}
	}
	for (auto image : mImageStack)
	{
		if (image->GetState() == Image::EActive)
		{
			image->Update(Time::gDeltaTime);
		}
	}

	// Delete any UIScreens that are closed
	auto iter = mUIStack.begin();
	while (iter != mUIStack.end())
	{
		if ((*iter)->GetState() == Canvas::EDestroy)
		{
			delete* iter;
			iter = mUIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	auto image = mImageStack.begin();
	while (image != mImageStack.end())
	{
		if ((*image)->GetState() == Image::EDestroy)
		{
			delete* image;
			image = mImageStack.erase(image);
		}
		else
		{
			++image;
		}
	}

	return true;
}

void BaseScene::HandleKeyPress(int key)
{
}

void BaseScene::AddActor(ActorObject* actor)
{
	// If we're updating actors, need to add to pending
	if (mUpdatingActors)
	{
		mPendingActors.emplace_back(actor);
	}
	else
	{
		mActors.emplace_back(actor);
	}
}

void BaseScene::RemoveActor(ActorObject* actor)
{
	// Is it in pending actors?
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// Is it in actors?
	iter = std::find(mActors.begin(), mActors.end(), actor);
	if (iter != mActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

Font* BaseScene::GetFont(const string& fileName)
{
	string filePath = FontFile::FontFilePath + fileName;
	auto iter = mFonts.find(filePath);
	if (iter != mFonts.end())
	{
		return iter->second;
	}
	else
	{
		Font* font = new Font();
		if (font->Load(filePath))
		{
			mFonts.emplace(filePath, font);
		}
		else
		{
			font->Unload();
			delete font;
			font = nullptr;
		}
		return font;
	}
}

void BaseScene::LoadText(const string& fileName)
{
	// Clear the existing map, if already loaded
	mText.clear();
	// Try to open the file
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		SDL_Log("Text file %s not found", fileName.c_str());
		return;
	}
	// Read the entire file to a string stream
	stringstream fileStream;
	fileStream << file.rdbuf();
	string contents = fileStream.str();
	// Open this file in rapidJSON
	rapidjson::StringStream jsonStr(contents.c_str());
	rapidjson::Document doc;
	doc.ParseStream(jsonStr);
	if (!doc.IsObject())
	{
		SDL_Log("Text file %s is not valid JSON", fileName.c_str());
		return;
	}
	// Parse the text map
	const rapidjson::Value& actions = doc["TextMap"];
	for (rapidjson::Value::ConstMemberIterator itr = actions.MemberBegin();
		itr != actions.MemberEnd(); ++itr)
	{
		if (itr->name.IsString() && itr->value.IsString())
		{
			mText.emplace(itr->name.GetString(),
				itr->value.GetString());
		}
	}
}

const string& BaseScene::GetText(const string& key)
{
	static string errorMsg("**KEY NOT FOUND**");
	// Find this text in the map, if it exists
	auto iter = mText.find(key);
	if (iter != mText.end())
	{
		return iter->second;
	}
	else
	{
		return errorMsg;
	}
}

Skeleton* BaseScene::GetSkeleton(const string& fileName)
{
	string file = Model::ModelPath + fileName;
	auto iter = mSkeletons.find(file);
	//すでにあるならそれを使う
	if (iter != mSkeletons.end())
	{
		return iter->second;
	}
	//新しく読み込み
	else
	{
		Skeleton* sk = new Skeleton();
		if (sk->LoadFromSkeletonBin(file))
		{
			mSkeletons.emplace(file, sk);
		}
		else if (sk->Load(file))
		{
			mSkeletons.emplace(file, sk);
		}
		else
		{
			delete sk;
			sk = nullptr;
		}
		return sk;
	}
	//読み込み失敗
	return nullptr;
}

Animator* BaseScene::GetAnimator(const string& fileName, Animator* animator)
{
	if (animator == nullptr)
	{
		Debug::ErrorLog("The project is ending because there are no animator.");
		return nullptr;
	}

	auto iter = mAnimators.find(fileName);
	if (iter != mAnimators.end())
	{
		return iter->second;
	}
	else
	{
		mAnimators.emplace(fileName, animator);
		return animator;
	}
}

void BaseScene::PushUI(Canvas* screen)
{
	mUIStack.emplace_back(screen);
}

void BaseScene::PushImage(Image* screen)
{
	mImageStack.emplace_back(screen);
}
void BaseScene::RemoveImage(Image* screen)
{
	// Is it in actors?
	auto iter = std::find(mImageStack.begin(), mImageStack.end(), screen);
	if (iter != mImageStack.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mImageStack.end() - 1);
		mImageStack.pop_back();
	}
}

void BaseScene::UnloadData()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!mActors.empty())
	{
		delete mActors.back();
	}

	// Clear the UI stack
	while (!mUIStack.empty())
	{
		delete mUIStack.back();
		mUIStack.pop_back();
	}

	while (!mImageStack.empty())
	{
		delete mImageStack.back();
		mImageStack.pop_back();
	}

	// Unload fonts
	for (auto& f : mFonts)
	{
		if (f.second)
		{
			f.second->Unload();
			delete f.second;
			f.second = nullptr;
		}
	}
	mFonts.clear();

	// Unload skeletons
	for (auto s : mSkeletons)
	{
		if (s.second) 
		{
			delete s.second;
			s.second = nullptr;
		}
	}
	mSkeletons.clear();

	// Unload animators
	for (auto a : mAnimators) 
	{
		if (a.second)
		{

			delete a.second;
		}
	}
	mAnimators.clear();

	delete mPhysWorld;
	if (mAudioSystem)
	{
		mAudioSystem->Shutdown();
	}
}
