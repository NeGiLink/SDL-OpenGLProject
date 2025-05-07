#pragma once

//***ゲームシーンで必要なオブジェクトや画像の情報をまとめているファイル
//Actor
#include "Actor.h"
//プロジェクトにデフォルトで入っているオブジェクトクラスのインクルード
#include "PlaneActor.h"
#include "CubeActor.h"
#include "SphereActor.h"
#include "CapsuleActor.h"
//Actorを継承したオブジェクトクラスのインクルード
#include "FPSActor.h"
#include "TargetActor.h"
#include "BallActor.h"
#include "DiceActor.h"
#include "DebugStageActor.h"
#include "TestCharacter.h"
#include "YBotActor.h"
#include "SmallCharacter.h"
//カメラの基底クラスのインクルード
#include "BaseCamera.h"
//スケルタルメッシュ関係のインクルード
#include "MeshRenderer.h"
#include "Skeleton.h"
//アニメーション関係のインクルード
#include "Animation.h"
#include "Animator.h"
//デフォルトでプロジェクトにある画像、テキスト描画関係のインクルード
#include "Image.h"
#include "Font.h"
#include "Text.h"
//UI関係のインクルード
#include "PauseMenu.h"
#include "UIScreen.h"
#include "HUD.h"
//ライト関係のインクルード
#include "PointLightComponent.h"