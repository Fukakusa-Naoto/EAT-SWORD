//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelatePause.cpp
//!
//! @brief  �|�[�Y�֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "RelatePause.h"
#include "RelateUI.h"


// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================

//�|�[�Y�̃t���O
BOOL g_pauseFlag;

//�摜
HGRP g_pauseImage;
HGRP g_cousorImage[2];

//�{
ObjectJaw g_cousor;

//�T�E���h
HGRP g_pauseSE[2];

// �֐��̃v���g�^�C�v�錾 ==================================================




// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �|�[�Y�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializePause(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�t���O
	g_pauseFlag = FALSE;

	//�摜�̓ǂݍ���
	g_pauseImage = LoadGraph("Resources/Images/Pause.png");

	//�{
	LoadDivGraph("Resources/Images/�{.png", 2, 1, 2, 640, 320, g_cousorImage);
	g_cousor.pos.x = (float)SCREEN_CENTER_X;
	g_cousor.pos.y = 165.0f;
	g_cousor.size.width = 150;
	g_cousor.size.height = 25;
	g_cousor.space = 17.0f;

	//�T�E���h�̓ǂݍ���
	g_pauseSE[0] = LoadSoundMem("Resources/Sounds/Cusor_SE.mp3");
	g_pauseSE[1] = LoadSoundMem("Resources/Sounds/decision_SE.mp3");

}



//----------------------------------------------------------------------
//! @brief �|�[�Y�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdatePause(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	static int selectId = 0;

	static BOOL selectFlag = FALSE;


	//���[�J���ϐ��̏�����//--------------------------------------------




	//�����̓��e//------------------------------------------------------

	//�L�[����
	if (selectFlag == FALSE)
	{
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_UP) != 0)	//��L�[
		{
			selectId--;
			//SE�̍Đ�
			PlaySoundMem(g_pauseSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_DOWN) != 0)	//���L�[
		{
			selectId++;
			//SE�̍Đ�
			PlaySoundMem(g_pauseSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_1) != 0)	//Z�L�[
		{
			selectFlag = TRUE;
			//SE�̍Đ�
			PlaySoundMem(g_pauseSE[1], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	//ID�̐���
	if (selectId <= 0)
	{
		selectId = 0;
	}
	if (selectId >= 2)
	{
		selectId = 2;
	}

	//�{�̍��W�X�V
	g_cousor.pos.y = 165.0f + 75.0f*(float)selectId;

	//�V�[���̈ړ�
	if (selectFlag == TRUE)
	{
		g_cousor.space--;

		if (g_cousor.space <= 0)
		{
			switch (selectId)
			{
				case 0:
					//���ɖ߂�
					selectId = 0;
					g_cousor.space = 17.0f;
					selectFlag = FALSE;
					//�Q�[���ɖ߂�
					g_pauseFlag = FALSE;
					break;
				case 1:
					//���ɖ߂�
					selectId = 0;
					g_cousor.space = 17.0f;
					selectFlag = FALSE;
					//�t���O��߂�
					g_pauseFlag = FALSE;
					//�X�e�[�W�Z���N�g��
					ChangeScene(SCENE_SELECT);
					break;
				case 2:
					//���ɖ߂�
					selectId = 0;
					g_cousor.space = 17.0f;
					selectFlag = FALSE;
					//�t���O��߂�
					g_pauseFlag = FALSE;
					//�X�e�[�W�Z���N�g��
					ChangeScene(SCENE_TITLE);
					break;
			default:

				break;
			}
		}
	}

}



//----------------------------------------------------------------------
//! @brief �|�[�Y�̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderPause(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�|�[�Y���
	DrawGraph(160, 96, g_pauseImage, TRUE);

	//�{�̕`��
	DrawJaw(g_cousor.pos.x, g_cousor.pos.y, (float)g_cousor.size.width, (float)g_cousor.size.height, g_cousor.space, g_cousorImage[0], g_cousorImage[1]);

}