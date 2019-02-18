//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file  RelateUI.cpp
//!
//! @brief  UI関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "RelateUI.h"


// データ型の定義 ==========================================================




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================
//画像
HGRP g_images[4];



// 関数のプロトタイプ宣言 ==================================================




// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief UIの初期化処理
//!
//! @param[no] 
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeUI(void)
{
	//ローカル変数の宣言//----------------------------------------------
	



	//ローカル変数の初期化//--------------------------------------------
	



	//処理の内容//------------------------------------------------------
	//画像の読み込み
	LoadDivGraph("Resources/Images/UI.png", 4, 4, 1, 70, 70, g_images);



}



//----------------------------------------------------------------------
//! @brief HPゲージの描画処理
//!
//! @param[x] 描画する左上のX座標
//! @param[y] 描画する左上のY座標
//! @param[width] 横幅
//! @param[height] 高さ
//! @param[max] 最大値
//! @param[now] 現在のHP
//!
//! @return なし
//----------------------------------------------------------------------
void DrawHPGauge(float x, float y, float width, float height, int max, int now)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;

	//目盛
	float scaleX1;
	float scaleX2;
	float scaleWidth;



	//ローカル変数の初期化//--------------------------------------------
	scaleWidth = width / (float)max;



	//処理の内容//------------------------------------------------------

	//枠
	DrawBoxAA(x - 1, y - 1, x + width + 1, y + height + 1, COLOR_BLACK, TRUE);

	for (i = 1; i <= max; i++)
	{
		scaleX1 = x + scaleWidth*(i - 1);
		scaleX2 = scaleX1 + scaleWidth;

		if (i <= now)
		{
			DrawBoxAA(scaleX1, y, scaleX2, y + height, COLOR_WHITE, FALSE);
		}
		else
		{
			DrawBoxAA(scaleX1, y, scaleX2, y + height, COLOR_WHITE, TRUE);
		}
	}
}



//----------------------------------------------------------------------
//! @brief 時間の描画処理
//!
//! @param[x] X座標
//! @param[y] Y座標
//! @param[time] 表示時間
//! @param[handle] グラフィックハンドル
//! @param[type] タイプ
//!
//! @return なし
//----------------------------------------------------------------------
void DrawTimer(float x, float y, int time, HGRP handle[], Type type)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//背景
	switch (type)
	{
	case NORMAL:
		
		break;
	case SWORD:
		DrawRotaGraphF(x, y, 1.0, 0.0, g_images[0], TRUE, FALSE);
		break;
	case FIRE:
		DrawRotaGraphF(x, y - 15.0f, 1.0, 0.0, g_images[1], TRUE, FALSE);
		break;
	case FLY:
		DrawRotaGraphF(x, y, 1.0, 0.0, g_images[2], TRUE, FALSE);
		break;
	case BIG:
		DrawRotaGraphF(x, y, 1.0, 0.0, g_images[3], TRUE, FALSE);
		break;
	default:

		break;
	}

	//枠
	DrawCircleAA(x, y, 20.0f, 100, COLOR_WHITE, TRUE);
	DrawCircleAA(x, y, 20.0f, 100, COLOR_BLACK, FALSE);

	//数字
	//十の桁
	DrawRotaGraphF(x - 8.0f, y, 0.5, 0.0, handle[time / 10], TRUE, FALSE);
	//一の桁
	DrawRotaGraphF(x + 8.0f, y, 0.5, 0.0, handle[time % 10], TRUE, FALSE);

}



//----------------------------------------------------------------------
//! @brief 顎の描画処理
//!
//! @param[x] X座標
//! @param[y] Y座標
//! @param[width] 幅
//! @param[height] 高さ
//! @param[space] 顎の開き
//! @param[upperHandle] 上顎の画像
//! @param[lowerHandle] 下顎の画像
//!
//! @return なし
//----------------------------------------------------------------------
void DrawJaw(float x, float y, float width, float height, float spece, HGRP upperHandle, HGRP lowerHandle)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//上顎の描画
	DrawExtendGraphF(x - width / 2, y - (height * 3 / 4) - spece, x + width / 2, y + height / 4 - spece, upperHandle, TRUE);

	//下顎の描画
	DrawExtendGraphF(x - width / 2, y - height / 4 + spece, x + width / 2, y + (height * 3 / 4) + spece, lowerHandle, TRUE);

}



//----------------------------------------------------------------------
//! @brief テキストボックスの描画処理
//!
//! @param[x] X座標
//! @param[y] Y座標
//! @param[width] 幅
//! @param[height] 高さ
//! @param[text] テキスト
//!
//! @return なし
//----------------------------------------------------------------------
void DrawTextBox(float x, float y, float width, float height, char *text)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//枠
	DrawBoxAA(x - width / 2, y - height / 2, x + width / 2, y + height / 2, COLOR_BLACK, TRUE);
	DrawBoxAA(x - width / 2 + 1.0f, y - height / 2 + 1.0f, x + width / 2 - 1.0f, y + height / 2 - 1.0f, COLOR_WHITE, TRUE);

	//テキスト
	DrawStringF(x - width / 2 + 10, y - height / 4, text, COLOR_BLACK);

}
