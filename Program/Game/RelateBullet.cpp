//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateBullet.cpp
//!
//! @brief  �e�֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <math.h>
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelateBullet.h"
#include "RelateCamera.h"


// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================

//�v���C���[�̒e
ObjectBullet g_playerBullet;

//�G�̒e
ObjectBullet g_enemyBullet[MAX_BULLET_ENEMY];

//�e�̉摜
HGRP g_bulletImage;


// �֐��̃v���g�^�C�v�錾 ==================================================
// �ʏ�e�̔���
void ShotNormalBullet(ObjectBullet *bullet, float x, float y, float speed);

// �^�[�Q�b�g�_���̒e�̔���
void ShotAimBullet(ObjectBullet *bullet, Vec2D target, float x, float y, float speed);

// �e�̈ړ�
void MoveBullet(ObjectBullet *bullet);



// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �e�̏���������
//!
//! @param[no] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeBullet(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------
	//�摜�̓ǂݍ���
	g_bulletImage = LoadGraph("Resources/Images/Slash.png");

	//�v���C���[�̒e
	g_playerBullet.pos.x = 0.0f;
	g_playerBullet.pos.y = 0.0f;
	g_playerBullet.vel.x = 0.0f;
	g_playerBullet.vel.y = 0.0f;
	g_playerBullet.image = g_bulletImage;
	g_playerBullet.angle = 0.0f;
	g_playerBullet.turn = FALSE;
	g_playerBullet.state = 0;

	//�摜�̓ǂݍ���
	g_bulletImage = LoadGraph("Resources/Images/Bullet.png");

	//�G�̒e
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
//! @brief �e�̍X�V����
//!
//! @param[no] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateBullet(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�v���C���[�̒e
	if (g_playerBullet.state == 1)
	{
		MoveBullet(&g_playerBullet);
	}

	//�G�̒e
	for (i = 0; i < MAX_BULLET_ENEMY; i++)
	{
		if (g_enemyBullet[i].state == 1)
		{
			MoveBullet(&g_enemyBullet[i]);
		}
	}

}



//----------------------------------------------------------------------
//! @brief �e�̕`�揈��
//!
//! @param[no] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RendarBullet(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�v���C���[�̒e
		if (g_playerBullet.state == 1)
		{
			DrawRotaGraphF(g_playerBullet.pos.x - g_cameraPos.x, g_playerBullet.pos.y, 1.0f, g_playerBullet.angle, g_playerBullet.image, TRUE, g_playerBullet.turn);
		}

	//�G�̒e
	for (i = 0; i < MAX_BULLET_ENEMY; i++)
	{
		if (g_enemyBullet[i].state == 1)
		{
			DrawRotaGraphF(g_enemyBullet[i].pos.x - g_cameraPos.x, g_enemyBullet[i].pos.y, 1.0f, g_enemyBullet[i].angle, g_enemyBullet[i].image, TRUE, g_enemyBullet[i].turn);
		}
	}

}



//----------------------------------------------------------------------
//! @brief �e�̔��ˏ���
//!
//! @param[bullet] �e
//! @param[max] �e�̍ő吔
//! @param[target] �^�[�Q�b�g�̍��W
//! @param[x] ���˒n�_��X���W
//! @param[y] ���˒n�_��Y���W
//! @param[speed] �e�̑��x
//! @param[type] �e�̎��
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ShotBullet(ObjectBullet bullet[], int max, Vec2D target, float x, float y, float speed, ShotMeans type)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�e�𒲂ׂ�
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

			//SE�̍Đ�
			PlaySoundMem(g_playSE[8], DX_PLAYTYPE_BACK, TRUE);

			break;
		}
	}

}



//----------------------------------------------------------------------
//! @brief �ʏ�e�̔��ˏ���
//!
//! @param[bullet] �e
//! @param[x] ���˒n�_��X���W
//! @param[y] ���˒n�_��Y���W
//! @param[speed] �e�̑��x
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ShotNormalBullet(ObjectBullet *bullet, float x, float y, float speed)
{
	//���[�J���ϐ��̐錾//----------------------------------------------




	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------

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
//! @brief �^�[�Q�b�g�_���̒e�̔��ˏ���
//!
//! @param[bullet] �e
//! @param[target] �^�[�Q�b�g�̍��W
//! @param[x] ���˒n�_��X���W
//! @param[y] ���˒n�_��Y���W
//! @param[speed] �e�̑��x
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ShotAimBullet(ObjectBullet *bullet, Vec2D target, float x, float y, float speed)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//����
	double dx;
	double dy;

	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	bullet->pos.x = x;
	bullet->pos.y = y;

	//���������߂�
	dx = target.x - bullet->pos.x;
	dy = target.y - bullet->pos.y;

	//�p�x�����߂�
	bullet->angle = (float)atan2(dy, dx);

	//���x��^����
	bullet->vel.x = speed*(float)cos(bullet->angle);
	bullet->vel.y = speed*(float)sin(bullet->angle);

	bullet->state = 1;

}



//----------------------------------------------------------------------
//! @brief �e�̈ړ�����
//!
//! @param[bullet] �e
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MoveBullet(ObjectBullet *bullet)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//���W�̍X�V
	bullet->pos.x += bullet->vel.x;
	bullet->pos.y += bullet->vel.y;

	//�e�̏���
	if ((bullet->pos.x<g_cameraPos.x) || (bullet->pos.x>g_cameraPos.x + CAMERA_WIDTH)
		|| (bullet->pos.y<g_cameraPos.y) || (bullet->pos.y>g_cameraPos.y + CAMERA_HEIGHT))
	{
		bullet->state = 0;
	}

}
