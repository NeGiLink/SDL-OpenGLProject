#pragma once
#include "StandardLibrary.h"

//シーンの管理、ロード処理を行うクラス
class SceneManager
{
private:
	//ロード対象のシーンリスト
	static std::unordered_map<int, class BaseScene*>	mScenes;
	//現在のシーン
	static class BaseScene*								mNowScene;
	//ロードフラグ
	static bool											loading;
public:
	//シーンのロード処理
	static void											LoadScene(int index);
	//シーンリストに追加
	static void											AddSceneList(class BaseScene* scene);
	//現在のシーンの取得
	static class BaseScene*								GetNowScene() { return mNowScene; }
	//ロードフラグの取得
	static bool											IsLoading() { return loading; }
	//ロードフラグを解除
	static void											DisabledLoading() { loading = false; }
};

