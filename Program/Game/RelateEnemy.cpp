//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateEnemy.cpp
//!
//! @brief  �G�֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
// �w�b�_�t�@�C���̓ǂݍ��� ================================================
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



// �񋓑̂̒�` ============================================================




// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================

//�G�̈ړ����x
#define MOVE_SPEED (1.0f)

//�G�̓���Ԋu�̎���
#define ACTION_INTERVAL (180)

//�G�̃W�����v��
#define JUMP_POWER (50.0f)


// �O���[�o���ϐ��̒�` ====================================================

//�G
ObjectEnemy g_enemies[MAX_ENEMY];

//�G�̍��W�f�[�^
int g_enemyData[STAGE_HEIGHT][STAGE_WIDTH];

//�G�̉摜
HGRP g_enemyImage[10];


// �֐��̃v���g�^�C�v�錾 ==================================================

//�G�f�[�^�̓ǂݍ���
void LoadEnemy(char *enemyFile, int width, int height);

//�G�̍U��
void AttackEnemy(ObjectEnemy *enemy);

//�U���^�C�v �t�@�C�A
void AttackTypeFire(ObjectEnemy *enemy);

//�G�̈ړ�
void MoveEnemy(ObjectEnemy *enemy);

//�ړ��^�C�v1
void MoveType1(ObjectEnemy *enemy);

//�ړ��^�C�v2
void MoveType2(ObjectEnemy *enemy);

//�ړ��^�C�v3
void MoveType3(ObjectEnemy *enemy);

//�ړ��^�C�v4
void MoveType4(ObjectEnemy *enemy);

//�G�̈ړ�����
void LimitAreaEnemy(ObjectEnemy *enemy);


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �G�̏���������
//!
//! @param[no] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeEnemy(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	char *enemyFile[MAX_STAGE];

	//�z��Ɏg�p
	int i;
	int x;
	int y;

	//���[�J���ϐ��̏�����//--------------------------------------------
	enemyFile[0] = "Resources/EnemyData/enemy.csv";
	enemyFile[1] = "Resources/EnemyData/enemy1.csv";
	enemyFile[2] = "Resources/EnemyData/enemy2.csv";
	enemyFile[3] = "Resources/EnemyData/enemy3.csv";
	enemyFile[4] = "Resources/EnemyData/enemy4.csv";
	enemyFile[5] = "Resources/EnemyData/tutorial.csv";
	enemyFile[6] = "Resources/EnemyData/tutorial2.csv";


	//�����̓��e//------------------------------------------------------

	// �G�̈ʒu�f�[�^�̓ǂݍ���
	LoadEnemy(enemyFile[g_stageId], STAGE_WIDTH, STAGE_HEIGHT);

	//�摜�̓ǂݍ���
	LoadDivGraph("Resources/Images/ENEMY_DATA.png", 5, 5, 1, 64, 64, g_enemyImage);

	//�G��������
	for (i = 0; i < MAX_ENEMY; i++)
	{
		g_enemies[i].state = 0;
	}

	//�X�e�[�W�ɔz�u
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
						case 1:	//�m�[�}��
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
						case 2:	//�\�[�h
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
						case 3:	//�t���C
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
						case 4:	//�t�@�C�A
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
						case 5:	//�r�b�O
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
//! @brief �G�̍X�V����
//!
//! @param[no] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateEnemy(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	for (i = 0; i < MAX_ENEMY; i++)
	{
		if ((g_enemies[i].state == 1) && (g_enemies[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + ENEMY_SIZE))
		{
			if (g_stageId != 6)
			{
				//�G�̍U��
				AttackEnemy(&g_enemies[i]);

				//�G�̈ړ�
				MoveEnemy(&g_enemies[i]);

				//�G�̈ړ�����
				LimitAreaEnemy(&g_enemies[i]);
			}
		}

	}

}



//----------------------------------------------------------------------
//! @brief �G�̕`�揈��
//!
//! @param[no] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RendarEnemy(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�G�̕`��
	for (i = 0; i < MAX_ENEMY; i++)
	{
		if ((g_enemies[i].state == 1) && (g_enemies[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + ENEMY_SIZE))
		{
			DrawRotaGraphF(g_enemies[i].pos.x - g_cameraPos.x, g_enemies[i].pos.y, g_enemies[i].extRate, (double)g_enemies[i].angle, g_enemies[i].image, TRUE, FALSE);
		}

	}

}



//*---------------------------------------------------------------------
//* �G�f�[�^�̓ǂݍ���
//*
//* @param [file] �G�t�@�C����
//* @param [Width] �X�e�[�W�̕�
//* @param [Height] �X�e�[�W�̍���
//*
//* @return �Ȃ�
//*---------------------------------------------------------------------
void LoadEnemy(char *enemyFile, int width, int height)
{
	//���[�J���ϐ��̐錾//--------------------------------
	// �t�@�C���\����
	FILE *fp;
	char buf[512];

	int i;	//�z��Ɏg�p
	int j;	//�z��Ɏg�p

	char *p;
	long number;

	//���[�J���ϐ��̏�����//------------------------------
	//�t�@�C�����J��
	fp = fopen(enemyFile, "r");

	p = NULL;

	//�����̓��e//----------------------------------------
	if (fp == NULL)
	{
		fprintf(stderr, "�t�@�C�����I�[�v���ł��܂���\n");
		// �����I��
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

	//�t�@�C�������
	fclose(fp);

}



//----------------------------------------------------------------------
//! @brief �G�̍U������
//!
//! @param[enemy] �U�����������G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void AttackEnemy(ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�G�̍U�����@
	if (enemy->actionInterval <= 0)
	{
		switch (enemy->type)
		{
		case NORMAL:	//�m�[�}��
			//�Ȃ�
			break;
		case SWORD:		//�\�[�h
			//�Ȃ�
			break;
		case FIRE:		//�t�@�C�A
			AttackTypeFire(enemy);
			break;
		case FLY:		//�t���C
			//�Ȃ�
			break;
		case BIG:		//�r�b�O
			//�Ȃ�
			break;
		default:

			break;
		}

		//�J�E���g��߂�
		enemy->actionInterval = ACTION_INTERVAL;
	}
	
	//����̊Ԋu������
	enemy->actionInterval--;

}



//----------------------------------------------------------------------
//! @brief �U���^�C�v �t�@�C�A�̏���
//!
//! @param[enemy] �G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void AttackTypeFire(ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�e�̔���
	ShotBullet(g_enemyBullet, MAX_BULLET_ENEMY, g_player.dataPos, enemy->pos.x, enemy->pos.y, SPEED_BULLET_ENEMY, AIM_SHOT);
	
}



//----------------------------------------------------------------------
//! @brief �G�̈ړ�����
//!
//! @param[enemy] �ړ����������G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MoveEnemy(ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�G�̈ړ����@
	switch (enemy->type)
	{
	case NORMAL:	//�m�[�}��
		MoveType1(enemy);
		break;
	case SWORD:		//�\�[�h
		MoveType2(enemy);
		break;
	case FIRE:		//�t�@�C�A
		//�Ȃ�
		break;
	case FLY:		//�t���C
		MoveType3(enemy);
		break;
	case BIG:		//�r�b�O
		MoveType4(enemy);
		break;
	default:

		break;
	}

	//����
	if (enemy->type != FLY)
	{
		enemy->vel.y += GRAVITY;
	}

	//�������x�̐���
	if (enemy->vel.y >= MAX_FALL_SPEED)
	{
		enemy->vel.y = MAX_FALL_SPEED;
	}

	//���W�̍X�V
	enemy->pos.x += enemy->vel.x;
	enemy->pos.y += enemy->vel.y;

}



//----------------------------------------------------------------------
//! @brief �G�̈ړ��^�C�v1�̏���
//!
//! @param[enemy] �G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MoveType1(ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//���x��^����
	if (enemy->vel.x == 0)
	{
		enemy->vel.x = -MOVE_SPEED;
	}

}



//----------------------------------------------------------------------
//! @brief �G�̈ړ��^�C�v2�̏���
//!
//! @param[enemy] �G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MoveType2(ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//���x��^����
	if (enemy->pos.x > g_player.dataPos.x)
	{
		enemy->vel.x = -MOVE_SPEED;
	}
	else
	{
		enemy->vel.x = MOVE_SPEED;
	}

	//��]
	enemy->angle += 0.1f;

}



//----------------------------------------------------------------------
//! @brief �G�̈ړ��^�C�v3�̏���
//!
//! @param[enemy] �G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MoveType3(ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	static float angle;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�p�x�̍X�V
	angle += 0.05f;

	//���x��^����
	enemy->vel.x = MOVE_SPEED*(float)cos((double)angle);
	enemy->vel.y = MOVE_SPEED*(float)sin((double)angle);

}



//----------------------------------------------------------------------
//! @brief �G�̈ړ��^�C�v4�̏���
//!
//! @param[enemy] �G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MoveType4(ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//���x��^����
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
//! @brief �G�̈ړ������̏���
//!
//! @param[enemy] ������������G
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void LimitAreaEnemy(ObjectEnemy *enemy)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	int i;

	//�����蔻��̌���
	BOOL result;

	float enemyX;
	float enemyY;
	float width;
	float height;
	float boxX;
	float boxY;


	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------

	//�G�̍��W������̂���I�u�W�F�N�g�������ꍇ
	for (i = 0; i < g_stageObjectNumber; i++)
	{
		if (g_objectStage[i].state == 1)
		{
			if (enemy->vel.x > 0)
			{
				//�E
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
						//�Ȃ�
						break;
					case FLY:
						//�Ȃ�
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
				//��
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
						//�Ȃ�
						break;
					case FLY:
						//�Ȃ�
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
			
			//�㉺�̔���
			enemyX = enemy->pos.x;
			enemyY = enemy->pos.y;
			width = (ENEMY_SIZE / 2) * enemy->extRate;
			height = ENEMY_SIZE * enemy->extRate;
			boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
			boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

			result = DetectCollisionBoxAndBox(enemyX, enemyY, width, height, boxX, boxY, STAGE_SIZE, STAGE_SIZE);

			if (result == TRUE)
			{
				//��
				if (enemyY <= boxY)
				{
					enemy->pos.y = g_objectStage[i].pos.y - (ENEMY_SIZE / 2) * enemy->extRate;
					enemy->vel.y = 0.0f;
				}
				//��
				else
				{
					enemy->pos.y = g_objectStage[i].pos.y + STAGE_SIZE * 2;
				}
			}
		}
	}

	//��ʊO�ɏo��
	if ((enemy->pos.x <= g_cameraPos.x - ENEMY_SIZE) || (enemy->pos.y >= SCREEN_BOTTOM + ENEMY_SIZE))
	{
		enemy->state = 0;
	}

}
