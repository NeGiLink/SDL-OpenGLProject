#pragma once
#include "StandardLibrary.h"

//画面サイズ
namespace Window
{
	//画面サイズ(横)
	static float Width = 1280.0f;
	//画面サイズ(縦)
	static float Height = 768.0f;
	//ビュー投影行列(カメラの目)
	static Vector3 ViewEye = Vector3::Zero;
	//ビュー投影行列(カメラターゲット)
	static Vector3 ViewTarget = Vector3::UnitX;
	//ビュー投影行列(カメラ方向)
	static Vector3 ViewUp = Vector3::UnitZ;
	//視野角
	static float FieldOfView = 70.0f;
	//カメラの最低描画距離
	static float CameraNear = 0.1f;
	//カメラの最大描画距離
	static float CameraFar = 10000.0f;
}