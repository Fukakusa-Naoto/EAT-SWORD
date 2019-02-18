//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneTitle.cpp
//!
//! @brief  タイトルシーン関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "SceneTitle.h"
#include "RelateUI.h"
#include "RelateStage.h"


// 列挙体の定義 ============================================================




// データ型の定義 ==========================================================

//ObjectTitle型
struct Tag_ObjectTitle
{
	Vec2D pos;
	HGRP handle;
	Size size;
};
typedef struct Tag_ObjectTitle ObjectTitle;


// 定数の定義 ==============================================================

//UIの描画間隔
#define DRAW_SPACE (64.0f)


// グローバル変数の定義 ====================================================

//タイトル
ObjectTitle g_title;

//UI
HGRP g_titleUiImage[2];
HGRP g_jawImage[2];

//テキスト
ObjectTitle g_titleUI[2];
//顎
ObjectJaw g_jaw;

//サウンド
//BGM
HSND g_titleBGM;
//SE
HSND g_titleSE[2];


// 関数のプロトタイプ宣言 ==================================================




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief タイトルシーンの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeTitle(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------
	
	//タイトル
	g_title.pos.x = (float)SCREEN_CENTER_X;
	g_title.pos.y = (float)SCREEN_CENTER_Y / 2;
	g_title.handle = LoadGraph("Resources/Images/TITLE.png");
	g_title.size.width = 384;
	g_title.size.height = 64;


	//UI
	LoadDivGraph("Resources/Images/TITLE_STRING.png", 2, 1, 2, 128, 32, g_titleUiImage);
	//START
	g_titleUI[0].pos.x = (float)SCREEN_CENTER_X;
	g_titleUI[0].pos.y = (float)SCREEN_CENTER_Y + DRAW_SPACE;
	g_titleUI[0].handle = g_titleUiImage[0];
	g_titleUI[0].size.width = 200;
	g_titleUI[0].size.height = 32;

	//EXIT
	g_titleUI[1].pos.x = (float)SCREEN_CENTER_X;
	g_titleUI[1].pos.y = (float)SCREEN_CENTER_Y + DRAW_SPACE * 2;
	g_titleUI[1].handle = g_titleUiImage[1];
	g_titleUI[1].size.width = 200;
	g_titleUI[1].size.height = 32;


	//顎
	LoadDivGraph("Resources/Images/顎.png", 2, 1, 2, 640, 320, g_jawImage);
	g_jaw.pos = g_titleUI[0].pos;
	g_jaw.size.width = 150;
	g_jaw.size.height = 25;
	g_jaw.space = 17.0f;

	//サウンド
	//BGM
	g_titleBGM = LoadSoundMem("Resources/Sounds/Title_BGM.mp3");
	//SE
	g_titleSE[0] = LoadSoundMem("Resources/Sounds/Cusor_SE.mp3");
	g_titleSE[1] = LoadSoundMem("Resources/Sounds/decision_SE.mp3");

}



//----------------------------------------------------------------------
//! @brief タイトルシーンの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateTitle(void)
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
			selectId = 0;
			g_jaw.pos = g_titleUI[0].pos;
			//SEの再生
			PlaySoundMem(g_titleSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_DOWN) != 0)	//下キー
		{
			selectId = 1;
			g_jaw.pos = g_titleUI[1].pos;
			//SEの再生
			PlaySoundMem(g_titleSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_1) != 0)	//Zキー
		{
			selectFlag = TRUE;
			//SEの再生
			PlaySoundMem(g_titleSE[1], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	//シーンの移動
	if (selectFlag == TRUE)
	{
		g_jaw.space--;

		if (g_jaw.space <= 0)
		{
			if (selectId == 0)
			{
				selectId = 0;
				g_stageId = 0;
				//セレクトシーンへ
				ChangeScene(SCENE_SELECT);

				selectFlag = FALSE;
			}
			else
			{
				selectId = 0;
				selectFlag = FALSE;
				//ゲームを終了
				ExitGame();
			}
		}
	}

	//BGMの再生
#if DEBUG

#else
	if (CheckSoundMem(g_titleBGM) == 0)
	{
		PlaySoundMem(g_titleBGM, DX_PLAYTYPE_BACK, TRUE);
	}
#endif

}



//----------------------------------------------------------------------
//! @brief タイトルシーンの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderTitle(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------
	
	//背景の描画
	DrawBox(SCREEN_LEFT, SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_WHITE, TRUE);

	//タイトルの描画
	DrawRotaGraphF(g_title.pos.x, g_title.pos.y, 1.0, 0.0, g_title.handle, TRUE, FALSE);

	//テキストの描画
	//START
	DrawRotaGraphF(g_titleUI[0].pos.x, g_titleUI[0].pos.y, 1.0, 0.0, g_titleUI[0].handle, TRUE, FALSE);
	//EXIT
	DrawRotaGraphF(g_titleUI[1].pos.x, g_titleUI[1].pos.y, 1.0, 0.0, g_titleUI[1].handle, TRUE, FALSE);

	//顎の描画
	DrawJaw(g_jaw.pos.x, g_jaw.pos.y, (float)g_jaw.size.width, (float)g_jaw.size.height, g_jaw.space, g_jawImage[0], g_jawImage[1]);

}



//----------------------------------------------------------------------
//! @brief タイトルシーンの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeTitle(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------
	
	//画像データの削除
	InitGraph();

	//音データの削除
	InitSoundMem();

}
