//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file  RelateUI.cpp
//!
//! @brief  UI�֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "RelateUI.h"


// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================
//�摜
HGRP g_images[4];



// �֐��̃v���g�^�C�v�錾 ==================================================




// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief UI�̏���������
//!
//! @param[no] 
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeUI(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	



	//���[�J���ϐ��̏�����//--------------------------------------------
	



	//�����̓��e//------------------------------------------------------
	//�摜�̓ǂݍ���
	LoadDivGraph("Resources/Images/UI.png", 4, 4, 1, 70, 70, g_images);



}



//----------------------------------------------------------------------
//! @brief HP�Q�[�W�̕`�揈��
//!
//! @param[x] �`�悷�鍶���X���W
//! @param[y] �`�悷�鍶���Y���W
//! @param[width] ����
//! @param[height] ����
//! @param[max] �ő�l
//! @param[now] ���݂�HP
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawHPGauge(float x, float y, float width, float height, int max, int now)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;

	//�ڐ�
	float scaleX1;
	float scaleX2;
	float scaleWidth;



	//���[�J���ϐ��̏�����//--------------------------------------------
	scaleWidth = width / (float)max;



	//�����̓��e//------------------------------------------------------

	//�g
	DrawBoxAA(x - 1, y - 1, x + width + 1, y + height + 1, COLOR_BLACK, TRUE);

	for (i = 1; i <= max; i++)
	{
		scaleX1 = x + scaleWidth*(i - 1);
		scaleX2 = scaleX1 + scaleWidth;

		if (i <= now)
		{
			DrawBoxAA(scaleX1, y, scaleX2, y + height, COLOR_WHITE, FALSE);
		}
		else
		{
			DrawBoxAA(scaleX1, y, scaleX2, y + height, COLOR_WHITE, TRUE);
		}
	}
}



//----------------------------------------------------------------------
//! @brief ���Ԃ̕`�揈��
//!
//! @param[x] X���W
//! @param[y] Y���W
//! @param[time] �\������
//! @param[handle] �O���t�B�b�N�n���h��
//! @param[type] �^�C�v
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawTimer(float x, float y, int time, HGRP handle[], Type type)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�w�i
	switch (type)
	{
	case NORMAL:
		
		break;
	case SWORD:
		DrawRotaGraphF(x, y, 1.0, 0.0, g_images[0], TRUE, FALSE);
		break;
	case FIRE:
		DrawRotaGraphF(x, y - 15.0f, 1.0, 0.0, g_images[1], TRUE, FALSE);
		break;
	case FLY:
		DrawRotaGraphF(x, y, 1.0, 0.0, g_images[2], TRUE, FALSE);
		break;
	case BIG:
		DrawRotaGraphF(x, y, 1.0, 0.0, g_images[3], TRUE, FALSE);
		break;
	default:

		break;
	}

	//�g
	DrawCircleAA(x, y, 20.0f, 100, COLOR_WHITE, TRUE);
	DrawCircleAA(x, y, 20.0f, 100, COLOR_BLACK, FALSE);

	//����
	//�\�̌�
	DrawRotaGraphF(x - 8.0f, y, 0.5, 0.0, handle[time / 10], TRUE, FALSE);
	//��̌�
	DrawRotaGraphF(x + 8.0f, y, 0.5, 0.0, handle[time % 10], TRUE, FALSE);

}



//----------------------------------------------------------------------
//! @brief �{�̕`�揈��
//!
//! @param[x] X���W
//! @param[y] Y���W
//! @param[width] ��
//! @param[height] ����
//! @param[space] �{�̊J��
//! @param[upperHandle] ��{�̉摜
//! @param[lowerHandle] ���{�̉摜
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawJaw(float x, float y, float width, float height, float spece, HGRP upperHandle, HGRP lowerHandle)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//��{�̕`��
	DrawExtendGraphF(x - width / 2, y - (height * 3 / 4) - spece, x + width / 2, y + height / 4 - spece, upperHandle, TRUE);

	//���{�̕`��
	DrawExtendGraphF(x - width / 2, y - height / 4 + spece, x + width / 2, y + (height * 3 / 4) + spece, lowerHandle, TRUE);

}



//----------------------------------------------------------------------
//! @brief �e�L�X�g�{�b�N�X�̕`�揈��
//!
//! @param[x] X���W
//! @param[y] Y���W
//! @param[width] ��
//! @param[height] ����
//! @param[text] �e�L�X�g
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawTextBox(float x, float y, float width, float height, char *text)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�g
	DrawBoxAA(x - width / 2, y - height / 2, x + width / 2, y + height / 2, COLOR_BLACK, TRUE);
	DrawBoxAA(x - width / 2 + 1.0f, y - height / 2 + 1.0f, x + width / 2 - 1.0f, y + height / 2 - 1.0f, COLOR_WHITE, TRUE);

	//�e�L�X�g
	DrawStringF(x - width / 2 + 10, y - height / 4, text, COLOR_BLACK);

}
