//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateDetectCollition.cpp
//!
//! @brief  衝突判定関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
// ヘッダファイルの読み込み ================================================
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelateDetectCollition.h"
#include "RelatePlayer.h"
#include "RelateEnemy.h"
#include "RelateCamera.h"
#include "RelateStage.h"
#include "RelateBullet.h"


// 列挙体の定義 ============================================================




// データ型の定義 ==========================================================




// 定数の定義 ==============================================================




// グローバル変数の定義 ====================================================




// 関数のプロトタイプ宣言 ==================================================

//プレイヤーと敵の当たり判定
void DetectCollisionPlayerAndEnemy(ObjectPlayer *player,ObjectEnemy *enemy);

//剣と敵との当たり判定
void DetectCollisionSwordAndEnemy(ObjectPlayer *player, ObjectEnemy *enemy);

//剣とステージオブジェクトとの当たり判定
void DetectCollisionSwordAndObject(ObjectPlayer *player, ObjectStage *stage);

//自機と敵の弾との当たり判定
void DetectCollisionPlayerAndBullet(ObjectPlayer *player, ObjectBullet *bullet);

//敵と自機の弾との当たり判定
void DetectCollisionEnemyAndBullet(ObjectEnemy *enemy, ObjectBullet *bullet);

//プレイヤーの弾とステージオブジェクトとの当たり判定
void DetectCollisionPlayerBulletAndObject(ObjectBullet *bullet, ObjectStage *stage);

//敵の弾とステージオブジェクトとの当たり判定
void DetectCollisionEnemyBulletAndObject(ObjectBullet *bullet, ObjectStage *stage);

//矩形同士の当たり判定
BOOL DetectCollisionBoxAndBox(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);

//矩形と点の当たり判定
BOOL DetectCollisionBoxAndPoint(float boxX, float boxY, float width, float height, float pointX, float pointY);


// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief 全ての当たり判定処理
//!
//! @param[no] なし
//!
//! @return なし
//----------------------------------------------------------------------
void AllDetectCollision(void)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;
	int j;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	if (g_player.state == 1)
	{
		//敵
		for (i = 0; i < MAX_ENEMY; i++)
		{
			if ((g_enemies[i].state == 1) && (g_enemies[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + ENEMY_SIZE))
			{
				//プレイヤーと敵との当たり判定
				DetectCollisionPlayerAndEnemy(&g_player, &g_enemies[i]);

				//剣と敵との当たり判定
				DetectCollisionSwordAndEnemy(&g_player, &g_enemies[i]);
			}
		}

		//ステージ
		for (i = 0; i < g_stageObjectNumber; i++)
		{
			if (g_objectStage[i].state == 1)
			{
				if ((g_objectStage[i].pos.x >= g_cameraPos.x - STAGE_SIZE) && (g_objectStage[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + STAGE_SIZE))
				{
					DetectCollisionSwordAndObject(&g_player, &g_objectStage[i]);
				}
			}
		}

		//敵の弾
		for (i = 0; i < MAX_BULLET_ENEMY; i++)
		{
			if (g_enemyBullet[i].state == 1)
			{
				DetectCollisionPlayerAndBullet(&g_player, &g_enemyBullet[i]);
			}
		}

		// <弾>
		//自機
		if (g_playerBullet.state == 1)
		{
			//敵
			for (j = 0; j < MAX_ENEMY; j++)
			{
				if ((g_enemies[j].state == 1) && (g_enemies[j].pos.x <= g_cameraPos.x + CAMERA_WIDTH + ENEMY_SIZE))
				{
					DetectCollisionEnemyAndBullet(&g_enemies[j], &g_playerBullet);
				}
			}

			//ステージ
			for (j = 0; j < g_stageObjectNumber; j++)
			{
				if (g_objectStage[j].state == 1)
				{
					if ((g_objectStage[j].pos.x >= g_cameraPos.x - STAGE_SIZE) && (g_objectStage[j].pos.x <= g_cameraPos.x + CAMERA_WIDTH + STAGE_SIZE))
					{
						DetectCollisionPlayerBulletAndObject(&g_playerBullet, &g_objectStage[j]);
					}
				}
			}
		}


		//敵
		for (i = 0; i < MAX_BULLET_ENEMY; i++)
		{
			if (g_enemyBullet[i].state == 1)
			{
				//ステージ
				for (j = 0; j < g_stageObjectNumber; j++)
				{
					if (g_objectStage[j].state == 1)
					{
						if ((g_objectStage[j].pos.x >= g_cameraPos.x - STAGE_SIZE) && (g_objectStage[j].pos.x <= g_cameraPos.x + CAMERA_WIDTH + STAGE_SIZE))
						{
							DetectCollisionEnemyBulletAndObject(&g_enemyBullet[i], &g_objectStage[j]);
						}
					}
				}
			}
		}
	}
}



//----------------------------------------------------------------------
//! @brief プレイヤーと敵との当たり判定処理
//!
//! @param[player] プレイヤー
//! @param[enemy] 敵
//!
//! @return なし
//----------------------------------------------------------------------
void DetectCollisionPlayerAndEnemy(ObjectPlayer *player, ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------
	//当たり判定の結果
	BOOL result;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------
	//当たり判定
	result = DetectCollisionBoxAndBox(player->dataPos.x, player->dataPos.y, (float)PLAYER_SIZE / 3, (float)PLAYER_SIZE, enemy->pos.x, enemy->pos.y, (float)ENEMY_SIZE * enemy->extRate, (float)ENEMY_SIZE * enemy->extRate);

	if (result == TRUE)
	{
#if DEBUG
		
#else
		player->hp--;
#endif
		enemy->state = 0;

		//SEの再生
		PlaySoundMem(g_playSE[2], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief 剣と敵との当たり判定処理
//!
//! @param[player] プレイヤー
//! @param[enemy] 敵
//!
//! @return なし
//----------------------------------------------------------------------
void DetectCollisionSwordAndEnemy(ObjectPlayer *player, ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------
	//当たり判定の結果
	BOOL result;

	//剣の座標
	float swordPosX;
	float swordPosY;

	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	// ノーマル //
	//座標の計算
	if (player->turn == TRUE)
	{
		swordPosX = player->dataPos.x - PLAYER_SIZE;
		swordPosY = player->dataPos.y;
	}
	else
	{
		swordPosX = player->dataPos.x + PLAYER_SIZE;
		swordPosY = player->dataPos.y;
	}

	result = DetectCollisionBoxAndPoint(swordPosX, swordPosY, (float)PLAYER_SIZE, (float)PLAYER_SIZE, enemy->pos.x, enemy->pos.y);

	if ((result == TRUE) && (player->animation[EAT].frameNum >= 10) && (player->animation[EAT].frameNum <= 13))
	{
		switch (enemy->type)
		{
		case NORMAL:	//ノーマル
			//なし
			break;
		case SWORD:		//ソード
			player->type = SWORD;
			player->count = TIME_SPECIAL;
			break;
		case FIRE:		//ファイア
			player->type = FIRE;
			player->count = TIME_SPECIAL;
			break;
		case FLY:		//フライ
			player->type = FLY;
			player->count = TIME_SPECIAL;
			break;
		case BIG:		//ビッグ
			player->type = BIG;
			player->count = TIME_SPECIAL;
			break;
		default:

			break;
		}

		enemy->state = 0;

		//SEの再生
		PlaySoundMem(g_playSE[10], DX_PLAYTYPE_BACK, TRUE);
	}

	// 暴食 //
	//座標の計算
	if (player->turn == TRUE)
	{
		swordPosX = player->dataPos.x - (float)STAGE_SIZE * 3.5f;
		swordPosY = player->dataPos.y - (float)STAGE_SIZE * 3.0f;
	}
	else
	{
		swordPosX = player->dataPos.x + (float)STAGE_SIZE * 3.5f;
		swordPosY = player->dataPos.y - (float)STAGE_SIZE * 3.0f;
	}

	//当たり判定
	result = DetectCollisionBoxAndPoint(swordPosX, swordPosY, (float)STAGE_SIZE * 7, (float)STAGE_SIZE * 8, enemy->pos.x, enemy->pos.y);

	if ((result == TRUE) && (player->animation[GLUTTONY].frameNum >= 10) && (player->animation[GLUTTONY].frameNum <= 13))
	{
		enemy->state = 0;

		//SEの再生
		PlaySoundMem(g_playSE[11], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief 剣とステージオブジェクトとの当たり判定処理
//!
//! @param[player] プレイヤー
//! @param[stage] ステージオブジェクト
//!
//! @return なし
//----------------------------------------------------------------------
void DetectCollisionSwordAndObject(ObjectPlayer *player, ObjectStage *stage)
{
	//ローカル変数の宣言//----------------------------------------------
	//当たり判定の結果
	BOOL result;

	//剣の座標
	float swordPosX;
	float swordPosY;

	//ステージオブジェクトの座標
	float stageX;
	float stageY;

	//配列に使用
	int i;

	//ローカル変数の初期化//--------------------------------------------
	stageX = stage->pos.x + STAGE_SIZE / 2;
	stageY = stage->pos.y + STAGE_SIZE / 2;


	//処理の内容//------------------------------------------------------

	// ノーマル //
	//座標の計算
	if (player->turn == TRUE)
	{
		swordPosX = player->dataPos.x - PLAYER_SIZE;
		swordPosY = player->dataPos.y;
	}
	else
	{
		swordPosX = player->dataPos.x + PLAYER_SIZE;
		swordPosY = player->dataPos.y;
	}

	result = DetectCollisionBoxAndBox(swordPosX, swordPosY, (float)STAGE_SIZE, (float)STAGE_SIZE * 3, stageX, stageY, (float)STAGE_SIZE, (float)STAGE_SIZE);

	if (result == TRUE)
	{
		if ((player->animation[EAT].frameNum >= 10) && (player->animation[EAT].frameNum <= 13))
		{
			if (stage->type == 2)
			{
				stage->state = 0;

				//SEの再生
				PlaySoundMem(g_playSE[10], DX_PLAYTYPE_BACK, TRUE);
			}
		}
	}

	// 炎剣 //
	if (player->type == FIRE)
	{
		//座標の計算
		if (player->turn == TRUE)
		{
			swordPosX = player->dataPos.x - PLAYER_SIZE / 2;
			swordPosY = player->dataPos.y;
		}
		else
		{
			swordPosX = player->dataPos.x + PLAYER_SIZE / 2;
			swordPosY = player->dataPos.y;
		}

		//当たり判定
		result = DetectCollisionBoxAndBox(swordPosX, swordPosY, (float)PLAYER_SIZE / 2, (float)PLAYER_SIZE / 2, stageX, stageY, (float)STAGE_SIZE, (float)STAGE_SIZE);

		if (result == TRUE)
		{
			if ((player->animation[SWING].frameNum >= 8) && (player->animation[SWING].frameNum <= 12))
			{
				if (stage->type == 3)
				{
					//エフェクトを出現
					for (i = 0; i < 100; i++)
					{
						if (g_stageAnimation[i].animation.state == 0)
						{
							g_stageAnimation[i].pos = stage->pos;
							g_stageAnimation[i].animation.state = 1;

							//SEの再生
							PlaySoundMem(g_playSE[16], DX_PLAYTYPE_BACK, TRUE);
							
							break;
						}
					}
				}
			}
		}
	}
	
	//オブジェクトの消滅
	for (i = 0; i < 100; i++)
	{
		if ((g_stageAnimation[i].pos.x == stage->pos.x) && (g_stageAnimation[i].pos.y == stage->pos.y))
		{
			if (g_stageAnimation[i].animation.state == 0)
			{
				stage->state = 0;
			}
		}
	}
	
	// 暴食 //
	//座標の計算
	if (player->turn == TRUE)
	{
		swordPosX = player->dataPos.x - (float)STAGE_SIZE * 4.0f;
		swordPosY = player->dataPos.y - (float)STAGE_SIZE * 3.0f;
	}
	else
	{
		swordPosX = player->dataPos.x + (float)STAGE_SIZE * 4.0f;
		swordPosY = player->dataPos.y - (float)STAGE_SIZE * 3.0f;
	}

	result = DetectCollisionBoxAndBox(swordPosX, swordPosY, (float)STAGE_SIZE * 7, (float)STAGE_SIZE * 8, stageX, stageY, (float)STAGE_SIZE, (float)STAGE_SIZE);

	if (result == TRUE)
	{
		if ((player->animation[GLUTTONY].frameNum >= 10) && (player->animation[GLUTTONY].frameNum <= 13))
		{
			if (stage->type == 2)
			{
				stage->state = 0;
				//SEの再生
				PlaySoundMem(g_playSE[11], DX_PLAYTYPE_BACK, TRUE);
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief プレイヤーと敵の弾との当たり判定処理
//!
//! @param[player] プレイヤー
//! @param[bullet] 弾
//!
//! @return なし
//----------------------------------------------------------------------
void DetectCollisionPlayerAndBullet(ObjectPlayer *player, ObjectBullet *bullet)
{
	//ローカル変数の宣言//----------------------------------------------
	//当たり判定の結果
	BOOL result;

	//プレイヤーの座標
	float playerPosX;
	float playerPosY;

	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//座標の計算
	playerPosX = player->dataPos.x;
	playerPosY = player->dataPos.y;

	result = DetectCollisionBoxAndBox(playerPosX, playerPosY, (float)PLAYER_SIZE / 3, (float)PLAYER_SIZE, bullet->pos.x, bullet->pos.y, (float)BULLET_SIZE, (float)BULLET_SIZE);

	if (result == TRUE)
	{
#if DEBUG

#else
		player->hp--;
#endif
		bullet->state = 0;

		//SEの再生
		PlaySoundMem(g_playSE[2], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief 敵と自機の弾との当たり判定処理
//!
//! @param[enemy] 敵
//! @param[bullet] 弾
//!
//! @return なし
//----------------------------------------------------------------------
void DetectCollisionEnemyAndBullet(ObjectEnemy *enemy, ObjectBullet *bullet)
{
	//ローカル変数の宣言//----------------------------------------------
	//当たり判定の結果
	BOOL result;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	result = DetectCollisionBoxAndBox(enemy->pos.x, enemy->pos.y, (float)ENEMY_SIZE * enemy->extRate, (float)ENEMY_SIZE * enemy->extRate, bullet->pos.x, bullet->pos.y, (float)BULLET_SIZE * 3, (float)BULLET_SIZE);

	if (result == TRUE)
	{
#if DEBUG

#else
		enemy->state = 0;
#endif
		bullet->state = 0;

		//SEの再生
		PlaySoundMem(g_playSE[12], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief プレイヤーの弾とステージオブジェクトとの当たり判定処理
//!
//! @param[bullet] 弾
//! @param[stage] ステージオブジェクト
//!
//! @return なし
//----------------------------------------------------------------------
void DetectCollisionPlayerBulletAndObject(ObjectBullet *bullet, ObjectStage *stage)
{
	//ローカル変数の宣言//----------------------------------------------
	//当たり判定の結果
	BOOL result;

	//ステージオブジェクトの座標
	float stageX;
	float stageY;

	//ローカル変数の初期化//--------------------------------------------
	stageX = stage->pos.x + STAGE_SIZE / 2;
	stageY = stage->pos.y + STAGE_SIZE / 2;


	//処理の内容//------------------------------------------------------

	result = DetectCollisionBoxAndBox(bullet->pos.x, bullet->pos.y, (float)BULLET_SIZE, (float)BULLET_SIZE, stageX, stageY, (float)STAGE_SIZE, (float)STAGE_SIZE);

	if (result == TRUE)
	{
		bullet->state = 0;

		//SEの再生
		PlaySoundMem(g_playSE[13], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief 敵の弾とステージオブジェクトとの当たり判定処理
//!
//! @param[bullet] 弾
//! @param[stage] ステージオブジェクト
//!
//! @return なし
//----------------------------------------------------------------------
void DetectCollisionEnemyBulletAndObject(ObjectBullet *bullet, ObjectStage *stage)
{
	//ローカル変数の宣言//----------------------------------------------
	//当たり判定の結果
	BOOL result;

	//ステージオブジェクトの座標
	float stageX;
	float stageY;

	//ローカル変数の初期化//--------------------------------------------
	stageX = stage->pos.x + STAGE_SIZE / 2;
	stageY = stage->pos.y + STAGE_SIZE / 2;


	//処理の内容//------------------------------------------------------

	result = DetectCollisionBoxAndBox(bullet->pos.x, bullet->pos.y, (float)BULLET_SIZE, (float)BULLET_SIZE, stageX, stageY, (float)STAGE_SIZE, (float)STAGE_SIZE);

	if (result == TRUE)
	{
		bullet->state = 0;

		//SEの再生
		PlaySoundMem(g_playSE[14], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief 矩形同士の当たり判定処理
//!
//! @param[x1] 矩形1のX座標
//! @param[y1] 矩形1のY座標
//! @param[width1] 矩形1の横幅
//! @param[height1] 矩形1の高さ
//! @param[x2] 矩形2のX座標
//! @param[y2] 矩形2のY座標
//! @param[width2] 矩形2の横幅
//! @param[height2] 矩形2の高さ
//!
//! @return TREU 当たっている
//!			FALSE 当たっていない
//----------------------------------------------------------------------
BOOL DetectCollisionBoxAndBox(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2)
{
	//ローカル変数の宣言//----------------------------------------------
	//矩形1
	float left1;
	float right1;
	float top1;
	float bottom1;
	//矩形2
	float left2;
	float right2;
	float top2;
	float bottom2;


	//ローカル変数の初期化//--------------------------------------------
	left1 = x1 - width1 / 2;
	right1 = x1 + width1 / 2;
	top1 = y1 - height1 / 2;
	bottom1 = y1 + height1 / 2;

	left2 = x2 - width2 / 2;
	right2 = x2 + width2 / 2;
	top2 = y2 - height2 / 2;
	bottom2 = y2 + height2 / 2;

	//処理の内容//------------------------------------------------------

	if ((left1 <= right2) && (right1 >= left2) && (top1 <= bottom2) && (bottom1 >= top2))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}



//----------------------------------------------------------------------
//! @brief 矩形と点との当たり判定処理
//!
//! @param[boxX] 矩形のX座標
//! @param[boxY] 矩形のY座標
//! @param[width] 矩形の横幅
//! @param[height] 矩形の高さ
//! @param[poinX] 点のX座標
//! @param[pointY] 点のY座標
//!
//! @return TREU 当たっている
//!			FALSE 当たっていない
//----------------------------------------------------------------------
BOOL DetectCollisionBoxAndPoint(float boxX, float boxY, float width, float height, float pointX, float pointY)
{
	//ローカル変数の宣言//----------------------------------------------
	//矩形
	float left;
	float right;
	float top;
	float bottom;
	

	//ローカル変数の初期化//--------------------------------------------
	left = boxX - width / 2;
	right = boxX + width / 2;
	top = boxY - height / 2;
	bottom = boxY + height / 2;


	//処理の内容//------------------------------------------------------

	if ((left <= pointX) && (right >= pointX) && (top <= pointY) && (bottom >= pointY))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}