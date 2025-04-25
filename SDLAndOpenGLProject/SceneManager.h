#pragma once
#include "STD.h"

class SceneManager
{
public:
	static void LoadScene(int index);

	static void AddSceneList(int sceneIndex,class BaseScene* scene);

	static class BaseScene* GetNowScene() { return mNowScene; }

	static bool IsLoading() { return loading; }

	static void NoActiveLoading() { loading = false; }
private:
	static std::unordered_map<int, class BaseScene*> mScenes;

	static class BaseScene* mNowScene;

	static bool loading;
};

