//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateEnemy.cpp
//!
//! @brief  敵関連のソースファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
// ヘッダファイルの読み込み ================================================
#include <stdio.h>
#include <math.h>
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelateEnemy.h"
#include "RelateStage.h"
#include "RelateCamera.h"
#include "RelateDetectCollition.h"
#include "RelateBullet.h"
#include "RelatePlayer.h"



// 列挙体の定義 ============================================================




// データ型の定義 ==========================================================




// 定数の定義 ==============================================================

//敵の移動速度
#define MOVE_SPEED (1.0f)

//敵の動作間隔の時間
#define ACTION_INTERVAL (180)

//敵のジャンプ力
#define JUMP_POWER (50.0f)


// グローバル変数の定義 ====================================================

//敵
ObjectEnemy g_enemies[MAX_ENEMY];

//敵の座標データ
int g_enemyData[STAGE_HEIGHT][STAGE_WIDTH];

//敵の画像
HGRP g_enemyImage[10];


// 関数のプロトタイプ宣言 ==================================================

//敵データの読み込み
void LoadEnemy(char *enemyFile, int width, int height);

//敵の攻撃
void AttackEnemy(ObjectEnemy *enemy);

//攻撃タイプ ファイア
void AttackTypeFire(ObjectEnemy *enemy);

//敵の移動
void MoveEnemy(ObjectEnemy *enemy);

//移動タイプ1
void MoveType1(ObjectEnemy *enemy);

//移動タイプ2
void MoveType2(ObjectEnemy *enemy);

//移動タイプ3
void MoveType3(ObjectEnemy *enemy);

//移動タイプ4
void MoveType4(ObjectEnemy *enemy);

//敵の移動制限
void LimitAreaEnemy(ObjectEnemy *enemy);


// 関数の定義 ==============================================================
//----------------------------------------------------------------------
//! @brief 敵の初期化処理
//!
//! @param[no] なし
//!
//! @return なし
//----------------------------------------------------------------------
void InitializeEnemy(void)
{
	//ローカル変数の宣言//----------------------------------------------
	char *enemyFile[MAX_STAGE];

	//配列に使用
	int i;
	int x;
	int y;

	//ローカル変数の初期化//--------------------------------------------
	enemyFile[0] = "Resources/EnemyData/enemy.csv";
	enemyFile[1] = "Resources/EnemyData/enemy1.csv";
	enemyFile[2] = "Resources/EnemyData/enemy2.csv";
	enemyFile[3] = "Resources/EnemyData/enemy3.csv";
	enemyFile[4] = "Resources/EnemyData/enemy4.csv";
	enemyFile[5] = "Resources/EnemyData/tutorial.csv";
	enemyFile[6] = "Resources/EnemyData/tutorial2.csv";


	//処理の内容//------------------------------------------------------

	// 敵の位置データの読み込み
	LoadEnemy(enemyFile[g_stageId], STAGE_WIDTH, STAGE_HEIGHT);

	//画像の読み込み
	LoadDivGraph("Resources/Images/ENEMY_DATA.png", 5, 5, 1, 64, 64, g_enemyImage);

	//敵を初期化
	for (i = 0; i < MAX_ENEMY; i++)
	{
		g_enemies[i].state = 0;
	}

	//ステージに配置
	for (y = 0; y < STAGE_HEIGHT; y++)
	{
		for (x = 0; x < STAGE_WIDTH; x++)
		{
			if (g_enemyData[y][x] != 0)
			{
				for (i = 0; i < MAX_ENEMY; i++)
				{
					if (g_enemies[i].state == 0)
					{
						switch (g_enemyData[y][x])
						{
						case 1:	//ノーマル
							g_enemies[i].pos.x = (float)(x*STAGE_SIZE);
							g_enemies[i].pos.y = (float)(y * STAGE_SIZE);
							g_enemies[i].vel.x = 0.0f;
							g_enemies[i].vel.y = 0.0f;
							g_enemies[i].image = g_enemyImage[0];
							g_enemies[i].extRate = 0.5f;
							g_enemies[i].angle = 0.0f;
							g_enemies[i].state = 1;
							g_enemies[i].type = NORMAL;
							g_enemies[i].actionInterval = ACTION_INTERVAL;
							break;
						case 2:	//ソード
							g_enemies[i].pos.x = (float)(x*STAGE_SIZE);
							g_enemies[i].pos.y = (float)(y * STAGE_SIZE);
							g_enemies[i].vel.x = 0.0f;
							g_enemies[i].vel.y = 0.0f;
							g_enemies[i].image = g_enemyImage[1];
							g_enemies[i].extRate = 0.7f;
							g_enemies[i].angle = 0.0f;
							g_enemies[i].state = 1;
							g_enemies[i].type = SWORD;
							g_enemies[i].actionInterval = ACTION_INTERVAL;
							break;
						case 3:	//フライ
							g_enemies[i].pos.x = (float)(x*STAGE_SIZE);
							g_enemies[i].pos.y = (float)(y * STAGE_SIZE);
							g_enemies[i].vel.x = 0.0f;
							g_enemies[i].vel.y = 0.0f;
							g_enemies[i].image = g_enemyImage[2];
							g_enemies[i].extRate = 1.0f;
							g_enemies[i].angle = 0.0f;
							g_enemies[i].state = 1;
							g_enemies[i].type = FLY;
							g_enemies[i].actionInterval = ACTION_INTERVAL;
							break;
						case 4:	//ファイア
							g_enemies[i].pos.x = (float)(x*STAGE_SIZE);
							g_enemies[i].pos.y = (float)(y * STAGE_SIZE);
							g_enemies[i].vel.x = 0.0f;
							g_enemies[i].vel.y = 0.0f;
							g_enemies[i].image = g_enemyImage[3];
							g_enemies[i].extRate = 0.5f;
							g_enemies[i].angle = 0.0f;
							g_enemies[i].state = 1;
							g_enemies[i].type = FIRE;
							g_enemies[i].actionInterval = ACTION_INTERVAL;
							break;
						case 5:	//ビッグ
							g_enemies[i].pos.x = (float)(x*STAGE_SIZE);
							g_enemies[i].pos.y = (float)(y * STAGE_SIZE);
							g_enemies[i].vel.x = 0.0f;
							g_enemies[i].vel.y = 0.0f;
							g_enemies[i].image = g_enemyImage[4];
							g_enemies[i].extRate = 1.0f;
							g_enemies[i].angle = 0.0f;
							g_enemies[i].state = 1;
							g_enemies[i].type = BIG;
							g_enemies[i].actionInterval = ACTION_INTERVAL;
							break;
						default:

							break;
						}

						break;
					}
				}
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief 敵の更新処理
//!
//! @param[no] なし
//!
//! @return なし
//----------------------------------------------------------------------
void UpdateEnemy(void)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if ((g_enemies[i].state == 1) && (g_enemies[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + ENEMY_SIZE))
		{
			if (g_stageId != 6)
			{
				//敵の攻撃
				AttackEnemy(&g_enemies[i]);

				//敵の移動
				MoveEnemy(&g_enemies[i]);

				//敵の移動制限
				LimitAreaEnemy(&g_enemies[i]);
			}
		}

	}

}



//----------------------------------------------------------------------
//! @brief 敵の描画処理
//!
//! @param[no] なし
//!
//! @return なし
//----------------------------------------------------------------------
void RendarEnemy(void)
{
	//ローカル変数の宣言//----------------------------------------------
	//配列に使用
	int i;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//敵の描画
	for (i = 0; i < MAX_ENEMY; i++)
	{
		if ((g_enemies[i].state == 1) && (g_enemies[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + ENEMY_SIZE))
		{
			DrawRotaGraphF(g_enemies[i].pos.x - g_cameraPos.x, g_enemies[i].pos.y, g_enemies[i].extRate, (double)g_enemies[i].angle, g_enemies[i].image, TRUE, FALSE);
		}

	}

}



//*---------------------------------------------------------------------
//* 敵データの読み込み
//*
//* @param [file] 敵ファイル名
//* @param [Width] ステージの幅
//* @param [Height] ステージの高さ
//*
//* @return なし
//*---------------------------------------------------------------------
void LoadEnemy(char *enemyFile, int width, int height)
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
	fp = fopen(enemyFile, "r");

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

				g_enemyData[i][j] = (int)number;
				p++;
			}
		}
	}

	//ファイルを閉じる
	fclose(fp);

}



//----------------------------------------------------------------------
//! @brief 敵の攻撃処理
//!
//! @param[enemy] 攻撃させたい敵
//!
//! @return なし
//----------------------------------------------------------------------
void AttackEnemy(ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//敵の攻撃方法
	if (enemy->actionInterval <= 0)
	{
		switch (enemy->type)
		{
		case NORMAL:	//ノーマル
			//なし
			break;
		case SWORD:		//ソード
			//なし
			break;
		case FIRE:		//ファイア
			AttackTypeFire(enemy);
			break;
		case FLY:		//フライ
			//なし
			break;
		case BIG:		//ビッグ
			//なし
			break;
		default:

			break;
		}

		//カウントを戻す
		enemy->actionInterval = ACTION_INTERVAL;
	}
	
	//動作の間隔を減少
	enemy->actionInterval--;

}



//----------------------------------------------------------------------
//! @brief 攻撃タイプ ファイアの処理
//!
//! @param[enemy] 敵
//!
//! @return なし
//----------------------------------------------------------------------
void AttackTypeFire(ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------
	


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//弾の発射
	ShotBullet(g_enemyBullet, MAX_BULLET_ENEMY, g_player.dataPos, enemy->pos.x, enemy->pos.y, SPEED_BULLET_ENEMY, AIM_SHOT);
	
}



//----------------------------------------------------------------------
//! @brief 敵の移動処理
//!
//! @param[enemy] 移動させたい敵
//!
//! @return なし
//----------------------------------------------------------------------
void MoveEnemy(ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//敵の移動方法
	switch (enemy->type)
	{
	case NORMAL:	//ノーマル
		MoveType1(enemy);
		break;
	case SWORD:		//ソード
		MoveType2(enemy);
		break;
	case FIRE:		//ファイア
		//なし
		break;
	case FLY:		//フライ
		MoveType3(enemy);
		break;
	case BIG:		//ビッグ
		MoveType4(enemy);
		break;
	default:

		break;
	}

	//落下
	if (enemy->type != FLY)
	{
		enemy->vel.y += GRAVITY;
	}

	//落下速度の制限
	if (enemy->vel.y >= MAX_FALL_SPEED)
	{
		enemy->vel.y = MAX_FALL_SPEED;
	}

	//座標の更新
	enemy->pos.x += enemy->vel.x;
	enemy->pos.y += enemy->vel.y;

}



//----------------------------------------------------------------------
//! @brief 敵の移動タイプ1の処理
//!
//! @param[enemy] 敵
//!
//! @return なし
//----------------------------------------------------------------------
void MoveType1(ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//速度を与える
	if (enemy->vel.x == 0)
	{
		enemy->vel.x = -MOVE_SPEED;
	}

}



//----------------------------------------------------------------------
//! @brief 敵の移動タイプ2の処理
//!
//! @param[enemy] 敵
//!
//! @return なし
//----------------------------------------------------------------------
void MoveType2(ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//速度を与える
	if (enemy->pos.x > g_player.dataPos.x)
	{
		enemy->vel.x = -MOVE_SPEED;
	}
	else
	{
		enemy->vel.x = MOVE_SPEED;
	}

	//回転
	enemy->angle += 0.1f;

}



//----------------------------------------------------------------------
//! @brief 敵の移動タイプ3の処理
//!
//! @param[enemy] 敵
//!
//! @return なし
//----------------------------------------------------------------------
void MoveType3(ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------
	static float angle;


	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//角度の更新
	angle += 0.05f;

	//速度を与える
	enemy->vel.x = MOVE_SPEED*(float)cos((double)angle);
	enemy->vel.y = MOVE_SPEED*(float)sin((double)angle);

}



//----------------------------------------------------------------------
//! @brief 敵の移動タイプ4の処理
//!
//! @param[enemy] 敵
//!
//! @return なし
//----------------------------------------------------------------------
void MoveType4(ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------



	//ローカル変数の初期化//--------------------------------------------



	//処理の内容//------------------------------------------------------

	//速度を与える
	if (enemy->pos.x < g_player.dataPos.x)
	{
		enemy->vel.x = -MOVE_SPEED;
	}
	else
	{
		enemy->vel.x = MOVE_SPEED;
	}

}



//----------------------------------------------------------------------
//! @brief 敵の移動制限の処理
//!
//! @param[enemy] 制限をかける敵
//!
//! @return なし
//----------------------------------------------------------------------
void LimitAreaEnemy(ObjectEnemy *enemy)
{
	//ローカル変数の宣言//----------------------------------------------
	int i;

	//当たり判定の結果
	BOOL result;

	float enemyX;
	float enemyY;
	float width;
	float height;
	float boxX;
	float boxY;


	//ローカル変数の初期化//--------------------------------------------




	//処理の内容//------------------------------------------------------

	//敵の座標が判定のあるオブジェクトだった場合
	for (i = 0; i < g_stageObjectNumber; i++)
	{
		if (g_objectStage[i].state == 1)
		{
			if (enemy->vel.x > 0)
			{
				//右
				enemyX = enemy->pos.x + (ENEMY_SIZE / 2) * enemy->extRate;
				enemyY = enemy->pos.y;
				boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
				boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

				result = DetectCollisionBoxAndPoint(boxX, boxY, STAGE_SIZE, STAGE_SIZE, enemyX, enemyY);

				if (result == TRUE)
				{
					switch (enemy->type)
					{
					case NORMAL:
						enemy->vel.x *= -1;
						break;
					case SWORD:
						enemy->pos.x -= enemy->vel.x;
						enemy->pos.y -= enemy->vel.y;
						break;
					case FIRE:
						//なし
						break;
					case FLY:
						//なし
						break;
					case BIG:
						enemy->pos.x -= enemy->vel.x;
						enemy->pos.y -= enemy->vel.y;
						break;
					default:

						break;
					}
				}
			}
			else
			{
				//左
				enemyX = enemy->pos.x - (ENEMY_SIZE / 2) * enemy->extRate;
				enemyY = enemy->pos.y;
				boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
				boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

				result = DetectCollisionBoxAndPoint(boxX, boxY, STAGE_SIZE, STAGE_SIZE, enemyX, enemyY);

				if (result == TRUE)
				{
					switch (enemy->type)
					{
					case NORMAL:
						enemy->vel.x *= -1;
						break;
					case SWORD:
						enemy->pos.x -= enemy->vel.x;
						enemy->pos.y -= enemy->vel.y;
						break;
					case FIRE:
						//なし
						break;
					case FLY:
						//なし
						break;
					case BIG:
						enemy->pos.x -= enemy->vel.x;
						enemy->pos.y -= enemy->vel.y;
						break;
					default:

						break;
					}
				}
			}
			
			//上下の判定
			enemyX = enemy->pos.x;
			enemyY = enemy->pos.y;
			width = (ENEMY_SIZE / 2) * enemy->extRate;
			height = ENEMY_SIZE * enemy->extRate;
			boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
			boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

			result = DetectCollisionBoxAndBox(enemyX, enemyY, width, height, boxX, boxY, STAGE_SIZE, STAGE_SIZE);

			if (result == TRUE)
			{
				//上
				if (enemyY <= boxY)
				{
					enemy->pos.y = g_objectStage[i].pos.y - (ENEMY_SIZE / 2) * enemy->extRate;
					enemy->vel.y = 0.0f;
				}
				//下
				else
				{
					enemy->pos.y = g_objectStage[i].pos.y + STAGE_SIZE * 2;
				}
			}
		}
	}

	//画面外に出る
	if ((enemy->pos.x <= g_cameraPos.x - ENEMY_SIZE) || (enemy->pos.y >= SCREEN_BOTTOM + ENEMY_SIZE))
	{
		enemy->state = 0;
	}

}
