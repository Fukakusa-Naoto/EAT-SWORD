//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelatePause.cpp
//!
//! @brief  ポーズ関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "RelatePause.h"
#include "RelateUI.h"


// データ型の定義 ==========================================================




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================

//ポーズのフラグ
BOOL g_pauseFlag;

//画像
HGRP g_pauseImage;
HGRP g_cousorImage[2];

//顎
ObjectJaw g_cousor;

//サウンド
HGRP g_pauseSE[2];

// 関数のプロトタイプ宣言 ==================================================




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ポーズの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializePause(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//フラグ
	g_pauseFlag = FALSE;

	//画像の読み込み
	g_pauseImage = LoadGraph("Resources/Images/Pause.png");

	//顎
	LoadDivGraph("Resources/Images/顎.png", 2, 1, 2, 640, 320, g_cousorImage);
	g_cousor.pos.x = (float)SCREEN_CENTER_X;
	g_cousor.pos.y = 165.0f;
	g_cousor.size.width = 150;
	g_cousor.size.height = 25;
	g_cousor.space = 17.0f;

	//サウンドの読み込み
	g_pauseSE[0] = LoadSoundMem("Resources/Sounds/Cusor_SE.mp3");
	g_pauseSE[1] = LoadSoundMem("Resources/Sounds/decision_SE.mp3");

}



//----------------------------------------------------------------------
//! @brief ポーズの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdatePause(void)
{
	//ローカル変数の宣言//----------------------------------------------
	static int selectId = 0;

	static BOOL selectFlag = FALSE;


	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------

	//キー入力
	if (selectFlag == FALSE)
	{
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_UP) != 0)	//上キー
		{
			selectId--;
			//SEの再生
			PlaySoundMem(g_pauseSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_DOWN) != 0)	//下キー
		{
			selectId++;
			//SEの再生
			PlaySoundMem(g_pauseSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_1) != 0)	//Zキー
		{
			selectFlag = TRUE;
			//SEの再生
			PlaySoundMem(g_pauseSE[1], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	//IDの制限
	if (selectId <= 0)
	{
		selectId = 0;
	}
	if (selectId >= 2)
	{
		selectId = 2;
	}

	//顎の座標更新
	g_cousor.pos.y = 165.0f + 75.0f*(float)selectId;

	//シーンの移動
	if (selectFlag == TRUE)
	{
		g_cousor.space--;

		if (g_cousor.space <= 0)
		{
			switch (selectId)
			{
				case 0:
					//元に戻す
					selectId = 0;
					g_cousor.space = 17.0f;
					selectFlag = FALSE;
					//ゲームに戻る
					g_pauseFlag = FALSE;
					break;
				case 1:
					//元に戻す
					selectId = 0;
					g_cousor.space = 17.0f;
					selectFlag = FALSE;
					//フラグを戻す
					g_pauseFlag = FALSE;
					//ステージセレクトへ
					ChangeScene(SCENE_SELECT);
					break;
				case 2:
					//元に戻す
					selectId = 0;
					g_cousor.space = 17.0f;
					selectFlag = FALSE;
					//フラグを戻す
					g_pauseFlag = FALSE;
					//ステージセレクトへ
					ChangeScene(SCENE_TITLE);
					break;
			default:

				break;
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief ポーズの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderPause(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//ポーズ画面
	DrawGraph(160, 96, g_pauseImage, TRUE);

	//顎の描画
	DrawJaw(g_cousor.pos.x, g_cousor.pos.y, (float)g_cousor.size.width, (float)g_cousor.size.height, g_cousor.space, g_cousorImage[0], g_cousorImage[1]);

}