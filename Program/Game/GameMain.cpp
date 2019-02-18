//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.cpp
//!
//! @brief  ゲーム関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "ChangeScene.h"
#include "RelateUI.h"


// 列挙体の定義 ============================================================
//シーンの切り替えID
enum Tag_ChangeID
{
	NO,	//なし
	CLOSE,	//閉じる
	CHANGE,	//切り替える
	OPEN	//開ける
};
typedef enum Tag_ChangeID ChangeID;


// データ型の定義 ==========================================================




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================
//シーン管理
SceneId g_currentSceneId;	//現在のシーンのID
SceneId g_nextSceneId;		//次のシーンのID

//キーの入力状態
int g_currentInputState;	//現在
int g_lastInputState;	//前回

//顎
HGRP g_jawImages[2];
float g_jawSpece;

//シーンの切り替え
ChangeID g_changeID;

//SE
HSND g_gameSE;


// 関数のプロトタイプ宣言 ==================================================

// シーンの切り替え演出
void ConvertScene(void);


// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ゲームの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeGame(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//シーンIDの初期化
	g_currentSceneId = SCENE_NONE;
	g_nextSceneId = SCENE_LOGO;

	//顎のスペース
	LoadDivGraph("Resources/Images/顎.png", 2, 1, 2, 640, 320, g_jawImages);
	g_jawSpece = 0.0f;

	//シーンの切り替え
	g_changeID = CHANGE;

	//SEの読み込み
	g_gameSE = LoadSoundMem("Resources/Sounds/Close.mp3");
}



//----------------------------------------------------------------------
//! @brief ゲームの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateGame(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//前回のキーの状態を記憶しておく
	g_lastInputState = ~g_currentInputState;

	//キー入力の読み込み
	g_currentInputState = GetJoypadInputState(DX_INPUT_KEY_PAD1);


	//シーンの切り替え
	ConvertScene();


	//シーン別の更新処理
	if (g_changeID == NO)
	{
		UpdateScene();
	}
	
}



//----------------------------------------------------------------------
//! @brief ゲームの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderGame(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//シーン別の描画処理
	RenderScene();

	//顎の描画
	if (g_changeID != NO)
	{
		DrawJaw((float)SCREEN_CENTER_X, (float)SCREEN_CENTER_Y, (float)SCREEN_WIDTH, 320.0f, g_jawSpece, g_jawImages[0], g_jawImages[1]);
	}

}



//----------------------------------------------------------------------
//! @brief ゲームの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeGame(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//シーン別の終了処理
	FinalizeScene();
}



//----------------------------------------------------------------------
//! @brief シーンの変更処理
//!
//! @param[nextSceneId] 次のシーン
//!
//! @return なし
//----------------------------------------------------------------------
void ChangeScene(SceneId nextSceneId)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//次のシーンの予約
	g_nextSceneId = nextSceneId;

	//演出
	g_changeID = CLOSE;

}



//----------------------------------------------------------------------
//! @brief シーンの切り替え演出処理
//!
//! @param[no] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ConvertScene(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	if (g_nextSceneId != g_currentSceneId)
	{
		switch (g_changeID)
		{
		case CLOSE:
			g_jawSpece -= 10;

			if (g_jawSpece <= 0)
			{
				//SEの再生
				PlaySoundMem(g_gameSE, DX_PLAYTYPE_BACK, TRUE);

				g_changeID = CHANGE;
			}
			break;
		case CHANGE:
			if (CheckSoundMem(g_gameSE) != 1)
			{
				FinalizeScene();	//シーンの終了処理
				g_currentSceneId = g_nextSceneId;	//次のシーンへ更新
				InitializeScene();	//シーンの初期化処理
				LoadDivGraph("Resources/Images/顎.png", 2, 1, 2, 640, 320, g_jawImages);
				g_gameSE = LoadSoundMem("Resources/Sounds/Close.mp3");
				g_changeID = OPEN;
			}
			break;
		default:

			break;
		}
		
	}

	if (g_changeID == OPEN)
	{
		g_jawSpece += 10;

		if (g_jawSpece >= SCREEN_CENTER_Y + 80)
		{
			g_jawSpece = (float)SCREEN_CENTER_Y + 80;
			g_changeID = NO;
		}
	}
}