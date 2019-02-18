//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScenePlaying.cpp
//!
//! @brief  プレイシーン関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelatePlayer.h"
#include "RelateStage.h"
#include "RelateCamera.h"
#include "RelateEnemy.h"
#include "RelateDetectCollition.h"
#include "RelateBullet.h"
#include "RelatePause.h"
#include "RelateUI.h"


// データ型の定義 ==========================================================




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================
//サウンド
//BGM
HSND g_playBGM;
//SE
HSND g_playSE[17];


// 関数のプロトタイプ宣言 ==================================================




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief プレイシーンの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializePlaying(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------
	//サウンド
	//BGM
	g_playBGM = LoadSoundMem("Resources/Sounds/Stage_BGM_01.mp3");
	//SE
	g_playSE[0] = LoadSoundMem("Resources/Sounds/Clear_BGM.mp3");
	g_playSE[1] = LoadSoundMem("Resources/Sounds/False.mp3");
	g_playSE[2] = LoadSoundMem("Resources/Sounds/Damage_SE.mp3");
	g_playSE[3] = LoadSoundMem("Resources/Sounds/Move_SE.mp3");
	g_playSE[4] = LoadSoundMem("Resources/Sounds/Jump(small)_SE.mp3");
	g_playSE[5] = LoadSoundMem("Resources/Sounds/Jump(big)_SE.mp3.mp3");
	g_playSE[6] = LoadSoundMem("Resources/Sounds/Jump(enemy)_SE.mp3");
	g_playSE[7] = LoadSoundMem("Resources/Sounds/Block_SE.mp3");
	g_playSE[8] = LoadSoundMem("Resources/Sounds/FIRE_SE.mp3.mp3");
	g_playSE[9] = LoadSoundMem("Resources/Sounds/Pause.mp3");
	g_playSE[10] = LoadSoundMem("Resources/Sounds/Eat.mp3");
	g_playSE[11] = LoadSoundMem("Resources/Sounds/Gluttony.mp3");
	g_playSE[12] = LoadSoundMem("Resources/Sounds/Sword.mp3");
	g_playSE[13] = LoadSoundMem("Resources/Sounds/CollisionSword.mp3");
	g_playSE[14] = LoadSoundMem("Resources/Sounds/CollisionBullet.mp3");
	g_playSE[15] = LoadSoundMem("Resources/Sounds/Fly.mp3");
	g_playSE[16] = LoadSoundMem("Resources/Sounds/Burn.mp3");


	//ステージの初期化
	InitializeStage();

	//プレイヤーの初期化
	InitializePlayer();

	//カメラの初期化
	InitializeCamera();

	//敵の初期化
	InitializeEnemy();

	//弾の初期化
	InitializeBullet();

	//ポーズの初期化
	InitializePause();

	//UIの初期化
	InitializeUI();

}



//----------------------------------------------------------------------
//! @brief プレイシーンの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdatePlaying(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//ポーズ中
	if (g_pauseFlag == TRUE)
	{
		//ポーズの更新
		UpdatePause();
	}
	else
	{
		//ステージの更新
		UpdateStage();

		//カメラの更新
		UpdateCamera();

		//プレイヤーの更新
		UpdatePlayer();

		//敵の更新
		UpdateEnemy();

		//弾の更新
		UpdateBullet();

		//当たり判定
		AllDetectCollision();

		//ポーズの操作
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_10) != 0)	//スペースキー
		{
			//フラグを立てる
			g_pauseFlag = TRUE;

			//SEの再生
			PlaySoundMem(g_playSE[9], DX_PLAYTYPE_BACK, TRUE);
		}
	}

#if DEBUG

#else
	//BGMの再生
	if (CheckSoundMem(g_playBGM) == 0)
	{
		PlaySoundMem(g_playBGM, DX_PLAYTYPE_BACK, TRUE);
	}
#endif

	//シーンの移動
	//プレイヤーがやられた
	if (g_player.state == 0)
	{
		//BGMの停止
		StopSoundMem(g_playBGM);
		//SEの再生
		PlaySoundMem(g_playSE[1], DX_PLAYTYPE_NORMAL, TRUE);
		//セレクトシーンへ
		ChangeScene(SCENE_SELECT);
	}
	//プレイヤーがゴールした
	if (g_player.dataPos.x >= (STAGE_WIDTH - 13)*STAGE_SIZE)
	{
		//BGMの停止
		StopSoundMem(g_playBGM);
		//SEの再生
		PlaySoundMem(g_playSE[0], DX_PLAYTYPE_NORMAL, TRUE);
		//セレクトシーンへ
		ChangeScene(SCENE_SELECT);
	}

}



//----------------------------------------------------------------------
//! @brief プレイシーンの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderPlaying(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//ステージの描画
	RendarStage();

	// <プレイヤーの描画>
	RendarPlayer();

	//敵の描画
	RendarEnemy();

	//弾の描画
	RendarBullet();

	//ポーズの描画
	if (g_pauseFlag == TRUE)
	{
		RenderPause();
	}

}



//----------------------------------------------------------------------
//! @brief プレイシーンの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizePlaying(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//画像データの削除
	InitGraph();

	//音データの削除
	InitSoundMem();

}