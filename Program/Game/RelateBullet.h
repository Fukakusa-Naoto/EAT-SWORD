//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateBullet.h
//!
//! @brief  �e�֘A�̃w�b�_�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �񋓑̂̒�` ============================================================
// ShotMeans�^
enum Tag_ShotMeans
{
	NORMAL_SHOT,
	AIM_SHOT
};
typedef enum Tag_ShotMeans ShotMeans;


// �f�[�^�^�̒�` ==========================================================

//ObjectBullet�^
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


// �萔�̒�` ==============================================================

// �G�̒e�̍ő吔
#define MAX_BULLET_ENEMY (100)

// �v���C���[�̒e�̑��x
#define SPEED_BULLET_PLAYER (5.0f)

// �G�̒e�̑��x
#define SPEED_BULLET_ENEMY (5.0f)

//�e�̃T�C�Y
#define BULLET_SIZE (16)


// �O���[�o���ϐ��̒�` ====================================================

//�v���C���[�̒e
extern ObjectBullet g_playerBullet;

//�G�̒e
extern ObjectBullet g_enemyBullet[MAX_BULLET_ENEMY];


// �֐��̐錾 ==============================================================

// �e�̏�����
void InitializeBullet(void);

// �e�̍X�V����
void UpdateBullet(void);

// �e�̕`��
void RendarBullet(void);

// �e�̔���
void ShotBullet(ObjectBullet bullet[], int max, Vec2D target, float x, float y, float speed, ShotMeans shotType);
