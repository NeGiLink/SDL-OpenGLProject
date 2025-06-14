#include "Renderer.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "VertexArray.h"
#include "SpriteComponent.h"
#include "LineRenderer.h"
#include "MeshRenderer.h"
#include "Canvas.h"
#include "Image.h"
#include "WinMain.h"
#include "BaseScene.h"
#include "GameApp.h"
#include <GL/glew.h>
#include "SkeletalMeshRenderer.h"
#include "GBuffer.h"
#include "PointLightComponent.h"



Renderer::Renderer(GameWinMain* game)
	: mNowScene(nullptr)
	, mSpriteShader(nullptr)
	, mMeshShader(nullptr)
	, mSkinnedShader(nullptr)
	, mGBuffer(nullptr)
	, mGGlobalShader(nullptr)
	, mGPointLightShader(nullptr)
	, mContext(nullptr)
	, mFanSpriteVerts(nullptr)
	, mPointLightMesh(nullptr)
	, mSpriteVerts(nullptr)
	, mWindow(nullptr)
{
}

Renderer::~Renderer()
{
}

bool Renderer::Initialize(float screenWidth, float screenHeight)
{

	// OpenGLの属性を設定する
	// コアOpenGLプロファイルを使用
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// バージョン3.3を指定
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// RGBAチャネルごとに8ビットのカラーバッファをリクエスト
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	// ダブルバッファリングを有効にする
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// OpenGLにハードウェアアクセラレーションを使用
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	mWindow = SDL_CreateWindow("SDL&OpenGLProject",static_cast<int>(WindowRenderProperty::GetWidth()), static_cast<int>(WindowRenderProperty::GetHeight()), SDL_WINDOW_OPENGL);

	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}

	// OpenGLコンテキストを作成する
	mContext = SDL_GL_CreateContext(mWindow);

	// GLEWを初期化する
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		SDL_Log("Failed to initialize GLEW.");
		return false;
	}

	// 一部のプラットフォームでは、GLEWが無害なエラーコードを出力するので、
	// これをクリア。
	glGetError();

	// シェーダーを作成/コンパイルできることを確認してください
	if (!LoadShaders())
	{
		SDL_Log("Failed to load shaders.");
		return false;
	}

	// 画面全体の四角形を作成する
	CreateSpriteVerts();

	// Gバッファを作成する
	mGBuffer = new GBuffer();
	int width = static_cast<int>(WindowRenderProperty::GetWidth());
	int height = static_cast<int>(WindowRenderProperty::GetHeight());
	if (!mGBuffer->Create(width, height))
	{
		SDL_Log("Failed to create G-buffer.");
		return false;
	}

	return true;
}

bool Renderer::LoadShaders()
{
	// スプライトシェーダーを作成する
	mSpriteShader = new Shader();
	if (!mSpriteShader->Load("Shaders/Sprite.vert", "Shaders/Sprite.frag"))
	{
		return false;
	}

	mSpriteShader->SetActive();
	// ビュー投影行列を設定する
	Matrix4 spriteViewProj = Matrix4::CreateSimpleViewProj(WindowRenderProperty::GetWidth(), WindowRenderProperty::GetHeight());
	mSpriteShader->SetMatrixUniform("uViewProj", spriteViewProj);

	// ビュー投影行列を設定する
	mView = Matrix4::CreateLookAt(WindowRenderProperty::GetViewEye(), WindowRenderProperty::GetViewTarget(), WindowRenderProperty::GetViewUp());
	mProjection = Matrix4::CreatePerspectiveFOV(Math::ToRadians(WindowRenderProperty::GetFieldOfView()), WindowRenderProperty::GetWidth(), WindowRenderProperty::GetHeight(), WindowRenderProperty::GetCameraNear(), WindowRenderProperty::GetCameraFar());

	// 基本的なメッシュシェーダーを作成する
	mMeshShader = new Shader();
	if (!mMeshShader->Load("Shaders/Phong.vert", "Shaders/GBufferWrite.frag"))
	{
		return false;
	}
	mMeshShader->SetActive();


	mMeshShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// スキンシェーダーを作成する
	mSkinnedShader = new Shader();
	if (!mSkinnedShader->Load("Shaders/Skinned.vert", "Shaders/GBufferWrite.frag"))
	{
		return false;
	}

	mSkinnedShader->SetActive();
	mSkinnedShader->SetMatrixUniform("uViewProj", mView * mProjection);

	// GBufferから描画するためのシェーダーを作成する（グローバルライティング）
	mGGlobalShader = new Shader();
	if (!mGGlobalShader->Load("Shaders/GBufferGlobal.vert", "Shaders/GBufferGlobal.frag"))
	{
		return false;
	}
	// GBufferのために、各サンプラーをインデックスに関連付ける
	mGGlobalShader->SetActive();
	mGGlobalShader->SetIntUniform("uGDiffuse", 0);
	mGGlobalShader->SetIntUniform("uGNormal", 1);
	mGGlobalShader->SetIntUniform("uGWorldPos", 2);
	// ビュー投影はただのスプライトのものです
	mGGlobalShader->SetMatrixUniform("uViewProj", spriteViewProj);
	// 世界の変形スケールが画面に適用され、yが反転します
	Matrix4 gbufferWorld = Matrix4::CreateScale(WindowRenderProperty::GetWidth(), -WindowRenderProperty::GetHeight(),
		1.0f);
	mGGlobalShader->SetMatrixUniform("uWorldTransform", gbufferWorld);

	// GBufferからポイントライト用のシェーダーを作成する
	mGPointLightShader = new Shader();
	if (!mGPointLightShader->Load("Shaders/BasicMesh.vert","Shaders/GBufferPointLight.frag"))
	{
		return false;
	}
	// サンプラーインデックスを設定する
	mGPointLightShader->SetActive();
	mGPointLightShader->SetIntUniform("uGDiffuse", 0);
	mGPointLightShader->SetIntUniform("uGNormal", 1);
	mGPointLightShader->SetIntUniform("uGWorldPos", 2);
	mGPointLightShader->SetVector2Uniform("uScreenDimensions",Vector2(WindowRenderProperty::GetWidth(), WindowRenderProperty::GetHeight()));

	return true;
}

void Renderer::Draw()
{
	// G-bufferに3Dシーンを描画します。
	Draw3DScene(mGBuffer->GetBufferID(), mView, mProjection, 1.0f, false);
	// フレームバッファをゼロ（スクリーンのフレームバッファ）に戻します
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	// Gバッファから描画する
	DrawFromGBuffer();

	// すべてのスプライトコンポーネントを描画する
	// 深度バッファリングを無効にする
	glDisable(GL_DEPTH_TEST);
	// カラー バッファでアルファ ブレンディングを有効にします
	glEnable(GL_BLEND);
	glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ZERO);

	// シェーダー/VAOをアクティブに設定
	mSpriteShader->SetActive();

	mSpriteVerts->SetActive();

	for (auto sprite : mSprites)
	{
		if (sprite->GetVisible())
		{
			sprite->Draw(mSpriteShader);
		}
	}


	for (auto ui : mNowScene->GetImageStack())
	{
		if (ui->GetState() == Image::EActive) 
		{
			if (ui->GetFillMethod() == Image::Radial360)
			{
				int count = CreateFanSpriteVerts(ui->GetFillAmount(),30);
				ui->SetVerticesCount(count);
				mFanSpriteVerts->SetActive();
			}
			else
			{
				mSpriteVerts->SetActive();
			}
			ui->Draw(mSpriteShader);
		}
	}

	// バッファを入れ替える
	SDL_GL_SwapWindow(mWindow);
}

void Renderer::Draw3DScene(unsigned int framebuffer, const Matrix4& view, const Matrix4& proj,
	float viewPortScale, bool lit)
{
	// 現在のフレームバッファを設定する
	glBindFramebuffer(GL_FRAMEBUFFER, framebuffer);

	// スケールに基づいてビューポートサイズを設定します
	glViewport(0, 0,static_cast<int>(WindowRenderProperty::GetWidth() * viewPortScale),static_cast<int>(WindowRenderProperty::GetHeight() * viewPortScale));

	// カラー バッファ/深度バッファをクリア
	glClearColor(Color::mClearColor.x, Color::mClearColor.y, Color::mClearColor.z, Color::mClearColor.w);
	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// メッシュコンポーネントを描画する深度バッファリングを有効にする
	// アルファブレンドを無効にする
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	// メッシュシェーダーをアクティブに設定します
	mMeshShader->SetActive();
	// ビュー投影行列を更新する
	mMeshShader->SetMatrixUniform("uViewProj", view * proj);
	// 照明のユニフォームを更新する
	if (lit)
	{
		SetLightUniforms(mMeshShader, view);
	}

	for (auto mc : mMeshComps)
	{
		if (mc->GetVisible())
		{
			mc->Draw(mMeshShader);
		}
	}

	// スキンメッシュを有効
	mSkinnedShader->SetActive();
	// ビュー投影行列を更新する
	mSkinnedShader->SetMatrixUniform("uViewProj", view * proj);
	// 照明のユニフォームを更新する
	if (lit)
	{
		SetLightUniforms(mSkinnedShader, view);
	}
	for (auto sk : mSkeletalMeshes)
	{
		if (sk->GetVisible())
		{
			sk->Draw(mSkinnedShader);
		}
	}
}

void Renderer::DrawFromGBuffer()
{
	// グローバルライティングパスの深度テストを無効にします
	glDisable(GL_DEPTH_TEST);
	// グローバルGバッファシェーダをアクティブにする
	mGGlobalShader->SetActive();
	// スプライトの頂点クアッドを有効化する
	mSpriteVerts->SetActive();
	// Gバッファーテクスチャをサンプリングするように設定する
	mGBuffer->SetTexturesActive();
	// 照明ユニフォームを設定する
	SetLightUniforms(mGGlobalShader, mView);
	// 三角形を描画
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

	// Gバッファからデフォルトフレームバッファに深度バッファをコピーする
	glBindFramebuffer(GL_READ_FRAMEBUFFER, mGBuffer->GetBufferID());
	int width = static_cast<int>(WindowRenderProperty::GetWidth());
	int height = static_cast<int>(WindowRenderProperty::GetHeight());
	glBlitFramebuffer(0, 0, width, height,0, 0, width, height,GL_DEPTH_BUFFER_BIT, GL_NEAREST);

	// 深度テストを有効にしますが、深度バッファへの書き込みを無効にします。
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);
	/*
	// 点光源シェーダーとメッシュをアクティブに設定します。
	mGPointLightShader->SetActive();
	size_t size = mPointLightMesh->GetVertexArrays().size();
	for (unsigned int i = 0; i < size; i++) 
	{
		mPointLightMesh->GetVertexArrays()[i]->SetActive();
	}
	*/
	// ビュー投影行列を設定する
	//mGPointLightShader->SetMatrixUniform("uViewProj",mView * mProjection);
	// サンプリングのためにGバッファーのテクスチャを設定します
	mGBuffer->SetTexturesActive();

	// 点光源の色は既存の色に追加される
	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);
	/*
	// ポイントライトを描画
	for (PointLightComponent* p : mPointLights)
	{
		p->Draw(mGPointLightShader, mPointLightMesh);
	}
	*/
}

void Renderer::Shutdown()
{
	// Gバッファを取り除く
	if (mGBuffer != nullptr)
	{
		mGBuffer->Destroy();
		delete mGBuffer;
	}
	// ポイントライトを削除する
	while (!mPointLights.empty())
	{
		delete mPointLights.back();
	}
	
	delete mSpriteVerts;
	
	mSpriteShader->Unload();
	
	delete mSpriteShader;
	
	mMeshShader->Unload();
	
	delete mMeshShader;
	
	SDL_GL_DestroyContext(mContext);

	SDL_DestroyWindow(mWindow);
}

void Renderer::UnloadData()
{
	// テクスチャを破壊する
	for (auto i : mTextures)
	{
		i.second->Unload();
		delete i.second;
	}
	mTextures.clear();

	// メッシュを破壊する
	for (auto i : mMeshes)
	{
		i.second->Unload();
		delete i.second;
	}
	mMeshes.clear();
}

void Renderer::AddSprite(SpriteComponent* sprite)
{
	//ソートされたベクター内の挿入ポイントを見つける
	// （現在よりも高い描画順序を持つ最初の要素）
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// イテレータの位置の前に要素を挿入します
	mSprites.insert(iter, sprite);
}

void Renderer::RemoveSprite(SpriteComponent* sprite)
{
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

void Renderer::AddLineSprite(LineRenderer* sprite)
{
	//ソートされたベクター内の挿入ポイントを見つける
// （現在よりも高い描画順序を持つ最初の要素）
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mLineSprites.begin();
	for (;
		iter != mLineSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// イテレータの位置の前に要素を挿入します
	mLineSprites.insert(iter, sprite);
}

void Renderer::RemoveLineSprite(LineRenderer* sprite)
{
	auto iter = std::find(mLineSprites.begin(), mLineSprites.end(), sprite);
	mLineSprites.erase(iter);
}

void Renderer::AddMeshComp(MeshRenderer* mesh)
{
	if (mesh->GetIsSkeletal())
	{
		SkeletalMeshRenderer* sk = static_cast<SkeletalMeshRenderer*>(mesh);
		mSkeletalMeshes.emplace_back(sk);
	}
	else
	{
		mMeshComps.emplace_back(mesh);
	}
}

void Renderer::RemoveMeshComp(MeshRenderer* mesh)
{
	if (mesh->GetIsSkeletal())
	{
		SkeletalMeshRenderer* sk = static_cast<SkeletalMeshRenderer*>(mesh);
		auto iter = std::find(mSkeletalMeshes.begin(), mSkeletalMeshes.end(), sk);
		mSkeletalMeshes.erase(iter);
	}
	else
	{
		auto iter = std::find(mMeshComps.begin(), mMeshComps.end(), mesh);
		mMeshComps.erase(iter);
	}
}

void Renderer::AddPointLight(PointLightComponent* light)
{
	mPointLights.emplace_back(light);
}

void Renderer::RemovePointLight(PointLightComponent* light)
{
	auto iter = std::find(mPointLights.begin(), mPointLights.end(), light);
	mPointLights.erase(iter);
}

Texture* Renderer::GetTexture(const string& fileName)
{
	Texture* tex = nullptr;
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		tex = new Texture();
		if (tex->Load(fileName))
		{
			mTextures.emplace(fileName, tex);
		}
		else
		{
			delete tex;
			tex = nullptr;
		}
	}
	return tex;
}

Mesh* Renderer::GetMesh(const string& fileName)
{
	string file = Model::ModelPath + fileName;
	Mesh* m = nullptr;
	auto iter = mMeshes.find(file);
	if (iter != mMeshes.end())
	{
		m = iter->second;
	}
	else
	{
		m = new Mesh();
		if (m->LoadFromMeshBin(file, this))
		{
			mMeshes.emplace(file, m);
		}
		else if (m->Load(file, this))
		{
			mMeshes.emplace(file, m);
		}
		else
		{
			delete m;
			m = nullptr;
		}
	}
	return m;
}

vector<class Mesh*> Renderer::GetMeshs(const string& fileName)
{
	//ファイルパス追加
	string filePath = Model::ModelPath + fileName;
	//返す複数のメッシュ
	vector<class Mesh*> ms;
	//メッシュの数を確認する処理
	Mesh* m = nullptr;
	m = new Mesh();
	int maxMesh = m->CheckMeshIndex(filePath, this);

	for (int i = 0; i < maxMesh; i++)
	{
		string inTex = std::to_string(i);
		Mesh* mesh = nullptr;
		auto iter = mMeshes.find(filePath + inTex.c_str());
		//すでに読み込んでいるものならそこから取得
		if (iter != mMeshes.end())
		{
			mesh = iter->second;
		}
		else
		{
			mesh = new Mesh();
			//ここにLoad前にバイナリファイルがあるかを確認する
			if (mesh->LoadFromMeshBin(filePath, this, i))
			{
				mMeshes.emplace(filePath + inTex.c_str(), mesh);
			}
			else if (mesh->Load(filePath, this , i))
			{
				mMeshes.emplace(filePath + inTex.c_str(), mesh);
			}
			else
			{
				delete mesh;
				mesh = nullptr;
			}
		}

		if (mesh != nullptr) {
			ms.push_back(mesh);
		}
	}
	return ms;
}

void Renderer::CreateSpriteVerts()
{
	float vertices[] = {
		-0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 0.f, // top left
		0.5f, 0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 0.f, // top right
		0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 1.f, 1.f, // bottom right
		-0.5f,-0.5f, 0.f, 0.f, 0.f, 0.0f, 0.f, 1.f  // bottom left
	};

	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	mSpriteVerts = new VertexArray(vertices, 4, VertexArray::PosNormTex, indices, 6);
}
int Renderer::CreateFanSpriteVerts(float fillRatio, int maxSegments)
{
	// 作成した頂点配列とインデックス配列でVertexArray作成

	if (mFanSpriteVerts)
		delete mFanSpriteVerts;
	mFanSpriteVerts = new VertexArray(fillRatio, maxSegments);
	return mFanSpriteVerts->GetNumVerts();
}

void Renderer::CreateLineSpriteVerts()
{
	float lineVertices[] = {
	0.0f, 0.0f, 0.0f,  // 始点 (x, y, z)
	1.0f, 1.0f, 1.0f   // 終点 (x, y, z)
	};

	//mLineSpriteVerts = new VertexArray(lineVertices, 2);
}

void Renderer::SetLightUniforms(Shader* shader, const Matrix4& view)
{
	// カメラの位置は逆さまの視点からです
	Matrix4 invView = view;
	invView.Invert();
	shader->SetVectorUniform("uCameraPos", invView.GetTranslation());
	// Ambient light
	shader->SetVectorUniform("uAmbientLight", mAmbientLight);
	// Directional light
	shader->SetVectorUniform("uDirLight.mDirection",
		mDirLight.mDirection);
	shader->SetVectorUniform("uDirLight.mDiffuseColor",
		mDirLight.mDiffuseColor);
	shader->SetVectorUniform("uDirLight.mSpecColor",
		mDirLight.mSpecColor);
}

Vector3 Renderer::Unproject(const Vector3& screenPoint) const
{
	// screenPointをデバイス座標（-1から+1の間）に変換する
	Vector3 deviceCoord = screenPoint;
	deviceCoord.x /= (WindowRenderProperty::GetWidth()) * 0.5f;
	deviceCoord.y /= (WindowRenderProperty::GetHeight()) * 0.5f;

	// 反投影行列でベクトルを変換する
	Matrix4 unprojection = mView * mProjection;
	unprojection.Invert();
	return Vector3::TransformWithPerspDiv(deviceCoord, unprojection);
}

void Renderer::GetScreenDirection(Vector3& outStart, Vector3& outDir) const
{
	// スタートポイントを取得する（近くの平面の画面の中心）
	Vector3 screenPoint(0.0f, 0.0f, 0.0f);
	outStart = Unproject(screenPoint);
	// 画面の中央、近くと遠くの間にエンドポイントを取得します。
	screenPoint.z = 0.9f;
	Vector3 end = Unproject(screenPoint);
	// 方向ベクトルを取得する
	outDir = end - outStart;
	outDir.Normalize();
}