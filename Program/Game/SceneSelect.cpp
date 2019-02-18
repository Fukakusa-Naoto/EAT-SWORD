//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneSelect.cpp
//!
//! @brief  セレクトシーン関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include <math.h>
#include "GameMain.h"
#include "SceneSelect.h"
#include "RelateAnimation.h"
#include "RelateStage.h"
#include "RelateDetectCollition.h"


// データ型の定義 ==========================================================
//ObjectCursor型
struct Tag_ObjectCursor
{
	Vec2D pos;
	float range;
};
typedef struct Tag_ObjectCursor ObjectCursor;

//ObjectChar型
struct Tag_ObjectChar
{
	Vec2D pos;
	Vec2D vel;
	Image image;
	Animation animation;
	BOOL turn;
};
typedef struct Tag_ObjectChar ObjectChar;


// 定数の定義 ==============================================================

//キャラクターの移動速度
#define MOVE_SPEED (2.0f)


// グローバル変数の定義 ====================================================

//画像
HGRP g_selectImage;

//カーソル
ObjectCursor g_cursor;

//キャラクター
ObjectChar g_character;

//サウンド
//BGM
HSND g_selectBGM;
//SE
HSND g_selectSE[2];


// 関数のプロトタイプ宣言 ==================================================

//カーソルの移動
void MoveCharacter(ObjectChar *character, Vec2D target);


// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief セレクトシーンの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeSelect(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//画像の読み込み
	g_selectImage = LoadGraph("Resources/Images/SELECT.png");

	if (g_stageId == 5)
	{
		g_stageId = 0;
	}

	//カーソル
	g_cursor.pos.x = 70.0f;
	g_cursor.pos.y = 230.0f;
	g_cursor.range = 5.0f;

	//キャラクター
	g_character.pos.x = 70.0f;
	g_character.pos.y = 230.0f;
	g_character.vel.x = 0.0f;
	g_character.vel.y = 0.0f;
	LoadDivGraph("Resources/Images/走る.png", 16, 4, 4, 64, 64, g_character.image.handle);
	g_character.image.extRate = 1.0f;
	g_character.image.angle = 0.0f;
	g_character.animation.numFrames = 15;
	g_character.animation.frameDuration = (int)((0.3 * 60) / g_character.animation.numFrames);
	g_character.animation.frameNum = 0;
	g_character.animation.elapsedTime = 0;
	g_character.animation.state = 0;
	g_character.turn = FALSE;

	//サウンド
	//BGM
	g_selectBGM = LoadSoundMem("Resources/Sounds/Select_BGM.mp3");
	//SE
	g_selectSE[0] = LoadSoundMem("Resources/Sounds/Move_SE.mp3");
	g_selectSE[1] = LoadSoundMem("Resources/Sounds/decision_SE.mp3");

}



//----------------------------------------------------------------------
//! @brief セレクトシーンの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateSelect(void)
{
	//ローカル変数の宣言//----------------------------------------------
	static BOOL selectFlag = FALSE;
	static BOOL moveFlag = FALSE;

	BOOL result;

	static int verticalPos = 1;
	static int horizontalPos = 0;

	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//キー入力
	if ((selectFlag|moveFlag) == FALSE)
	{
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_LEFT) != 0)	//左キー
		{
			horizontalPos--;
			g_character.turn = TRUE;
			moveFlag = TRUE;
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_RIGHT) != 0)	//右キー
		{
			horizontalPos++;
			g_character.turn = FALSE;
			moveFlag = TRUE;
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_UP) != 0)	//上キー
		{
			verticalPos--;
			moveFlag = TRUE;
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_DOWN) != 0)	//下キー
		{
			verticalPos++;
			moveFlag = TRUE;
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_1) != 0)	//Zキー
		{
			selectFlag = TRUE;
			//SEの再生
			PlaySoundMem(g_selectSE[1], DX_PLAYTYPE_BACK, TRUE);
		}
	}
	
	//カーソルの座標の更新
	g_cursor.pos.x = 70.0f + (130.0f * (float)horizontalPos);
	g_cursor.pos.y = 80.0f + (150.0f*(float)verticalPos);

	//キャラクターの移動および移動制限
	result = DetectCollisionBoxAndPoint(g_cursor.pos.x, g_cursor.pos.y, g_cursor.range, g_cursor.range, g_character.pos.x, g_character.pos.y);
	if (result == TRUE)
	{
		//移動を中止
		moveFlag = FALSE;
		//座標を固定
		g_character.pos = g_cursor.pos;
		//速度をなくす
		g_character.vel.x = g_character.vel.y = 0.0f;
		//アニメーションの停止
		ResetAnimation(&g_character.animation);
		//SEの停止
		StopSoundMem(g_selectSE[0]);
	}
	else
	{
		//移動中
		moveFlag = TRUE;

		//キャラクターを移動
		MoveCharacter(&g_character, g_cursor.pos);
		//アニメーションを再生
		if (g_character.animation.state == 0)
		{
			g_character.animation.state = 1;
		}
		//SEの再生
		if (CheckSoundMem(g_selectSE[0]) == 0)
		{
			PlaySoundMem(g_selectSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
	}


	// <アニメーション>
	//アニメーションの更新
	UpdataAnimation(&g_character.animation);

	//カーソルの制限
	//横
	if (horizontalPos <= 0)
	{
		horizontalPos = 0;
	}
	switch (verticalPos)
	{
	case 0:
		if (horizontalPos >= 1)
		{
			horizontalPos = 1;
		}
		break;
	case 1:
		if (horizontalPos >= 4)
		{
			horizontalPos = 4;
		}
		break;
	case 2:
		if (horizontalPos != 0)
		{
			horizontalPos = 0;
		}
		break;
	default:

		break;
	}
	//縦
	if (verticalPos <= 0)
	{
		verticalPos = 0;
	}
	if (verticalPos >= 2)
	{
		verticalPos = 2;
	}

	//シーンの移動
	if ((selectFlag&~moveFlag) == TRUE)
	{
		switch (verticalPos)
		{
		case 0:
			switch (horizontalPos)
			{
			case 0:
				g_stageId = 5;
				break;
			case 1:
				g_stageId = 6;
				break;
			default:

				break;
			}
			//プレイシーンへ
			ChangeScene(SCENE_PLAYING);
			break;
		case 1:
			switch (horizontalPos)
			{
			case 0:
				g_stageId = 0;
				break;
			case 1:
				g_stageId = 1;
				break;
			case 2:
				g_stageId = 2;
				break;
			case 3:
				g_stageId = 3;
				break;
			case 4:
				g_stageId = 4;
				break;
			default:

				break;
			}
			//プレイシーンへ
			ChangeScene(SCENE_PLAYING);
			break;
		case 2:
			//タイトルシーンへ
			ChangeScene(SCENE_TITLE);
			break;
		default:

			break;
		}

		selectFlag = FALSE;
	}

#if DEBUG

#else
	//BGMの再生
	if (CheckSoundMem(g_selectBGM) == 0)
	{
		PlaySoundMem(g_selectBGM, DX_PLAYTYPE_BACK, TRUE);
	}
#endif

}



//----------------------------------------------------------------------
//! @brief セレクトシーンの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RenderSelect(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//背景の描画
	DrawBox(SCREEN_LEFT, SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_WHITE, TRUE);

	//ステージ画像の描画
	DrawGraph(SCREEN_LEFT, SCREEN_TOP - 15, g_selectImage, TRUE);

	//カーソルの描画
	DrawRotaGraphF(g_character.pos.x, g_character.pos.y,
		g_character.image.extRate,
		g_character.image.angle,
		g_character.image.handle[g_character.animation.frameNum],
		TRUE, g_character.turn);


	//デバッグ情報
#if DEBUG
	DrawBoxAA(g_cursor.pos.x - g_cursor.range / 2, g_cursor.pos.y - g_cursor.range / 2, g_cursor.pos.x + g_cursor.range / 2, g_cursor.pos.y + g_cursor.range / 2, COLOR_RED, FALSE);

	DrawCircleAA(g_character.pos.x, g_character.pos.y, 1.0f, 100, COLOR_RED);
#endif

}



//----------------------------------------------------------------------
//! @brief セレクトシーンの終了処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void FinalizeSelect(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//画像データの削除
	InitGraph();

	//音データの削除
	InitSoundMem();

}



//----------------------------------------------------------------------
//! @brief キャラクターの追従移動処理
//!
//! @param[character] 移動させるキャラクター
//! @param[target] 目標
//!
//! @return なし
//----------------------------------------------------------------------
void MoveCharacter(ObjectChar *character,Vec2D target)
{
	//ローカル変数の宣言//----------------------------------------------
	float dx;
	float dy;
	float angle;


	//ローカル変数の初期化//--------------------------------------------
	//距離
	dx = target.x - character->pos.x;
	dy = target.y - character->pos.y;

	//角度
	angle = (float)atan2((double)dy, (double)dx);


	//処理の内容//------------------------------------------------------
	//速度を与える
	character->vel.x = MOVE_SPEED*(float)cos((double)angle);
	character->vel.y = MOVE_SPEED*(float)sin((double)angle);

	//向きの変更
	if (character->vel.x < 0)
	{
		character->turn = TRUE;
	}
	if (character->vel.x > 0)
	{
		character->turn = FALSE;
	}
	
	//座標の更新
	character->pos.x += character->vel.x;
	character->pos.y += character->vel.y;

}