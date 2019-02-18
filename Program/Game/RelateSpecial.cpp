//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateSpecial.cpp
//!
//! @brief  ����\�͊֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <math.h>
#include "GameMain.h"
#include "RelateSpecial.h"
#include "RelateBullet.h"
#include "RelatePlayer.h"
#include "RelateAnimation.h"


// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================
//�����x
#define ACCEL_SPEED (5.0f)

//���C�W��
#define FRICTION (0.9f)


// �O���[�o���ϐ��̒�` ====================================================
//��s�t���O
BOOL g_flyFlag;



// �֐��̃v���g�^�C�v�錾 ==================================================
//����\�� Type-SWORD
void SpecialPowerTypeSword(ObjectPlayer *player);

//����\�� Type-FIRE
void SpecialPowerTypeFire(ObjectPlayer *player);

//����\�� Type-FLY
void SpecialPowerTypeFly(ObjectPlayer *player);

//����\�� Type-BIG
void SpecialPowerTypeBig(ObjectPlayer *player);


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief ����\�͂̎g�p����
//!
//! @param[player] �v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UseSpecialPower(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------




	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------

	//�C�[�g�\�[�h���g�p����Ă��Ȃ�
	if (player->animation[EAT].state == 0)
	{
		switch (player->type)
		{
		case NORMAL:	//�m�[�}��
						//�Ȃ�
			break;
		case SWORD:		//�\�[�h
			SpecialPowerTypeSword(player);
			break;
		case FIRE:		//�t�@�C�A
			SpecialPowerTypeFire(player);
			break;
		case FLY:		//�t���C
			SpecialPowerTypeFly(player);
			break;
		case BIG:		//�r�b�O
			SpecialPowerTypeBig(player);
			break;
		default:

			break;
		}
	}

#if DEBUG

#else
	//����\�͂̎g�p���Ԃ̃J�E���g
	if (player->type != NORMAL)
	{
		player->count--;
	}

	//����\�͂̎��Ԑ؂�
	if (player->count <= 0)
	{
		//�ʏ탂�[�h�ɖ߂�
		player->type = NORMAL;

		if ((player->animation[EAT].state | player->animation[SWING].state | player->animation[GLUTTONY].state) == 0)
		{
			player->action = RUN;
		}

		//�A�j���[�V����
		ResetAnimation(&player->animation[SWING]);
	
	}

	//��s�t���O���Ȃ���
	if (player->type != FLY)
	{
		g_flyFlag = FALSE;
	}

#endif
	
}



//----------------------------------------------------------------------
//! @brief ����\�� Type-SWORD�̏���
//!
//! @param[player] �v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void SpecialPowerTypeSword(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//���ˍ��W
	float pointX;
	float pointY;

	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------
	//����\�͂��g�p
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_2) != 0)	//X�L�[
	{
		if (player->animation[SWING].state == 0)
		{
			player->action = SWING;
			player->animation[SWING].state = 1;
		}
	}

	//�a��������
	if (player->animation[SWING].frameNum == 10)
	{
		if (g_playerBullet.state == 0)
		{
			if (player->turn == FALSE)
			{
				//���W�̌v�Z
				pointX = player->dataPos.x + PLAYER_SIZE;
				pointY = player->dataPos.y;

				//���ˏ���
				ShotBullet(&g_playerBullet, 1, { 0.0f, 0.0f }, pointX, pointY, SPEED_BULLET_PLAYER, NORMAL_SHOT);
			}
			else
			{
				//���W�̌v�Z
				pointX = player->dataPos.x - PLAYER_SIZE;
				pointY = player->dataPos.y;

				//���ˏ���
				ShotBullet(&g_playerBullet, 1, { 0.0f, 0.0f }, pointX, pointY, -SPEED_BULLET_PLAYER, NORMAL_SHOT);
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief ����\�� Type-FIRE�̏���
//!
//! @param[player] �v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void SpecialPowerTypeFire(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	



	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------
	//����\�͂��g�p
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_2) != 0)	//X�L�[
	{
		if (player->animation[SWING].state == 0)
		{
			player->action = SWING;
			player->animation[SWING].state = 1;
		}
	}

}



//----------------------------------------------------------------------
//! @brief ����\�� Type-FLY�̏���
//!
//! @param[player] �v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void SpecialPowerTypeFly(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	


	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------
	//����\�͂��g�p
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_2) != 0)	//X�L�[
	{
		//��s���[�h��؂�ւ���
		if (g_flyFlag == FALSE)
		{
			g_flyFlag = TRUE;
			player->action = FLYING;
			ResetAnimation(&player->animation[RUN]);
		}
		else
		{
			g_flyFlag = FALSE;
			player->action = RUN;
		}
	}

}



//----------------------------------------------------------------------
//! @brief ����\�� Type-BIG�̏���
//!
//! @param[player] �v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void SpecialPowerTypeBig(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------

	//����\�͂��g�p
	if (((g_lastInputState&g_currentInputState)&PAD_INPUT_2) != 0)	//X�L�[
	{
		player->action = GLUTTONY;
		player->animation[GLUTTONY].state = 1;
	}

}



//----------------------------------------------------------------------
//! @brief ��s���̑��쏈��
//!
//! @param[player] �v���C���[
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ManipulateFlyingPlayer(ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�L�[�̓��͎��Ԃ̃J�E���g
	static int count = 0;

	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------

	//�v���C���[���g�p����Ă���
	if (player->state == 1)
	{

		//�A�N�V�������s���Ă��Ȃ�
		if ((player->animation[EAT].state | player->animation[SWING].state) == 0)
		{
			//�L�[����
			if (((g_currentInputState)&PAD_INPUT_LEFT) != 0)	//���L�[
			{
				//�J�E���g�𑝂₷
				count++;

				//���x��^����
				player->vel.x = -ACCEL_SPEED*((float)count / 60);

				//�摜�𔽓]
				player->turn = TRUE;
			}
			else if (((g_currentInputState)&PAD_INPUT_RIGHT) != 0)	//�E�L�[
			{
				//�J�E���g�𑝂₷
				count++;

				//���x��^����
				player->vel.x = ACCEL_SPEED*((float)count / 60);

				//�摜�𔽓]
				player->turn = FALSE;
			}
			else if (((g_currentInputState)&PAD_INPUT_UP) != 0)	//��L�[
			{
				//�J�E���g�𑝂₷
				count++;

				//���x��^����
				player->vel.y = -ACCEL_SPEED*((float)count / 60);
			}
			else if (((g_currentInputState)&PAD_INPUT_DOWN) != 0)	//���L�[
			{
				//�J�E���g�𑝂₷
				count++;

				//���x��^����
				player->vel.y = ACCEL_SPEED*((float)count / 60);
			}
			else
			{
				//�J�E���g�̏�����
				count = 0;
			}
		}
	}

	//���C�ɂ�錸��
	player->vel.x *= FRICTION;
	player->vel.y *= FRICTION;

	//X����
	if ((player->vel.x <= 0.005) && (player->vel.x >= -0.005))
	{
		player->vel.x = 0.0f;
	}
	//Y����
	if ((player->vel.y <= 0.005) && (player->vel.y >= -0.005))
	{
		player->vel.y = 0.0f;
	}
	
	//�A�j���[�V����
	player->animation[FLYING].frameNum = (int)fabs((double)player->vel.x);
	if (player->animation[FLYING].frameNum >= player->animation[FLYING].numFrames)
	{
		player->animation[FLYING].frameNum = 3;
	}

}