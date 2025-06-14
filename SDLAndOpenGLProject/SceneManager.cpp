#include "SceneManager.h"
#include "BaseScene.h"

std::unordered_map<int,BaseScene*> SceneManager::mScenes;

BaseScene* SceneManager::mNowScene;

bool SceneManager::loading = false;

int SceneManager::mNowSceneIndex = 0;

void SceneManager::LoadScene(int index)
{
	if (mNowScene == mScenes[index]) { return; }
	mNowScene = mScenes[index];
	mNowSceneIndex = index;
	loading = true;
}

void SceneManager::AddSceneList(class BaseScene* scene)
{
	auto iter = mScenes.find(mScenes.size());
	if (iter != mScenes.end())
	{
		return;
	}
	else
	{
		mScenes.emplace(mScenes.size(), scene);
	}
}
