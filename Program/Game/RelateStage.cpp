//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateStage.cpp
//!
//! @brief  ステージ関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include <stdio.h>
#include "GameMain.h"
#include "RelateStage.h"
#include "RelatePlayer.h"
#include "RelateCamera.h"
#include "RelateUI.h"
#include "RelateAnimation.h"



// データ型の定義 ==========================================================




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================

// <背景>
BackGround g_backGround;

// <ステージ>
int g_stageData[STAGE_HEIGHT][STAGE_WIDTH];

ObjectStage g_objectStage[MAX_STAGECHIP];

HGRP g_stageImage[10];

HGRP g_goalImage;

int g_stageObjectNumber;

// ステージID
int g_stageId;

//アニメーション
StageAnimation g_stageAnimation[100];


// 関数のプロトタイプ宣言 ==================================================

//背景のスクロール
void ScrollBackGround(BackGround *backGround, ObjectPlayer *player);

//背景の描画
void DrawBackGround(BackGround backGround);

//ステージの読み込み
void LoadStage(char *stageFile, int width, int height);

//チュートリアル中の操作説明
void ExplainOperation1(Vec2D pos);
void ExplainOperation2(Vec2D pos);


// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief ステージの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeStage(void)
{
	//ローカル変数の宣言//----------------------------------------------
	//ステージファイル
	char *stageFile[MAX_STAGE];

	//配列に使用
	int x;
	int y;

	//ローカル変数の初期化//--------------------------------------------
	stageFile[0] = "Resources/StageData/stage.csv";
	stageFile[1] = "Resources/StageData/stage1.csv";
	stageFile[2] = "Resources/StageData/stage2.csv";
	stageFile[3] = "Resources/StageData/stage3.csv";
	stageFile[4] = "Resources/StageData/stage4.csv";
	stageFile[5] = "Resources/StageData/tutorial.csv";
	stageFile[6] = "Resources/StageData/tutorial2.csv";


	//処理の内容//------------------------------------------------------

	// <背景>
	g_backGround.pos.x = 0.0f;
	g_backGround.pos.y = 0.0f;
	// 画像の読み込み
	g_backGround.handle = LoadGraph("Resources/Images/背景.png");

	// <ステージ>
	g_stageObjectNumber = 0;

	// 画像の読み込み
	LoadDivGraph("Resources/Images/STAGE_IMAGE.png", 3, 3, 1, 64, 64, g_stageImage);
	LoadStage(stageFile[g_stageId], STAGE_WIDTH, STAGE_HEIGHT);

	for (y = 0; y < STAGE_HEIGHT; y++)
	{
		for (x = 0; x < STAGE_WIDTH; x++)
		{
			if (g_stageData[y][x] != 0)
			{
				//ステージオブジェクトを生成
				CreateStageObject(&g_objectStage[g_stageObjectNumber], (float)(STAGE_SIZE*x), (float)(STAGE_SIZE*y), g_stageData[y][x]);
			}
		}
	}

	//ゴール画像の読み込み
	g_goalImage = LoadGraph("Resources/Images/ゴール.png");

	//アニメーション
	for (x = 0; x < 100; x++)
	{
		g_stageAnimation[x].pos.x = 0.0f;
		g_stageAnimation[x].pos.y = 0.0f;
		LoadDivGraph("Resources/Images/Burn.png", 3, 3, 1, 64, 64, g_stageAnimation[x].image.handle);
		g_stageAnimation[x].animation.elapsedTime = 0;
		g_stageAnimation[x].animation.frameDuration = 30;
		g_stageAnimation[x].animation.frameNum = 0;
		g_stageAnimation[x].animation.numFrames = 2;
		g_stageAnimation[x].animation.state = 0;
	}

}



//----------------------------------------------------------------------
//! @brief ステージの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateStage(void)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//背景のスクロール
	ScrollBackGround(&g_backGround, &g_player);

	//アニメーションの更新
	for (i = 0; i < 100; i++)
	{
		if (g_stageAnimation[i].animation.state == 1)
		{
			UpdataAnimation(&g_stageAnimation[i].animation);
		}
	}

}



//----------------------------------------------------------------------
//! @brief ステージの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RendarStage(void)
{
	//ローカル変数の宣言//----------------------------------------------

	//配列に使用
	int i;

	//描画座標
	float x1;
	float y1;
	float x2;
	float y2;


	//ローカル変数の初期化//--------------------------------------------
	



	//処理の内容//------------------------------------------------------

	//背景の描画
	DrawBackGround(g_backGround);

	//ゴールの描画
	DrawGraphF(((STAGE_WIDTH - 15)*STAGE_SIZE) - g_cameraPos.x, (13 * STAGE_SIZE) - 128, g_goalImage, TRUE);

	//ステージ
	for (i = 0; i < g_stageObjectNumber; i++)
	{
		if (g_objectStage[i].state == 1)
		{
			if ((g_objectStage[i].pos.x >= g_cameraPos.x - STAGE_SIZE) && (g_objectStage[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + STAGE_SIZE))
			{
				x1 = g_objectStage[i].pos.x - g_cameraPos.x;
				x2 = g_objectStage[i].pos.x + (float)STAGE_SIZE - g_cameraPos.x;
				y1 = g_objectStage[i].pos.y;
				y2 = g_objectStage[i].pos.y + (float)STAGE_SIZE;

				DrawExtendGraphF(x1, y1, x2, y2, g_stageImage[g_objectStage[i].type - 1], TRUE);
			}
		}
	}

	//チュートリアル時の操作説明の描画
	if (g_stageId == 5)
	{
		ExplainOperation1(g_player.dataPos);
	}
	if (g_stageId == 6)
	{
		ExplainOperation2(g_player.dataPos);
	}

	//アニメーション
	for (i = 0; i < 100; i++)
	{
		if (g_stageAnimation[i].animation.state == 1)
		{
			x1 = g_stageAnimation[i].pos.x - g_cameraPos.x;
			x2 = g_stageAnimation[i].pos.x + (float)STAGE_SIZE - g_cameraPos.x;
			y1 = g_stageAnimation[i].pos.y;
			y2 = g_stageAnimation[i].pos.y + (float)STAGE_SIZE;

			DrawExtendGraphF(x1, y1, x2, y2, g_stageAnimation[i].image.handle[g_stageAnimation[i].animation.frameNum], TRUE);
		}
	}

}



//----------------------------------------------------------------------
//! @brief ステージオブジェクトの生成処理
//!
//! @param[stageObject] 生成するステージオブジェクト
//! @param[posX] ステージオブジェクトのX座標
//! @param[posY] ステージオブジェクトのY座標
//! @param[type] ステージオブジェクトのタイプ
//!
//! @return なし
//----------------------------------------------------------------------
void CreateStageObject(ObjectStage *stageObject, float posX,float posY,int type)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	stageObject->pos.x = posX;
	stageObject->pos.y = posY;
	stageObject->type = type;
	stageObject->state = 1;

	g_stageObjectNumber++;
}



//----------------------------------------------------------------------
//! @brief 背景のスクロール処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void ScrollBackGround(BackGround *backGround, ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//背景をプレイヤーに合わせてスクロールさせる
	if ((player->vel.x != 0) && (player->dataPos.x > SCREEN_CENTER_X / 2) && (g_cameraPos.x < (STAGE_WIDTH*STAGE_SIZE) - CAMERA_WIDTH))
	{
		backGround->pos.x += -(player->vel.x / 4);
	}
	
	//背景をずらす
	if (backGround->pos.x < -SCREEN_WIDTH)
	{
		backGround->pos.x = 0;
	}
	if (backGround->pos.x > 0)
	{
		backGround->pos.x = -SCREEN_WIDTH;
	}


}



//*---------------------------------------------------------------------
//* ステージデータの読み込み
//*
//* @param [file] ステージファイル名
//* @param [Width] ステージの幅
//* @param [Height] ステージの高さ
//*
//* @return なし
//*---------------------------------------------------------------------
void LoadStage(char *file, int width, int height)
{
	//ローカル変数の宣言//--------------------------------
	// ファイル構造体
	FILE *fp;
	char buf[512];

	int i;	//配列に使用
	int j;	//配列に使用

	char *p;
	long number;

	//ローカル変数の初期化//------------------------------
	//ファイルを開く
	fp = fopen(file, "r");

	p = NULL;

	//処理の内容//----------------------------------------
	if (fp == NULL)
	{
		fprintf(stderr, "ファイルがオープンできません\n");
		// 強制終了
		exit(1);
	}

	for (i = 0; i < height; i++)
	{
		if (fgets(buf, 512, fp) != NULL)
		{
			p = buf;

			for (j = 0; j < width; j++)
			{
				number = strtol(p, &p, 0);

				g_stageData[i][j] = (int)number;
				p++;
			}
		}
	}

	//ファイルを閉じる
	fclose(fp);

}



//----------------------------------------------------------------------
//! @brief 背景の描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void DrawBackGround(BackGround backGround)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//1枚目
	DrawGraphF(backGround.pos.x, backGround.pos.y, backGround.handle, TRUE);

	//2枚目
	DrawGraphF(backGround.pos.x + SCREEN_WIDTH, backGround.pos.y, backGround.handle, TRUE);

}



//----------------------------------------------------------------------
//! @brief チュートリアル中の操作説明1の処理
//!
//! @param[pos] 座標
//!
//! @return なし
//----------------------------------------------------------------------
void ExplainOperation1(Vec2D pos)
{
	//ローカル変数の宣言//----------------------------------------------
	char *text;

	float x;
	float y;

	//ローカル変数の初期化//--------------------------------------------
	
	x = 500.0f;
	y = 50.0f;

	//処理の内容//------------------------------------------------------

	//移動
	if (pos.x <= 300)
	{
		text = "左右キーで移動";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//ジャンプ
	if ((pos.x >= 300) && (pos.x <= 750))
	{
		text = "上キーでジャンプ";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//食べる
	if ((pos.x >= 750) && (pos.x <= 1120))
	{
		text = "Zキーで食べる";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//攻撃
	if ((pos.x >= 2300) && (pos.x <= 2800))
	{
		text = "Zキーで攻撃";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}

}



//----------------------------------------------------------------------
//! @brief チュートリアル中の操作説明2の処理
//!
//! @param[pos] 座標
//!
//! @return なし
//----------------------------------------------------------------------
void ExplainOperation2(Vec2D pos)
{
	//ローカル変数の宣言//----------------------------------------------
	char *text;

	float x;
	float y;

	//ローカル変数の初期化//--------------------------------------------

	x = 500.0f;
	y = 50.0f;

	//処理の内容//------------------------------------------------------

	//特殊能力
	if (pos.x <= 360)
	{
		text = "特定の敵を食べると\n特殊能力が使える";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//制限
	if ((pos.x >= 360) && (pos.x <= 700))
	{
		text = "カウントが0になると\n使えなくなる";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//斬撃
	if ((pos.x >= 700) && (pos.x <= 1400))
	{
		text = "Xキーで斬撃を飛ばせる";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//飛行
	if ((pos.x >= 1760) && (pos.x <= 2200))
	{
		text = "Xキーで飛行モードに\n切り替える";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//操作
	if ((pos.x >= 2200) && (pos.x <= 2970))
	{
		text = "十字キーで移動";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//炎
	if ((pos.x >= 3350) && (pos.x <= 4470))
	{
		text = "Xキーで氷のブロックを\n解かせる";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//食べる
	if ((pos.x >= 4830) && (pos.x <= 5900))
	{
		text = "Xキーで一気に\n食べることができる";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//終了
	if (pos.x >= 6000)
	{
		text = "以上でチュートリアルは\n終了です";

		//テキスト
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}

}
