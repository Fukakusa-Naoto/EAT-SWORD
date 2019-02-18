//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateSpecial.cpp
//!
//! @brief  特殊能力関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include <math.h>
#include "GameMain.h"
#include "RelateSpecial.h"
#include "RelateBullet.h"
#include "RelatePlayer.h"
#include "RelateAnimation.h"


// データ型の定義 ==========================================================




// 定数の定義 ==============================================================
//加速度
#define ACCEL_SPEED (5.0f)

//摩擦係数
#define FRICTION (0.9f)


// グローバル変数の定義 ====================================================
//飛行フラグ
BOOL g_flyFlag;



// 関数のプロトタイプ宣言 ==================================================
//特殊能力 Type-SWORD
void SpecialPowerTypeSword(ObjectPlayer *player);

//特殊能力 Type-FIRE
void SpecialPowerTypeFire(ObjectPlayer *player);

//特殊能力 Type-FLY
void SpecialPowerTypeFly(ObjectPlayer *player);

//特殊能力 Type-BIG
void SpecialPowerTypeBig(ObjectPlayer *player);


// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief 特殊能力の使用処理
//!
//! @param[player] プレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void UseSpecialPower(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------




	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------

	//イートソードが使用されていない
	if (player->animation[EAT].state == 0)
	{
		switch (player->type)
		{
		case NORMAL:	//ノーマル
						//なし
			break;
		case SWORD:		//ソード
			SpecialPowerTypeSword(player);
			break;
		case FIRE:		//ファイア
			SpecialPowerTypeFire(player);
			break;
		case FLY:		//フライ
			SpecialPowerTypeFly(player);
			break;
		case BIG:		//ビッグ
			SpecialPowerTypeBig(player);
			break;
		default:

			break;
		}
	}

#if DEBUG

#else
	//特殊能力の使用時間のカウント
	if (player->type != NORMAL)
	{
		player->count--;
	}

	//特殊能力の時間切れ
	if (player->count <= 0)
	{
		//通常モードに戻す
		player->type = NORMAL;

		if ((player->animation[EAT].state | player->animation[SWING].state | player->animation[GLUTTONY].state) == 0)
		{
			player->action = RUN;
		}

		//アニメーション
		ResetAnimation(&player->animation[SWING]);
	
	}

	//飛行フラグをなくす
	if (player->type != FLY)
	{
		g_flyFlag = FALSE;
	}

#endif
	
}



//----------------------------------------------------------------------
//! @brief 特殊能力 Type-SWORDの処理
//!
//! @param[player] プレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void SpecialPowerTypeSword(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------
	//発射座標
	float pointX;
	float pointY;

	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------
	//特殊能力を使用
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_2) != 0)	//Xキー
	{
		if (player->animation[SWING].state == 0)
		{
			player->action = SWING;
			player->animation[SWING].state = 1;
		}
	}

	//斬撃を撃つ
	if (player->animation[SWING].frameNum == 10)
	{
		if (g_playerBullet.state == 0)
		{
			if (player->turn == FALSE)
			{
				//座標の計算
				pointX = player->dataPos.x + PLAYER_SIZE;
				pointY = player->dataPos.y;

				//発射処理
				ShotBullet(&g_playerBullet, 1, { 0.0f, 0.0f }, pointX, pointY, SPEED_BULLET_PLAYER, NORMAL_SHOT);
			}
			else
			{
				//座標の計算
				pointX = player->dataPos.x - PLAYER_SIZE;
				pointY = player->dataPos.y;

				//発射処理
				ShotBullet(&g_playerBullet, 1, { 0.0f, 0.0f }, pointX, pointY, -SPEED_BULLET_PLAYER, NORMAL_SHOT);
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief 特殊能力 Type-FIREの処理
//!
//! @param[player] プレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void SpecialPowerTypeFire(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------
	



	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------
	//特殊能力を使用
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_2) != 0)	//Xキー
	{
		if (player->animation[SWING].state == 0)
		{
			player->action = SWING;
			player->animation[SWING].state = 1;
		}
	}

}



//----------------------------------------------------------------------
//! @brief 特殊能力 Type-FLYの処理
//!
//! @param[player] プレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void SpecialPowerTypeFly(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------
	


	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------
	//特殊能力を使用
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_2) != 0)	//Xキー
	{
		//飛行モードを切り替える
		if (g_flyFlag == FALSE)
		{
			g_flyFlag = TRUE;
			player->action = FLYING;
			ResetAnimation(&player->animation[RUN]);
		}
		else
		{
			g_flyFlag = FALSE;
			player->action = RUN;
		}
	}

}



//----------------------------------------------------------------------
//! @brief 特殊能力 Type-BIGの処理
//!
//! @param[player] プレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void SpecialPowerTypeBig(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------

	//特殊能力を使用
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_2) != 0)	//Xキー
	{
		player->action = GLUTTONY;
		player->animation[GLUTTONY].state = 1;
	}

}



//----------------------------------------------------------------------
//! @brief 飛行中の操作処理
//!
//! @param[player] プレイヤー
//!
//! @return なし
//----------------------------------------------------------------------
void ManipulateFlyingPlayer(ObjectPlayer *player)
{
	//ローカル変数の宣言//----------------------------------------------
	//キーの入力時間のカウント
	static int count = 0;

	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------

	//プレイヤーが使用されている
	if (player->state == 1)
	{

		//アクションが行われていない
		if ((player->animation[EAT].state | player->animation[SWING].state) == 0)
		{
			//キー入力
			if (((g_currentInputState)&PAD_INPUT_LEFT) != 0)	//左キー
			{
				//カウントを増やす
				count++;

				//速度を与える
				player->vel.x = -ACCEL_SPEED*((float)count / 60);

				//画像を反転
				player->turn = TRUE;
			}
			else if (((g_currentInputState)&PAD_INPUT_RIGHT) != 0)	//右キー
			{
				//カウントを増やす
				count++;

				//速度を与える
				player->vel.x = ACCEL_SPEED*((float)count / 60);

				//画像を反転
				player->turn = FALSE;
			}
			else if (((g_currentInputState)&PAD_INPUT_UP) != 0)	//上キー
			{
				//カウントを増やす
				count++;

				//速度を与える
				player->vel.y = -ACCEL_SPEED*((float)count / 60);
			}
			else if (((g_currentInputState)&PAD_INPUT_DOWN) != 0)	//下キー
			{
				//カウントを増やす
				count++;

				//速度を与える
				player->vel.y = ACCEL_SPEED*((float)count / 60);
			}
			else
			{
				//カウントの初期化
				count = 0;
			}
		}
	}

	//摩擦による減速
	player->vel.x *= FRICTION;
	player->vel.y *= FRICTION;

	//X成分
	if ((player->vel.x <= 0.005) && (player->vel.x >= -0.005))
	{
		player->vel.x = 0.0f;
	}
	//Y成分
	if ((player->vel.y <= 0.005) && (player->vel.y >= -0.005))
	{
		player->vel.y = 0.0f;
	}
	
	//アニメーション
	player->animation[FLYING].frameNum = (int)fabs((double)player->vel.x);
	if (player->animation[FLYING].frameNum >= player->animation[FLYING].numFrames)
	{
		player->animation[FLYING].frameNum = 3;
	}

}