//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateDetectCollition.cpp
//!
//! @brief  �Փ˔���֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelateDetectCollition.h"
#include "RelatePlayer.h"
#include "RelateEnemy.h"
#include "RelateCamera.h"
#include "RelateStage.h"
#include "RelateBullet.h"


// �񋓑̂̒�` ============================================================




// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================




// �֐��̃v���g�^�C�v�錾 ==================================================

//�v���C���[�ƓG�̓����蔻��
void DetectCollisionPlayerAndEnemy(ObjectPlayer *player,ObjectEnemy *enemy);

//���ƓG�Ƃ̓����蔻��
void DetectCollisionSwordAndEnemy(ObjectPlayer *player, ObjectEnemy *enemy);

//���ƃX�e�[�W�I�u�W�F�N�g�Ƃ̓����蔻��
void DetectCollisionSwordAndObject(ObjectPlayer *player, ObjectStage *stage);

//���@�ƓG�̒e�Ƃ̓����蔻��
void DetectCollisionPlayerAndBullet(ObjectPlayer *player, ObjectBullet *bullet);

//�G�Ǝ��@�̒e�Ƃ̓����蔻��
void DetectCollisionEnemyAndBullet(ObjectEnemy *enemy, ObjectBullet *bullet);

//�v���C���[�̒e�ƃX�e�[�W�I�u�W�F�N�g�Ƃ̓����蔻��
void DetectCollisionPlayerBulletAndObject(ObjectBullet *bullet, ObjectStage *stage);

//�G�̒e�ƃX�e�[�W�I�u�W�F�N�g�Ƃ̓����蔻��
void DetectCollisionEnemyBulletAndObject(ObjectBullet *bullet, ObjectStage *stage);

//��`���m�̓����蔻��
BOOL DetectCollisionBoxAndBox(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);

//��`�Ɠ_�̓����蔻��
BOOL DetectCollisionBoxAndPoint(float boxX, float boxY, float width, float height, float pointX, float pointY);


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �S�Ă̓����蔻�菈��
//!
//! @param[no] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void AllDetectCollision(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;
	int j;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	if (g_player.state == 1)
	{
		//�G
		for (i = 0; i < MAX_ENEMY; i++)
		{
			if ((g_enemies[i].state == 1) && (g_enemies[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + ENEMY_SIZE))
			{
				//�v���C���[�ƓG�Ƃ̓����蔻��
				DetectCollisionPlayerAndEnemy(&g_player, &g_enemies[i]);

				//���ƓG�Ƃ̓����蔻��
				DetectCollisionSwordAndEnemy(&g_player, &g_enemies[i]);
			}
		}

		//�X�e�[�W
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

		//�G�̒e
		for (i = 0; i < MAX_BULLET_ENEMY; i++)
		{
			if (g_enemyBullet[i].state == 1)
			{
				DetectCollisionPlayerAndBullet(&g_player, &g_enemyBullet[i]);
			}
		}

		// <�e>
		//���@
		if (g_playerBullet.state == 1)
		{
			//�G
			for (j = 0; j < MAX_ENEMY; j++)
			{
				if ((g_enemies[j].state == 1) && (g_enemies[j].pos.x <= g_cameraPos.x + CAMERA_WIDTH + ENEMY_SIZE))
				{
					DetectCollisionEnemyAndBullet(&g_enemies[j], &g_playerBullet);
				}
			}

			//�X�e�[�W
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


		//�G
		for (i = 0; i < MAX_BULLET_ENEMY; i++)
		{
			if (g_enemyBullet[i].state == 1)
			{
				//�X�e�[�W
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
//! @brief �v���C���[�ƓG�Ƃ̓����蔻�菈��
//!
//! @param[player] �v���C���[
//! @param[enemy] �G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DetectCollisionPlayerAndEnemy(ObjectPlayer *player, ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�����蔻��̌���
	BOOL result;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------
	//�����蔻��
	result = DetectCollisionBoxAndBox(player->dataPos.x, player->dataPos.y, (float)PLAYER_SIZE / 3, (float)PLAYER_SIZE, enemy->pos.x, enemy->pos.y, (float)ENEMY_SIZE * enemy->extRate, (float)ENEMY_SIZE * enemy->extRate);

	if (result == TRUE)
	{
#if DEBUG
		
#else
		player->hp--;
#endif
		enemy->state = 0;

		//SE�̍Đ�
		PlaySoundMem(g_playSE[2], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief ���ƓG�Ƃ̓����蔻�菈��
//!
//! @param[player] �v���C���[
//! @param[enemy] �G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DetectCollisionSwordAndEnemy(ObjectPlayer *player, ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�����蔻��̌���
	BOOL result;

	//���̍��W
	float swordPosX;
	float swordPosY;

	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	// �m�[�}�� //
	//���W�̌v�Z
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
		case NORMAL:	//�m�[�}��
			//�Ȃ�
			break;
		case SWORD:		//�\�[�h
			player->type = SWORD;
			player->count = TIME_SPECIAL;
			break;
		case FIRE:		//�t�@�C�A
			player->type = FIRE;
			player->count = TIME_SPECIAL;
			break;
		case FLY:		//�t���C
			player->type = FLY;
			player->count = TIME_SPECIAL;
			break;
		case BIG:		//�r�b�O
			player->type = BIG;
			player->count = TIME_SPECIAL;
			break;
		default:

			break;
		}

		enemy->state = 0;

		//SE�̍Đ�
		PlaySoundMem(g_playSE[10], DX_PLAYTYPE_BACK, TRUE);
	}

	// �\�H //
	//���W�̌v�Z
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

	//�����蔻��
	result = DetectCollisionBoxAndPoint(swordPosX, swordPosY, (float)STAGE_SIZE * 7, (float)STAGE_SIZE * 8, enemy->pos.x, enemy->pos.y);

	if ((result == TRUE) && (player->animation[GLUTTONY].frameNum >= 10) && (player->animation[GLUTTONY].frameNum <= 13))
	{
		enemy->state = 0;

		//SE�̍Đ�
		PlaySoundMem(g_playSE[11], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief ���ƃX�e�[�W�I�u�W�F�N�g�Ƃ̓����蔻�菈��
//!
//! @param[player] �v���C���[
//! @param[stage] �X�e�[�W�I�u�W�F�N�g
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DetectCollisionSwordAndObject(ObjectPlayer *player, ObjectStage *stage)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�����蔻��̌���
	BOOL result;

	//���̍��W
	float swordPosX;
	float swordPosY;

	//�X�e�[�W�I�u�W�F�N�g�̍��W
	float stageX;
	float stageY;

	//�z��Ɏg�p
	int i;

	//���[�J���ϐ��̏�����//--------------------------------------------
	stageX = stage->pos.x + STAGE_SIZE / 2;
	stageY = stage->pos.y + STAGE_SIZE / 2;


	//�����̓��e//------------------------------------------------------

	// �m�[�}�� //
	//���W�̌v�Z
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

				//SE�̍Đ�
				PlaySoundMem(g_playSE[10], DX_PLAYTYPE_BACK, TRUE);
			}
		}
	}

	// ���� //
	if (player->type == FIRE)
	{
		//���W�̌v�Z
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

		//�����蔻��
		result = DetectCollisionBoxAndBox(swordPosX, swordPosY, (float)PLAYER_SIZE / 2, (float)PLAYER_SIZE / 2, stageX, stageY, (float)STAGE_SIZE, (float)STAGE_SIZE);

		if (result == TRUE)
		{
			if ((player->animation[SWING].frameNum >= 8) && (player->animation[SWING].frameNum <= 12))
			{
				if (stage->type == 3)
				{
					//�G�t�F�N�g���o��
					for (i = 0; i < 100; i++)
					{
						if (g_stageAnimation[i].animation.state == 0)
						{
							g_stageAnimation[i].pos = stage->pos;
							g_stageAnimation[i].animation.state = 1;

							//SE�̍Đ�
							PlaySoundMem(g_playSE[16], DX_PLAYTYPE_BACK, TRUE);
							
							break;
						}
					}
				}
			}
		}
	}
	
	//�I�u�W�F�N�g�̏���
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
	
	// �\�H //
	//���W�̌v�Z
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
				//SE�̍Đ�
				PlaySoundMem(g_playSE[11], DX_PLAYTYPE_BACK, TRUE);
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief �v���C���[�ƓG�̒e�Ƃ̓����蔻�菈��
//!
//! @param[player] �v���C���[
//! @param[bullet] �e
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DetectCollisionPlayerAndBullet(ObjectPlayer *player, ObjectBullet *bullet)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�����蔻��̌���
	BOOL result;

	//�v���C���[�̍��W
	float playerPosX;
	float playerPosY;

	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//���W�̌v�Z
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

		//SE�̍Đ�
		PlaySoundMem(g_playSE[2], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief �G�Ǝ��@�̒e�Ƃ̓����蔻�菈��
//!
//! @param[enemy] �G
//! @param[bullet] �e
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DetectCollisionEnemyAndBullet(ObjectEnemy *enemy, ObjectBullet *bullet)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�����蔻��̌���
	BOOL result;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	result = DetectCollisionBoxAndBox(enemy->pos.x, enemy->pos.y, (float)ENEMY_SIZE * enemy->extRate, (float)ENEMY_SIZE * enemy->extRate, bullet->pos.x, bullet->pos.y, (float)BULLET_SIZE * 3, (float)BULLET_SIZE);

	if (result == TRUE)
	{
#if DEBUG

#else
		enemy->state = 0;
#endif
		bullet->state = 0;

		//SE�̍Đ�
		PlaySoundMem(g_playSE[12], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief �v���C���[�̒e�ƃX�e�[�W�I�u�W�F�N�g�Ƃ̓����蔻�菈��
//!
//! @param[bullet] �e
//! @param[stage] �X�e�[�W�I�u�W�F�N�g
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DetectCollisionPlayerBulletAndObject(ObjectBullet *bullet, ObjectStage *stage)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�����蔻��̌���
	BOOL result;

	//�X�e�[�W�I�u�W�F�N�g�̍��W
	float stageX;
	float stageY;

	//���[�J���ϐ��̏�����//--------------------------------------------
	stageX = stage->pos.x + STAGE_SIZE / 2;
	stageY = stage->pos.y + STAGE_SIZE / 2;


	//�����̓��e//------------------------------------------------------

	result = DetectCollisionBoxAndBox(bullet->pos.x, bullet->pos.y, (float)BULLET_SIZE, (float)BULLET_SIZE, stageX, stageY, (float)STAGE_SIZE, (float)STAGE_SIZE);

	if (result == TRUE)
	{
		bullet->state = 0;

		//SE�̍Đ�
		PlaySoundMem(g_playSE[13], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief �G�̒e�ƃX�e�[�W�I�u�W�F�N�g�Ƃ̓����蔻�菈��
//!
//! @param[bullet] �e
//! @param[stage] �X�e�[�W�I�u�W�F�N�g
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DetectCollisionEnemyBulletAndObject(ObjectBullet *bullet, ObjectStage *stage)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�����蔻��̌���
	BOOL result;

	//�X�e�[�W�I�u�W�F�N�g�̍��W
	float stageX;
	float stageY;

	//���[�J���ϐ��̏�����//--------------------------------------------
	stageX = stage->pos.x + STAGE_SIZE / 2;
	stageY = stage->pos.y + STAGE_SIZE / 2;


	//�����̓��e//------------------------------------------------------

	result = DetectCollisionBoxAndBox(bullet->pos.x, bullet->pos.y, (float)BULLET_SIZE, (float)BULLET_SIZE, stageX, stageY, (float)STAGE_SIZE, (float)STAGE_SIZE);

	if (result == TRUE)
	{
		bullet->state = 0;

		//SE�̍Đ�
		PlaySoundMem(g_playSE[14], DX_PLAYTYPE_BACK, TRUE);
	}

}



//----------------------------------------------------------------------
//! @brief ��`���m�̓����蔻�菈��
//!
//! @param[x1] ��`1��X���W
//! @param[y1] ��`1��Y���W
//! @param[width1] ��`1�̉���
//! @param[height1] ��`1�̍���
//! @param[x2] ��`2��X���W
//! @param[y2] ��`2��Y���W
//! @param[width2] ��`2�̉���
//! @param[height2] ��`2�̍���
//!
//! @return TREU �������Ă���
//!			FALSE �������Ă��Ȃ�
//----------------------------------------------------------------------
BOOL DetectCollisionBoxAndBox(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//��`1
	float left1;
	float right1;
	float top1;
	float bottom1;
	//��`2
	float left2;
	float right2;
	float top2;
	float bottom2;


	//���[�J���ϐ��̏�����//--------------------------------------------
	left1 = x1 - width1 / 2;
	right1 = x1 + width1 / 2;
	top1 = y1 - height1 / 2;
	bottom1 = y1 + height1 / 2;

	left2 = x2 - width2 / 2;
	right2 = x2 + width2 / 2;
	top2 = y2 - height2 / 2;
	bottom2 = y2 + height2 / 2;

	//�����̓��e//------------------------------------------------------

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
//! @brief ��`�Ɠ_�Ƃ̓����蔻�菈��
//!
//! @param[boxX] ��`��X���W
//! @param[boxY] ��`��Y���W
//! @param[width] ��`�̉���
//! @param[height] ��`�̍���
//! @param[poinX] �_��X���W
//! @param[pointY] �_��Y���W
//!
//! @return TREU �������Ă���
//!			FALSE �������Ă��Ȃ�
//----------------------------------------------------------------------
BOOL DetectCollisionBoxAndPoint(float boxX, float boxY, float width, float height, float pointX, float pointY)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//��`
	float left;
	float right;
	float top;
	float bottom;
	

	//���[�J���ϐ��̏�����//--------------------------------------------
	left = boxX - width / 2;
	right = boxX + width / 2;
	top = boxY - height / 2;
	bottom = boxY + height / 2;


	//�����̓��e//------------------------------------------------------

	if ((left <= pointX) && (right >= pointX) && (top <= pointY) && (bottom >= pointY))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}

}