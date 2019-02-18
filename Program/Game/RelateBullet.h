//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateBullet.h
//!
//! @brief  eΦAΜwb_t@C
//!
//! @date   2017.10.01
//!
//! @author GF1.21.[Όl
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ½dCN[hΜh~ ==================================================
#pragma once




// ρΜΜθ` ============================================================
// ShotMeans^
enum Tag_ShotMeans
{
	NORMAL_SHOT,
	AIM_SHOT
};
typedef enum Tag_ShotMeans ShotMeans;


// f[^^Μθ` ==========================================================

//ObjectBullet^
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


// θΜθ` ==============================================================

// GΜeΜΕε
#define MAX_BULLET_ENEMY (100)

// vC[ΜeΜ¬x
#define SPEED_BULLET_PLAYER (5.0f)

// GΜeΜ¬x
#define SPEED_BULLET_ENEMY (5.0f)

//eΜTCY
#define BULLET_SIZE (16)


// O[oΟΜθ` ====================================================

//vC[Μe
extern ObjectBullet g_playerBullet;

//GΜe
extern ObjectBullet g_enemyBullet[MAX_BULLET_ENEMY];


// ΦΜιΎ ==============================================================

// eΜϊ»
void InitializeBullet(void);

// eΜXV
void UpdateBullet(void);

// eΜ`ζ
void RendarBullet(void);

// eΜ­Λ
void ShotBullet(ObjectBullet bullet[], int max, Vec2D target, float x, float y, float speed, ShotMeans shotType);
