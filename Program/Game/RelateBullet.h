//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateBullet.h
//!
//! @brief  弾関連のヘッダファイル
//!
//! @date   2017.10.01
//!
//! @author GF1.21.深草直斗
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// 多重インクルードの防止 ==================================================
#pragma once




// 列挙体の定義 ============================================================
// ShotMeans型
enum Tag_ShotMeans
{
	NORMAL_SHOT,
	AIM_SHOT
};
typedef enum Tag_ShotMeans ShotMeans;


// データ型の定義 ==========================================================

//ObjectBullet型
struct Tag_ObjectBullet
{
	Vec2D pos;
	Vec2D vel;
	HGRP image;
	int state;
	bool turn;
	float angle;
};
typedef struct Tag_ObjectBullet ObjectBullet;


// 定数の定義 ==============================================================

// 敵の弾の最大数
#define MAX_BULLET_ENEMY (100)

// プレイヤーの弾の速度
#define SPEED_BULLET_PLAYER (5.0f)

// 敵の弾の速度
#define SPEED_BULLET_ENEMY (5.0f)

//弾のサイズ
#define BULLET_SIZE (16)


// グローバル変数の定義 ====================================================

//プレイヤーの弾
extern ObjectBullet g_playerBullet;

//敵の弾
extern ObjectBullet g_enemyBullet[MAX_BULLET_ENEMY];


// 関数の宣言 ==============================================================

// 弾の初期化
void InitializeBullet(void);

// 弾の更新処理
void UpdateBullet(void);

// 弾の描画
void RendarBullet(void);

// 弾の発射
void ShotBullet(ObjectBullet bullet[], int max, Vec2D target, float x, float y, float speed, ShotMeans shotType);
