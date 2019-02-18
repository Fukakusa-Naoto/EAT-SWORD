//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelatePlayer.cpp
//!
//! @brief  �v���C���[�֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <math.h>
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelatePlayer.h"
#include "RelateAnimation.h"
#include "RelateStage.h"
#include "RelateDetectCollition.h"
#include "RelateUI.h"
#include "RelateSpecial.h"

#include "RelateCamera.h"


// �񋓑̂̒�` ============================================================




// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================

// <�A�j���[�V�����Đ����x> -------------------------------------------
// ����
#define ANIME_SPEED_RUN (0.3f)

// �H�ׂ�
#define ANIME_SPEED_EAT (0.5f)

// ����U��
#define ANIME_SPEED_SWING (0.5f)

// �\�H
#define ANIME_SPEED_GLUTTONY (1.0f)

// <�X�e�[�^�X> -------------------------------------------------------
// �ړ����x
#define MOVE_SPEED (4.0f)

// �W�����v��
#define JUMP_POWER (20.0f)

// �W�����v��(����\��)
#define SPECIAL_JUMP_POWER (30.0f)

//�ő�̗͗�
#define MAX_HP (10)

// �O���[�o���ϐ��̒�` ====================================================

// <�v���C���[> -------------------------------------------------------
ObjectPlayer g_player;

// ����
HGRP g_numberImage[10];

// �֐��̃v���g�^�C�v�錾 ==================================================

//�v���C���[�̈ړ�����
void ManipulateMovingPlayer(ObjectPlayer *player);

//�v���C���[�̃W�����v����
void ManipulateJumpingPlayer(ObjectPlayer *player);

//�C�[�g�\�[�h���g�p
void UseEatsword(ObjectPlayer *player);

//�v���C���[�̈ړ�
void MovePlayer(ObjectPlayer *player);

//�v���C���[�̈ړ�����
void LimitAreaPlayer(ObjectPlayer *player);


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �v���C���[�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializePlayer(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//����
	LoadDivGraph("Resources/Images/����.png", 10, 5, 2, 32, 32, g_numberImage);

	// <���W>
	g_player.pos.x = (float)SCREEN_CENTER_X / 2;
	g_player.pos.y = (float)(STAGE_SIZE * 13) - (PLAYER_SIZE / 2);

	// <�f�[�^��̍��W>
	g_player.dataPos.x = (float)SCREEN_CENTER_X / 2;
	g_player.dataPos.y = (float)(STAGE_SIZE * 13) - (PLAYER_SIZE / 2);

	// <���x>
	g_player.vel.x = 0.0f;
	g_player.vel.y = 0.0f;

	// <�摜>
	//����
	LoadDivGraph("Resources/Images/����.png", 16, 4, 4, 64, 64, g_player.image[RUN].handle);
	g_player.image[RUN].extRate = 1.0f;
	g_player.image[RUN].angle = 0.0f;
	//�H�ׂ�
	LoadDivGraph("Resources/Images/�H�ׂ�.png", 16, 4, 4, 128, 128, g_player.image[EAT].handle);
	g_player.image[EAT].extRate = 1.0f;
	g_player.image[EAT].angle = 0.0f;
	//����U��
	LoadDivGraph("Resources/Images/����U��.png", 16, 4, 4, 128, 128, g_player.image[SWING].handle);
	g_player.image[SWING].extRate = 1.0f;
	g_player.image[SWING].angle = 0.0f;
	//��s
	LoadDivGraph("Resources/Images/Fly.png", 4, 4, 1, 64, 64, g_player.image[FLYING].handle);
	g_player.image[FLYING].extRate = 0.8f;
	g_player.image[FLYING].angle = 0.0f;
	//�\�H
	LoadDivGraph("Resources/Images/�H�ׂ�2.png", 16, 4, 4, 384, 384, g_player.image[GLUTTONY].handle);
	g_player.image[GLUTTONY].extRate = 1.0f;
	g_player.image[GLUTTONY].angle = 0.0f;

	// <�A�j���[�V����>
	//����
	g_player.animation[RUN].numFrames = 15;
	g_player.animation[RUN].frameDuration = (int)((ANIME_SPEED_RUN * 60) / g_player.animation[RUN].numFrames);
	g_player.animation[RUN].frameNum = 0;
	g_player.animation[RUN].elapsedTime = 0;
	g_player.animation[RUN].state = 0;
	//�H�ׂ�
	g_player.animation[EAT].numFrames = 15;
	g_player.animation[EAT].frameDuration = (int)((ANIME_SPEED_EAT * 60) / g_player.animation[EAT].numFrames);
	g_player.animation[EAT].frameNum = 0;
	g_player.animation[EAT].elapsedTime = 0;
	g_player.animation[EAT].state = 0;
	//����U��
	g_player.animation[SWING].numFrames = 15;
	g_player.animation[SWING].frameDuration = (int)((ANIME_SPEED_EAT * 60) / g_player.animation[SWING].numFrames);
	g_player.animation[SWING].frameNum = 0;
	g_player.animation[SWING].elapsedTime = 0;
	g_player.animation[SWING].state = 0;
	//��s
	g_player.animation[FLYING].numFrames = 3;
	g_player.animation[FLYING].frameDuration = 0;
	g_player.animation[FLYING].frameNum = 0;
	g_player.animation[FLYING].elapsedTime = 0;
	g_player.animation[FLYING].state = 0;
	//�\�H
	g_player.animation[GLUTTONY].numFrames = 15;
	g_player.animation[GLUTTONY].frameDuration = (int)((ANIME_SPEED_GLUTTONY * 60) / g_player.animation[GLUTTONY].numFrames);
	g_player.animation[GLUTTONY].frameNum = 0;
	g_player.animation[GLUTTONY].elapsedTime = 0;
	g_player.animation[GLUTTONY].state = 0;

	// <����>
	g_player.action = RUN;

	// <���]>
	g_player.turn = FALSE;

	// <���>
	g_player.state = 1;

	// <�^�C�v>
	g_player.type = NORMAL;

	// <����\�͂̎g�p����>
	g_player.count = 0;

	// <�̗�>
	g_player.hp = MAX_HP;

#if DEBUG
	g_player.type = FLY;
#endif

}



//----------------------------------------------------------------------
//! @brief �v���C���[�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdatePlayer(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	// <�v���C���[�̑���>
	if (g_flyFlag == FALSE)
	{
		//�ړ�
		ManipulateMovingPlayer(&g_player);

		//�W�����v
		ManipulateJumpingPlayer(&g_player);

		//�C�[�g�\�[�h���g�p
		UseEatsword(&g_player);

		//SE�̒�~
		StopSoundMem(g_playSE[15]);
	}
	else
	{
		//�ړ�
		ManipulateFlyingPlayer(&g_player);

		//SE�̍Đ�
		if (CheckSoundMem(g_playSE[15]) != 1)
		{
			PlaySoundMem(g_playSE[15], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	//����\�͂��g�p
	UseSpecialPower(&g_player);


	// <�v���C���[�̓���X�V>
	//�ړ�
	MovePlayer(&g_player);

	//�ړ�����
	LimitAreaPlayer(&g_player);

	// <�A�j���[�V�����̍X�V>
	UpdataAnimation(&g_player.animation[g_player.action]);

	//�̗͐؂�
	if (g_player.hp <= 0)
	{
		g_player.state = 0;
	}

}



//----------------------------------------------------------------------
//! @brief �v���C���[�̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RendarPlayer(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	// <�v���C���[> -----------------------------------------------

	//HP�Q�[�W�̕`��
	DrawHPGauge(10.0f, 10.0f, 200.0f, 30.0f, MAX_HP, g_player.hp);

	//�^�C�}�[�̕`��
	DrawTimer((float)SCREEN_CENTER_X, 50.0f, (int)g_player.count / 60, g_numberImage, g_player.type);

	//�v���C���[���g�p����Ă���
	if (g_player.state == 1)
	{
		switch (g_player.action)
		{
		case RUN:
			DrawRotaGraphF(g_player.pos.x, g_player.pos.y,
				g_player.image[g_player.action].extRate,
				g_player.image[g_player.action].angle,
				g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
				TRUE, g_player.turn);
			break;
		case EAT:
			//���]�����ۂ̍��W�̏C��
			if (g_player.turn == TRUE)
			{
				DrawRotaGraphF(g_player.pos.x - PLAYER_SIZE / 2, g_player.pos.y,
					g_player.image[g_player.action].extRate,
					g_player.image[g_player.action].angle,
					g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
					TRUE, g_player.turn);
			}
			else
			{
				DrawRotaGraphF(g_player.pos.x + PLAYER_SIZE / 2, g_player.pos.y,
					g_player.image[g_player.action].extRate,
					g_player.image[g_player.action].angle,
					g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
					TRUE, g_player.turn);
			}
			break;
		case SWING:
			DrawRotaGraphF(g_player.pos.x, g_player.pos.y,
				g_player.image[g_player.action].extRate,
				g_player.image[g_player.action].angle,
				g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
				TRUE, g_player.turn);
			break;
		case FLYING:
			DrawRotaGraphF(g_player.pos.x, g_player.pos.y,
				g_player.image[g_player.action].extRate,
				g_player.image[g_player.action].angle,
				g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
				TRUE, g_player.turn);
			break;
		case GLUTTONY:
			//���]�����ۂ̍��W�̏C��
			if (g_player.turn == TRUE)
			{
				DrawRotaGraphF(g_player.pos.x - PLAYER_SIZE * 2, g_player.pos.y - 160.0f,
					g_player.image[g_player.action].extRate,
					g_player.image[g_player.action].angle,
					g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
					TRUE, g_player.turn);
			}
			else
			{
				DrawRotaGraphF(g_player.pos.x + PLAYER_SIZE * 2, g_player.pos.y - 160.0f,
					g_player.image[g_player.action].extRate,
					g_player.image[g_player.action].angle,
					g_player.image[g_player.action].handle[g_player.animation[g_player.action].frameNum],
					TRUE, g_player.turn);
			}
			break;
		default:

			break;
		}
		
	}


	// <�f�o�b�O���> ---------------------------------------------
#if DEBUG
	//�v���C���[�̍��W
	DrawCircleAA(g_player.pos.x, g_player.pos.y, 2.0f, 100, COLOR_RED, TRUE);
	DrawFormatString(0, 0, COLOR_RED, "posX=%f\nposY=%f\ndataX=%f\ndataY=%f\ncamera=%f", g_player.pos.x, g_player.pos.y, g_player.dataPos.x, g_player.dataPos.y,g_cameraPos.x);
#endif

}



//----------------------------------------------------------------------
//! @brief �v���C���[�̈ړ�����̏���
//!
//! @param[player] ���삷��v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ManipulateMovingPlayer(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	



	//���[�J���ϐ��̏�����//--------------------------------------------
	



	//�����̓��e//------------------------------------------------------

	//�v���C���[���g�p����Ă���
	if (player->state == 1)
	{
		//���x�̏�����
		player->vel.x = 0.0f;

		//�A�N�V�������s���Ă��Ȃ�
		if ((player->animation[EAT].state | player->animation[SWING].state | player->animation[GLUTTONY].state) == 0)
		{
			//�L�[����
			if (((g_currentInputState)&PAD_INPUT_LEFT) != 0)	//���L�[
			{
				//���x��^����
				player->vel.x = -MOVE_SPEED;

				//�摜�𔽓]
				player->turn = TRUE;

				//�A�j���[�V�������J�n
				player->action = RUN;
				player->animation[RUN].state = 1;
			}
			else if (((g_currentInputState)&PAD_INPUT_RIGHT) != 0)	//�E�L�[
			{
				//���x��^����
				player->vel.x = MOVE_SPEED;

				//�摜�𔽓]
				player->turn = FALSE;

				//�A�j���[�V�������J�n
				player->action = RUN;
				player->animation[RUN].state = 1;
			}
			else
			{
				//�A�j���[�V���������Z�b�g
				ResetAnimation(&player->animation[RUN]);
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief �v���C���[�̃W�����v����̏���
//!
//! @param[player] ���삷��v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ManipulateJumpingPlayer(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	// <�W�����v>
	// �t���O
	static BOOL jumpFlag = FALSE;

	// ���x
	static float jumpSpeed;


	int i;

	//�����蔻��̌���
	BOOL result;

	float playerX;
	float playerY;
	float width;
	float height;
	float boxX;
	float boxY;


	//���[�J���ϐ��̏�����//--------------------------------------------
	



	//�����̓��e//------------------------------------------------------

	// �W�����v�̏I��
	for (i = 0; i < g_stageObjectNumber; i++)
	{
		if (g_objectStage[i].state == 1)
		{
			playerX = player->dataPos.x;
			playerY = player->dataPos.y;
			width = PLAYER_SIZE / 4;
			height = PLAYER_SIZE;
			boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
			boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

			result = DetectCollisionBoxAndBox(playerX, playerY, width, height, boxX, boxY, STAGE_SIZE, STAGE_SIZE);

			if (result == TRUE)
			{
				if (playerY <= boxY)
				{
					//�W�����v�\�ɂ���
					jumpFlag = FALSE;

					//�W�����v�͂��Ȃ���
					jumpSpeed = 0.0f;
				}
			}
		}
	}

	// �W�����v�̊J�n
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_UP) != 0)	//��L�[
	{
		//�W�����v���Ă��Ȃ�
		if (jumpFlag == FALSE)
		{
			//�W�����v�J�n
			jumpFlag = TRUE;
			
			//�W�����v�͂�^����
			jumpSpeed = JUMP_POWER;

			//SE�̍Đ�
			PlaySoundMem(g_playSE[4], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	// �W�����v���̏���
	if (jumpFlag == TRUE)
	{
		//�A�j���[�V���������Z�b�g
		ResetAnimation(player->animation);

		//���x��^����
		player->vel.y = -jumpSpeed;

		//����
		jumpSpeed--;

		//�A�j���[�V���������Z�b�g
		ResetAnimation(&player->animation[RUN]);
	}

}



//----------------------------------------------------------------------
//! @brief �C�[�g�\�[�h�̎g�p����
//!
//! @param[player] �v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UseEatsword(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	



	//���[�J���ϐ��̏�����//--------------------------------------------
	



	//�����̓��e//------------------------------------------------------

	//�C�[�g�\�[�h���g�p����Ă��Ȃ�
	if ((player->animation[EAT].state | player->animation[SWING].state | player->animation[GLUTTONY].state) == 0)
	{
		//�C�[�g�\�[�h���g�p
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_1) != 0)	//Z�L�[
		{
			player->action = EAT;
			player->animation[EAT].state = 1;
		}
	}

}



//----------------------------------------------------------------------
//! @brief �v���C���[�̈ړ�����
//!
//! @param[player] �ړ�����v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MovePlayer(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------




	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------

	//��s���Ă��Ȃ�
	if (g_flyFlag == FALSE)
	{
		//����
		player->vel.y += GRAVITY;

		//�������x�̐���
		if (player->vel.y >= MAX_FALL_SPEED)
		{
			player->vel.y = MAX_FALL_SPEED;
		}
	}
	else
	{
		//�ő呬�x
		//X����
		if (player->vel.x >= MOVE_SPEED)
		{
			player->vel.x = MOVE_SPEED;
		}
		if (player->vel.x <= -MOVE_SPEED)
		{
			player->vel.x = -MOVE_SPEED;
		}
		//Y����
		if (player->vel.y >= MOVE_SPEED)
		{
			player->vel.y = MOVE_SPEED;
		}
		if (player->vel.y <= -MOVE_SPEED)
		{
			player->vel.y = -MOVE_SPEED;
		}
	}


	//�A�N�V�������s���Ă���
	if ((player->animation[EAT].state | player->animation[SWING].state | player->animation[GLUTTONY].state) == 1)
	{
		//�ړ����~
		player->vel.x = 0.0f;
		player->vel.y = 0.0f;
	}

	//���W�̍X�V
	if (player->dataPos.x < SCREEN_CENTER_X / 2)
	{
		player->pos.x += player->vel.x;
	}
	player->pos.y += player->vel.y;
	if (player->dataPos.x >= SCREEN_LEFT + PLAYER_SIZE / 3)
	{
		player->dataPos.x += player->vel.x;
	}
	
	player->dataPos.y += player->vel.y;

	//SE�̍Đ�
	if (player->animation[RUN].state == 1)
	{
		if (CheckSoundMem(g_playSE[3]) == 0)
		{
			PlaySoundMem(g_playSE[3], DX_PLAYTYPE_BACK, TRUE);
		}
	}
	else
	{
		//SE�̒�~
		StopSoundMem(g_playSE[3]);
	}

}



//----------------------------------------------------------------------
//! @brief �v���C���[�̈ړ���������
//!
//! @param[player] �ړ���������v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void LimitAreaPlayer(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	int i;

	//�����蔻��̌���
	BOOL result;

	float playerX;
	float playerY;
	float width;
	float height;
	float boxX;
	float boxY;


	//���[�J���ϐ��̏�����//--------------------------------------------
	
	


	//�����̓��e//------------------------------------------------------

	//�v���C���[�̍��W������̂���I�u�W�F�N�g�������ꍇ
	for (i = 0; i < g_stageObjectNumber; i++)
	{
		if (g_objectStage[i].state == 1)
		{
			if (player->turn == false)
			{
				//�E
				playerX = player->dataPos.x + PLAYER_SIZE / 3;
				playerY = player->dataPos.y;
				boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
				boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

				result = DetectCollisionBoxAndPoint(boxX, boxY, STAGE_SIZE, STAGE_SIZE, playerX, playerY);

				if (result == TRUE)
				{
					player->dataPos.x -= player->vel.x;
					player->vel.x = 0.0f;
				}
			}
			else
			{
				//��
				playerX = player->dataPos.x - PLAYER_SIZE / 3;
				playerY = player->dataPos.y;
				boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
				boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

				result = DetectCollisionBoxAndPoint(boxX, boxY, STAGE_SIZE, STAGE_SIZE, playerX, playerY);

				if (result == TRUE)
				{
					player->dataPos.x -= player->vel.x;
					player->vel.x = 0.0f;
				}
			}
			

			playerX = player->dataPos.x;
			playerY = player->dataPos.y;
			width = PLAYER_SIZE / 4;
			height = PLAYER_SIZE;
			boxX = g_objectStage[i].pos.x + STAGE_SIZE / 2;
			boxY = g_objectStage[i].pos.y + STAGE_SIZE / 2;

			result = DetectCollisionBoxAndBox(playerX, playerY, width, height, boxX, boxY, STAGE_SIZE, STAGE_SIZE);

			if (result == TRUE)
			{
				//��
				if (playerY <= boxY)
				{
					player->pos.y = g_objectStage[i].pos.y - STAGE_SIZE;
					player->dataPos.y = g_objectStage[i].pos.y - STAGE_SIZE;
					player->vel.y = 0.0f;
				}
				//��
				else
				{
					player->pos.y = g_objectStage[i].pos.y + STAGE_SIZE * 2;
					player->dataPos.y = g_objectStage[i].pos.y + STAGE_SIZE * 2;
					player->vel.y = 0.0f;
				}
			}
		}
	}

	//��ʏ�ł̈ړ�����
	if (player->pos.x < SCREEN_LEFT + PLAYER_SIZE / 3)
	{
		player->pos.x = SCREEN_LEFT + PLAYER_SIZE / 3;
	}
	if (player->dataPos.x < SCREEN_LEFT + PLAYER_SIZE / 3)
	{
		player->dataPos.x = SCREEN_LEFT + PLAYER_SIZE / 3;
	}

	//�������ꍇ
	if (player->pos.y >= SCREEN_BOTTOM + PLAYER_SIZE)
	{
		player->state = 0;
	}

	// <�f�o�b�O���> ------------------------------
#if DEBUG
	//DrawFormatString(0, 0, COLOR_RED, "stageDataT=%d\nstageDataB=%d", g_stageData[arrayPosT][arrayPosX], g_stageData[arrayPosB][arrayPosX]);
#endif

}
