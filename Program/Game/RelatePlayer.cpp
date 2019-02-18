//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelatePlayer.cpp
//!
//! @brief  プレイヤー関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include <math.h>
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelatePlayer.h"
#include "RelateAnimation.h"
#include "RelateStage.h"
#include "RelateDetectCollition.h"
#include "RelateUI.h"
#include "RelateSpecial.h"

#include "RelateCamera.h"


// 列挙体の定義 ============================================================




// データ型の定義 ==========================================================




// 定数の定義 ==============================================================

// <アニメーション再生速度> -------------------------------------------
// 走る
#define ANIME_SPEED_RUN (0.3f)

// 食べる
#define ANIME_SPEED_EAT (0.5f)

// 剣を振る
#define ANIME_SPEED_SWING (0.5f)

// 暴食
#define ANIME_SPEED_GLUTTONY (1.0f)

// <ステータス> -------------------------------------------------------
// 移動速度
#define MOVE_SPEED (4.0f)

// ジャンプ力
#define JUMP_POWER (20.0f)

// ジャンプ力(特殊能力)
#define SPECIAL_JUMP_POWER (30.0f)

//最大体力量
#define MAX_HP (10)

// グローバル変数の定義 ====================================================

// <プレイヤー> -------------------------------------------------------
ObjectPlayer g_player;

// 数字
HGRP g_numberImage[10];

// 関数のプロトタイプ宣言 ==================================================

//プレイヤーの移動操作
void ManipulateMovingPlayer(ObjectPlayer *player);

//プレイヤーのジャンプ操作
void ManipulateJumpingPlayer(ObjectPlayer *player);

//イートソードを使用
void UseEatsword(ObjectPlayer *player);

//プレイヤーの移動
void MovePlayer(ObjectPlayer *player);

//プレイヤーの移動制限
void LimitAreaPlayer(ObjectPlayer *player);


// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief プレイヤーの初期化処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializePlayer(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//数字
	LoadDivGraph("Resources/Images/数字.png", 10, 5, 2, 32, 32, g_numberImage);

	// <座標>
	g_player.pos.x = (float)SCREEN_CENTER_X / 2;
	g_player.pos.y = (float)(STAGE_SIZE * 13) - (PLAYER_SIZE / 2);

	// <データ上の座標>
	g_player.dataPos.x = (float)SCREEN_CENTER_X / 2;
	g_player.dataPos.y = (float)(STAGE_SIZE * 13) - (PLAYER_SIZE / 2);

	// <速度>
	g_player.vel.x = 0.0f;
	g_player.vel.y = 0.0f;

	// <画像>
	//走る
	LoadDivGraph("Resources/Images/走る.png", 16, 4, 4, 64, 64, g_player.image[RUN].handle);
	g_player.image[RUN].extRate = 1.0f;
	g_player.image[RUN].angle = 0.0f;
	//食べる
	LoadDivGraph("Resources/Images/食べる.png", 16, 4, 4, 128, 128, g_player.image[EAT].handle);
	g_player.image[EAT].extRate = 1.0f;
	g_player.image[EAT].angle = 0.0f;
	//剣を振る
	LoadDivGraph("Resources/Images/剣を振る.png", 16, 4, 4, 128, 128, g_player.image[SWING].handle);
	g_player.image[SWING].extRate = 1.0f;
	g_player.image[SWING].angle = 0.0f;
	//飛行
	LoadDivGraph("Resources/Images/Fly.png", 4, 4, 1, 64, 64, g_player.image[FLYING].handle);
	g_player.image[FLYING].extRate = 0.8f;
	g_player.image[FLYING].angle = 0.0f;
	//暴食
	LoadDivGraph("Resources/Images/食べる2.png", 16, 4, 4, 384, 384, g_player.image[GLUTTONY].handle);
	g_player.image[GLUTTONY].extRate = 1.0f;
	g_player.image[GLUTTONY].angle = 0.0f;

	// <アニメーション>
	//走る
	g_player.animation[RUN].numFrames = 15;
	g_player.animation[RUN].frameDuration = (int)((ANIME_SPEED_RUN * 60) / g_player.animation[RUN].numFrames);
	g_player.animation[RUN].frameNum = 0;
	g_player.animation[RUN].elapsedTime = 0;
	g_player.animation[RUN].state = 0;
	//食べる
	g_player.animation[EAT].numFrames = 15;
	g_player.animation[EAT].frameDuration = (int)((ANIME_SPEED_EAT * 60) / g_player.animation[EAT].numFrames);
	g_player.animation[EAT].frameNum = 0;
	g_player.animation[EAT].elapsedTime = 0;
	g_player.animation[EAT].state = 0;
	//剣を振る
	g_player.animation[SWING].numFrames = 15;
	g_player.animation[SWING].frameDuration = (int)((ANIME_SPEED_EAT * 60) / g_player.animation[SWING].numFrames);
	g_player.animation[SWING].frameNum = 0;
	g_player.animation[SWING].elapsedTime = 0;
	g_player.animation[SWING].state = 0;
	//飛行
	g_player.animation[FLYING].numFrames = 3;
	g_player.animation[FLYING].frameDuration = 0;
	g_player.animation[FLYING].frameNum = 0;
	g_player.animation[FLYING].elapsedTime = 0;
	g_player.animation[FLYING].state = 0;
	//暴食
	g_player.animation[GLUTTONY].numFrames = 15;
	g_player.animation[GLUTTONY].frameDuration = (int)((ANIME_SPEED_GLUTTONY * 60) / g_player.animation[GLUTTONY].numFrames);
	g_player.animation[GLUTTONY].frameNum = 0;
	g_player.animation[GLUTTONY].elapsedTime = 0;
	g_player.animation[GLUTTONY].state = 0;

	// <動作>
	g_player.action = RUN;

	// <反転>
	g_player.turn = FALSE;

	// <状態>
	g_player.state = 1;

	// <タイプ>
	g_player.type = NORMAL;

	// <特殊能力の使用時間>
	g_player.count = 0;

	// <体力>
	g_player.hp = MAX_HP;

#if DEBUG
	g_player.type = FLY;
#endif

}



//----------------------------------------------------------------------
//! @brief プレイヤーの更新処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdatePlayer(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	// <プレイヤーの操作>
	if (g_flyFlag == FALSE)
	{
		//移動
		ManipulateMovingPlayer(&g_player);

		//ジャンプ
		ManipulateJumpingPlayer(&g_player);

		//イートソードを使用
		UseEatsword(&g_player);

		//SEの停止
		StopSoundMem(g_playSE[15]);
	}
	else
	{
		//移動
		ManipulateFlyingPlayer(&g_player);

		//SEの再生
		if (CheckSoundMem(g_playSE[15]) != 1)
		{
			PlaySoundMem(g_playSE[15], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	//特殊能力を使用
	UseSpecialPower(&g_player);


	// <プレイヤーの動作更新>
	//移動
	MovePlayer(&g_player);

	//移動制限
	LimitAreaPlayer(&g_player);

	// <アニメーションの更新>
	UpdataAnimation(&g_player.animation[g_player.action]);

	//体力切れ
	if (g_player.hp <= 0)
	{
		g_player.state = 0;
	}

}



//----------------------------------------------------------------------
//! @brief プレイヤーの描画処理
//!
//! @param[in] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RendarPlayer(void)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	// <プレイヤー> -----------------------------------------------

	//HPゲージの描画
	DrawHPGauge(10.0f, 10.0f, 200.0f, 30.0f, MAX_HP, g_player.hp);

	//タイマーの描画
	DrawTimer((float)SCREEN_CENTER_X, 50.0f, (int)g_player.count / 60, g_numberImage, g_player.type);

	//プレイヤーが使用されている
	if (g_player.state == 1)
	{
		switch (g_player.action)
		{
		case RUN:
			DrawRotaGraphF(g_player.pos.x, g_player.pos.y,
				g_player.image[g_player.action].extRate,
				g_player.image[g_player.action].angle,
				g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
				TRUE, g_player.turn);
			break;
		case EAT:
			//反転した際の座標の修正
			if (g_player.turn == TRUE)
			{
				DrawRotaGraphF(g_player.pos.x - PLAYER_SIZE / 2, g_player.pos.y,
					g_player.image[g_player.action].extRate,
					g_player.image[g_player.action].angle,
					g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
					TRUE, g_player.turn);
			}
			else
			{
				DrawRotaGraphF(g_player.pos.x + PLAYER_SIZE / 2, g_player.pos.y,
					g_player.image[g_player.action].extRate,
					g_player.image[g_player.action].angle,
					g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
					TRUE, g_player.turn);
			}
			break;
		case SWING:
			DrawRotaGraphF(g_player.pos.x, g_player.pos.y,
				g_player.image[g_player.action].extRate,
				g_player.image[g_player.action].angle,
				g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
				TRUE, g_player.turn);
			break;
		case FLYING:
			DrawRotaGraphF(g_player.pos.x, g_player.pos.y,
				g_player.image[g_player.action].extRate,
				g_player.image[g_player.action].angle,
				g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
				TRUE, g_player.turn);
			break;
		case GLUTTONY:
			//反転した際の座標の修正
			if (g_player.turn == TRUE)
			{
				DrawRotaGraphF(g_player.pos.x - PLAYER_SIZE * 2, g_player.pos.y - 160.0f,
					g_player.image[g_player.action].extRate,
					g_player.image[g_player.action].angle,
					g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
					TRUE, g_player.turn);
			}
			else
			{
				DrawRotaGraphF(g_player.pos.x + PLAYER_SIZE * 2, g_player.pos.y - 160.0f,
					g_player.image[g_player.action].extRate,
					g_player.image[g_player.action].angle,
					g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
					TRUE, g_player.turn);
			}
			break;
		default:

			break;
		}
		
	}


	// <デバッグ情報> ---------------------------------------------
#if DEBUG
	//プレイヤーの座標
	DrawCircleAA(g_player.pos.x, g_player.pos.y, 2.0f, 100, COLOR_RED, TRUE);
	DrawFormatString(0, 0, COLOR_RED, "posX=%f\nposY=%f\ndataX=%f\ndataY=%f\ncamera=%f", g_player.pos.x, g_player.pos.y, g_player.dataPos.x, g_player.dataPos.y,g_cameraPos.x);
#endif

}



//----------------------------------------------------------------------
//! @brief プレイヤーの移動操作の処理
//!
//! @param[player] 操作するプレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void ManipulateMovingPlayer(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------
	



	//ローカル変数の初期化//--------------------------------------------
	



	//処理の内容//------------------------------------------------------

	//プレイヤーが使用されている
	if (player->state == 1)
	{
		//速度の初期化
		player->vel.x = 0.0f;

		//アクションが行われていない
		if ((player->animation[EAT].state | player->animation[SWING].state | player->animation[GLUTTONY].state) == 0)
		{
			//キー入力
			if (((g_currentInputState)&PAD_INPUT_LEFT) != 0)	//左キー
			{
				//速度を与える
				player->vel.x = -MOVE_SPEED;

				//画像を反転
				player->turn = TRUE;

				//アニメーションを開始
				player->action = RUN;
				player->animation[RUN].state = 1;
			}
			else if (((g_currentInputState)&PAD_INPUT_RIGHT) != 0)	//右キー
			{
				//速度を与える
				player->vel.x = MOVE_SPEED;

				//画像を反転
				player->turn = FALSE;

				//アニメーションを開始
				player->action = RUN;
				player->animation[RUN].state = 1;
			}
			else
			{
				//アニメーションをリセット
				ResetAnimation(&player->animation[RUN]);
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief プレイヤーのジャンプ操作の処理
//!
//! @param[player] 操作するプレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void ManipulateJumpingPlayer(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------
	// <ジャンプ>
	// フラグ
	static BOOL jumpFlag = FALSE;

	// 速度
	static float jumpSpeed;


	int i;

	//当たり判定の結果
	BOOL result;

	float playerX;
	float playerY;
	float width;
	float height;
	float boxX;
	float boxY;


	//ローカル変数の初期化//--------------------------------------------
	



	//処理の内容//------------------------------------------------------

	// ジャンプの終了
	for (i = 0; i < g_stageObjectNumber; i++)
	{
		if (g_objectStage[i].state == 1)
		{
			playerX = player->dataPos.x;
			playerY = player->dataPos.y;
			width = PLAYER_SIZE / 4;
			height = PLAYER_SIZE;
			boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
			boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

			result = DetectCollisionBoxAndBox(playerX, playerY, width, height, boxX, boxY, STAGE_SIZE, STAGE_SIZE);

			if (result == TRUE)
			{
				if (playerY <= boxY)
				{
					//ジャンプ可能にする
					jumpFlag = FALSE;

					//ジャンプ力をなくす
					jumpSpeed = 0.0f;
				}
			}
		}
	}

	// ジャンプの開始
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_UP) != 0)	//上キー
	{
		//ジャンプしていない
		if (jumpFlag == FALSE)
		{
			//ジャンプ開始
			jumpFlag = TRUE;
			
			//ジャンプ力を与える
			jumpSpeed = JUMP_POWER;

			//SEの再生
			PlaySoundMem(g_playSE[4], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	// ジャンプ中の処理
	if (jumpFlag == TRUE)
	{
		//アニメーションをリセット
		ResetAnimation(player->animation);

		//速度を与える
		player->vel.y = -jumpSpeed;

		//減速
		jumpSpeed--;

		//アニメーションをリセット
		ResetAnimation(&player->animation[RUN]);
	}

}



//----------------------------------------------------------------------
//! @brief イートソードの使用処理
//!
//! @param[player] プレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void UseEatsword(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------
	



	//ローカル変数の初期化//--------------------------------------------
	



	//処理の内容//------------------------------------------------------

	//イートソードが使用されていない
	if ((player->animation[EAT].state | player->animation[SWING].state | player->animation[GLUTTONY].state) == 0)
	{
		//イートソードを使用
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_1) != 0)	//Zキー
		{
			player->action = EAT;
			player->animation[EAT].state = 1;
		}
	}

}



//----------------------------------------------------------------------
//! @brief プレイヤーの移動処理
//!
//! @param[player] 移動するプレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void MovePlayer(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------




	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------

	//飛行していない
	if (g_flyFlag == FALSE)
	{
		//落下
		player->vel.y += GRAVITY;

		//落下速度の制限
		if (player->vel.y >= MAX_FALL_SPEED)
		{
			player->vel.y = MAX_FALL_SPEED;
		}
	}
	else
	{
		//最大速度
		//X成分
		if (player->vel.x >= MOVE_SPEED)
		{
			player->vel.x = MOVE_SPEED;
		}
		if (player->vel.x <= -MOVE_SPEED)
		{
			player->vel.x = -MOVE_SPEED;
		}
		//Y成分
		if (player->vel.y >= MOVE_SPEED)
		{
			player->vel.y = MOVE_SPEED;
		}
		if (player->vel.y <= -MOVE_SPEED)
		{
			player->vel.y = -MOVE_SPEED;
		}
	}


	//アクションが行われている
	if ((player->animation[EAT].state | player->animation[SWING].state | player->animation[GLUTTONY].state) == 1)
	{
		//移動を停止
		player->vel.x = 0.0f;
		player->vel.y = 0.0f;
	}

	//座標の更新
	if (player->dataPos.x < SCREEN_CENTER_X / 2)
	{
		player->pos.x += player->vel.x;
	}
	player->pos.y += player->vel.y;
	if (player->dataPos.x >= SCREEN_LEFT + PLAYER_SIZE / 3)
	{
		player->dataPos.x += player->vel.x;
	}
	
	player->dataPos.y += player->vel.y;

	//SEの再生
	if (player->animation[RUN].state == 1)
	{
		if (CheckSoundMem(g_playSE[3]) == 0)
		{
			PlaySoundMem(g_playSE[3], DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else
	{
		//SEの停止
		StopSoundMem(g_playSE[3]);
	}

}



//----------------------------------------------------------------------
//! @brief プレイヤーの移動制限処理
//!
//! @param[player] 移動制限するプレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void LimitAreaPlayer(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------
	int i;

	//当たり判定の結果
	BOOL result;

	float playerX;
	float playerY;
	float width;
	float height;
	float boxX;
	float boxY;


	//ローカル変数の初期化//--------------------------------------------
	
	


	//処理の内容//------------------------------------------------------

	//プレイヤーの座標が判定のあるオブジェクトだった場合
	for (i = 0; i < g_stageObjectNumber; i++)
	{
		if (g_objectStage[i].state == 1)
		{
			if (player->turn == false)
			{
				//右
				playerX = player->dataPos.x + PLAYER_SIZE / 3;
				playerY = player->dataPos.y;
				boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
				boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

				result = DetectCollisionBoxAndPoint(boxX, boxY, STAGE_SIZE, STAGE_SIZE, playerX, playerY);

				if (result == TRUE)
				{
					player->dataPos.x -= player->vel.x;
					player->vel.x = 0.0f;
				}
			}
			else
			{
				//左
				playerX = player->dataPos.x - PLAYER_SIZE / 3;
				playerY = player->dataPos.y;
				boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
				boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

				result = DetectCollisionBoxAndPoint(boxX, boxY, STAGE_SIZE, STAGE_SIZE, playerX, playerY);

				if (result == TRUE)
				{
					player->dataPos.x -= player->vel.x;
					player->vel.x = 0.0f;
				}
			}
			

			playerX = player->dataPos.x;
			playerY = player->dataPos.y;
			width = PLAYER_SIZE / 4;
			height = PLAYER_SIZE;
			boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
			boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

			result = DetectCollisionBoxAndBox(playerX, playerY, width, height, boxX, boxY, STAGE_SIZE, STAGE_SIZE);

			if (result == TRUE)
			{
				//上
				if (playerY <= boxY)
				{
					player->pos.y = g_objectStage[i].pos.y - STAGE_SIZE;
					player->dataPos.y = g_objectStage[i].pos.y - STAGE_SIZE;
					player->vel.y = 0.0f;
				}
				//下
				else
				{
					player->pos.y = g_objectStage[i].pos.y + STAGE_SIZE * 2;
					player->dataPos.y = g_objectStage[i].pos.y + STAGE_SIZE * 2;
					player->vel.y = 0.0f;
				}
			}
		}
	}

	//画面上での移動制限
	if (player->pos.x < SCREEN_LEFT + PLAYER_SIZE / 3)
	{
		player->pos.x = SCREEN_LEFT + PLAYER_SIZE / 3;
	}
	if (player->dataPos.x < SCREEN_LEFT + PLAYER_SIZE / 3)
	{
		player->dataPos.x = SCREEN_LEFT + PLAYER_SIZE / 3;
	}

	//落ちた場合
	if (player->pos.y >= SCREEN_BOTTOM + PLAYER_SIZE)
	{
		player->state = 0;
	}

	// <デバッグ情報> ------------------------------
#if DEBUG
	//DrawFormatString(0, 0, COLOR_RED, "stageDataT=%d\nstageDataB=%d", g_stageData[arrayPosT][arrayPosX], g_stageData[arrayPosB][arrayPosX]);
#endif

}
