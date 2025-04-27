#pragma once
#include "StandardLibrary.h"

//シーンの管理、ロード処理を行うクラス
class SceneManager
{
public:
	static void LoadScene(int index);

	static void AddSceneList(int sceneIndex,class BaseScene* scene);

	static class BaseScene* GetNowScene() { return mNowScene; }

	static bool IsLoading() { return loading; }

	static void DisabledLoading() { loading = false; }
private:
	static std::unordered_map<int, class BaseScene*>	mScenes;

	static class BaseScene*								mNowScene;

	static bool											loading;
};

