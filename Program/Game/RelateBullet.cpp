//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateBullet.cpp
//!
//! @brief  弾関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ヘッダファイルの読み込み ================================================
#include <math.h>
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelateBullet.h"
#include "RelateCamera.h"


// データ型の定義 ==========================================================




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================

//プレイヤーの弾
ObjectBullet g_playerBullet;

//敵の弾
ObjectBullet g_enemyBullet[MAX_BULLET_ENEMY];

//弾の画像
HGRP g_bulletImage;


// 関数のプロトタイプ宣言 ==================================================
// 通常弾の発射
void ShotNormalBullet(ObjectBullet *bullet, float x, float y, float speed);

// ターゲット狙いの弾の発射
void ShotAimBullet(ObjectBullet *bullet, Vec2D target, float x, float y, float speed);

// 弾の移動
void MoveBullet(ObjectBullet *bullet);



// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief 弾の初期化処理
//!
//! @param[no] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeBullet(void)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------
	//画像の読み込み
	g_bulletImage = LoadGraph("Resources/Images/Slash.png");

	//プレイヤーの弾
	g_playerBullet.pos.x = 0.0f;
	g_playerBullet.pos.y = 0.0f;
	g_playerBullet.vel.x = 0.0f;
	g_playerBullet.vel.y = 0.0f;
	g_playerBullet.image = g_bulletImage;
	g_playerBullet.angle = 0.0f;
	g_playerBullet.turn = FALSE;
	g_playerBullet.state = 0;

	//画像の読み込み
	g_bulletImage = LoadGraph("Resources/Images/Bullet.png");

	//敵の弾
	for (i = 0; i < MAX_BULLET_ENEMY; i++)
	{
		g_enemyBullet[i].pos.x = 0.0f;
		g_enemyBullet[i].pos.y = 0.0f;
		g_enemyBullet[i].vel.x = 0.0f;
		g_enemyBullet[i].vel.y = 0.0f;
		g_enemyBullet[i].image = g_bulletImage;
		g_enemyBullet[i].angle = 0.0f;
		g_enemyBullet[i].turn = FALSE;
		g_enemyBullet[i].state = 0;
	}

}



//----------------------------------------------------------------------
//! @brief 弾の更新処理
//!
//! @param[no] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateBullet(void)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//プレイヤーの弾
	if (g_playerBullet.state == 1)
	{
		MoveBullet(&g_playerBullet);
	}

	//敵の弾
	for (i = 0; i < MAX_BULLET_ENEMY; i++)
	{
		if (g_enemyBullet[i].state == 1)
		{
			MoveBullet(&g_enemyBullet[i]);
		}
	}

}



//----------------------------------------------------------------------
//! @brief 弾の描画処理
//!
//! @param[no] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RendarBullet(void)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//プレイヤーの弾
		if (g_playerBullet.state == 1)
		{
			DrawRotaGraphF(g_playerBullet.pos.x - g_cameraPos.x, g_playerBullet.pos.y, 1.0f, g_playerBullet.angle, g_playerBullet.image, TRUE, g_playerBullet.turn);
		}

	//敵の弾
	for (i = 0; i < MAX_BULLET_ENEMY; i++)
	{
		if (g_enemyBullet[i].state == 1)
		{
			DrawRotaGraphF(g_enemyBullet[i].pos.x - g_cameraPos.x, g_enemyBullet[i].pos.y, 1.0f, g_enemyBullet[i].angle, g_enemyBullet[i].image, TRUE, g_enemyBullet[i].turn);
		}
	}

}



//----------------------------------------------------------------------
//! @brief 弾の発射処理
//!
//! @param[bullet] 弾
//! @param[max] 弾の最大数
//! @param[target] ターゲットの座標
//! @param[x] 発射地点のX座標
//! @param[y] 発射地点のY座標
//! @param[speed] 弾の速度
//! @param[type] 弾の種類
//!
//! @return なし
//----------------------------------------------------------------------
void ShotBullet(ObjectBullet bullet[], int max, Vec2D target, float x, float y, float speed, ShotMeans type)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//弾を調べる
	for (i = 0; i < max; i++)
	{
		if (bullet[i].state == 0)
		{
			switch (type)
			{
			case NORMAL_SHOT:
				ShotNormalBullet(&bullet[i], x, y, speed);
				break;
			case AIM_SHOT:
				ShotAimBullet(&bullet[i], target, x, y, speed);
				break;
			default:

				break;
			}

			//SEの再生
			PlaySoundMem(g_playSE[8], DX_PLAYTYPE_BACK, TRUE);

			break;
		}
	}

}



//----------------------------------------------------------------------
//! @brief 通常弾の発射処理
//!
//! @param[bullet] 弾
//! @param[x] 発射地点のX座標
//! @param[y] 発射地点のY座標
//! @param[speed] 弾の速度
//!
//! @return なし
//----------------------------------------------------------------------
void ShotNormalBullet(ObjectBullet *bullet, float x, float y, float speed)
{
	//ローカル変数の宣言//----------------------------------------------




	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------

	bullet->pos.x = x;
	bullet->pos.y = y;
	bullet->vel.x = speed;
	if (speed > 0)
	{
		bullet->turn = TRUE;
	}
	else
	{
		bullet->turn = FALSE;
	}
	bullet->state = 1;

}



//----------------------------------------------------------------------
//! @brief ターゲット狙いの弾の発射処理
//!
//! @param[bullet] 弾
//! @param[target] ターゲットの座標
//! @param[x] 発射地点のX座標
//! @param[y] 発射地点のY座標
//! @param[speed] 弾の速度
//!
//! @return なし
//----------------------------------------------------------------------
void ShotAimBullet(ObjectBullet *bullet, Vec2D target, float x, float y, float speed)
{
	//ローカル変数の宣言//----------------------------------------------
	//距離
	double dx;
	double dy;

	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	bullet->pos.x = x;
	bullet->pos.y = y;

	//距離を求める
	dx = target.x - bullet->pos.x;
	dy = target.y - bullet->pos.y;

	//角度を求める
	bullet->angle = (float)atan2(dy, dx);

	//速度を与える
	bullet->vel.x = speed*(float)cos(bullet->angle);
	bullet->vel.y = speed*(float)sin(bullet->angle);

	bullet->state = 1;

}



//----------------------------------------------------------------------
//! @brief 弾の移動処理
//!
//! @param[bullet] 弾
//!
//! @return なし
//----------------------------------------------------------------------
void MoveBullet(ObjectBullet *bullet)
{
	//ローカル変数の宣言//----------------------------------------------
	


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//座標の更新
	bullet->pos.x += bullet->vel.x;
	bullet->pos.y += bullet->vel.y;

	//弾の消滅
	if ((bullet->pos.x<g_cameraPos.x) || (bullet->pos.x>g_cameraPos.x + CAMERA_WIDTH)
		|| (bullet->pos.y<g_cameraPos.y) || (bullet->pos.y>g_cameraPos.y + CAMERA_HEIGHT))
	{
		bullet->state = 0;
	}

}
