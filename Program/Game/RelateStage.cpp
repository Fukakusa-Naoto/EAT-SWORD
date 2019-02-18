//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateStage.cpp
//!
//! @brief  �X�e�[�W�֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <stdio.h>
#include "GameMain.h"
#include "RelateStage.h"
#include "RelatePlayer.h"
#include "RelateCamera.h"
#include "RelateUI.h"
#include "RelateAnimation.h"



// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================

// <�w�i>
BackGround g_backGround;

// <�X�e�[�W>
int g_stageData[STAGE_HEIGHT][STAGE_WIDTH];

ObjectStage g_objectStage[MAX_STAGECHIP];

HGRP g_stageImage[10];

HGRP g_goalImage;

int g_stageObjectNumber;

// �X�e�[�WID
int g_stageId;

//�A�j���[�V����
StageAnimation g_stageAnimation[100];


// �֐��̃v���g�^�C�v�錾 ==================================================

//�w�i�̃X�N���[��
void ScrollBackGround(BackGround *backGround, ObjectPlayer *player);

//�w�i�̕`��
void DrawBackGround(BackGround backGround);

//�X�e�[�W�̓ǂݍ���
void LoadStage(char *stageFile, int width, int height);

//�`���[�g���A�����̑������
void ExplainOperation1(Vec2D pos);
void ExplainOperation2(Vec2D pos);


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �X�e�[�W�̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeStage(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�X�e�[�W�t�@�C��
	char *stageFile[MAX_STAGE];

	//�z��Ɏg�p
	int x;
	int y;

	//���[�J���ϐ��̏�����//--------------------------------------------
	stageFile[0] = "Resources/StageData/stage.csv";
	stageFile[1] = "Resources/StageData/stage1.csv";
	stageFile[2] = "Resources/StageData/stage2.csv";
	stageFile[3] = "Resources/StageData/stage3.csv";
	stageFile[4] = "Resources/StageData/stage4.csv";
	stageFile[5] = "Resources/StageData/tutorial.csv";
	stageFile[6] = "Resources/StageData/tutorial2.csv";


	//�����̓��e//------------------------------------------------------

	// <�w�i>
	g_backGround.pos.x = 0.0f;
	g_backGround.pos.y = 0.0f;
	// �摜�̓ǂݍ���
	g_backGround.handle = LoadGraph("Resources/Images/�w�i.png");

	// <�X�e�[�W>
	g_stageObjectNumber = 0;

	// �摜�̓ǂݍ���
	LoadDivGraph("Resources/Images/STAGE_IMAGE.png", 3, 3, 1, 64, 64, g_stageImage);
	LoadStage(stageFile[g_stageId], STAGE_WIDTH, STAGE_HEIGHT);

	for (y = 0; y < STAGE_HEIGHT; y++)
	{
		for (x = 0; x < STAGE_WIDTH; x++)
		{
			if (g_stageData[y][x] != 0)
			{
				//�X�e�[�W�I�u�W�F�N�g�𐶐�
				CreateStageObject(&g_objectStage[g_stageObjectNumber], (float)(STAGE_SIZE*x), (float)(STAGE_SIZE*y), g_stageData[y][x]);
			}
		}
	}

	//�S�[���摜�̓ǂݍ���
	g_goalImage = LoadGraph("Resources/Images/�S�[��.png");

	//�A�j���[�V����
	for (x = 0; x < 100; x++)
	{
		g_stageAnimation[x].pos.x = 0.0f;
		g_stageAnimation[x].pos.y = 0.0f;
		LoadDivGraph("Resources/Images/Burn.png", 3, 3, 1, 64, 64, g_stageAnimation[x].image.handle);
		g_stageAnimation[x].animation.elapsedTime = 0;
		g_stageAnimation[x].animation.frameDuration = 30;
		g_stageAnimation[x].animation.frameNum = 0;
		g_stageAnimation[x].animation.numFrames = 2;
		g_stageAnimation[x].animation.state = 0;
	}

}



//----------------------------------------------------------------------
//! @brief �X�e�[�W�̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateStage(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	//�z��Ɏg�p
	int i;


	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�w�i�̃X�N���[��
	ScrollBackGround(&g_backGround, &g_player);

	//�A�j���[�V�����̍X�V
	for (i = 0; i < 100; i++)
	{
		if (g_stageAnimation[i].animation.state == 1)
		{
			UpdataAnimation(&g_stageAnimation[i].animation);
		}
	}

}



//----------------------------------------------------------------------
//! @brief �X�e�[�W�̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RendarStage(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------

	//�z��Ɏg�p
	int i;

	//�`����W
	float x1;
	float y1;
	float x2;
	float y2;


	//���[�J���ϐ��̏�����//--------------------------------------------
	



	//�����̓��e//------------------------------------------------------

	//�w�i�̕`��
	DrawBackGround(g_backGround);

	//�S�[���̕`��
	DrawGraphF(((STAGE_WIDTH - 15)*STAGE_SIZE) - g_cameraPos.x, (13 * STAGE_SIZE) - 128, g_goalImage, TRUE);

	//�X�e�[�W
	for (i = 0; i < g_stageObjectNumber; i++)
	{
		if (g_objectStage[i].state == 1)
		{
			if ((g_objectStage[i].pos.x >= g_cameraPos.x - STAGE_SIZE) && (g_objectStage[i].pos.x <= g_cameraPos.x + CAMERA_WIDTH + STAGE_SIZE))
			{
				x1 = g_objectStage[i].pos.x - g_cameraPos.x;
				x2 = g_objectStage[i].pos.x + (float)STAGE_SIZE - g_cameraPos.x;
				y1 = g_objectStage[i].pos.y;
				y2 = g_objectStage[i].pos.y + (float)STAGE_SIZE;

				DrawExtendGraphF(x1, y1, x2, y2, g_stageImage[g_objectStage[i].type - 1], TRUE);
			}
		}
	}

	//�`���[�g���A�����̑�������̕`��
	if (g_stageId == 5)
	{
		ExplainOperation1(g_player.dataPos);
	}
	if (g_stageId == 6)
	{
		ExplainOperation2(g_player.dataPos);
	}

	//�A�j���[�V����
	for (i = 0; i < 100; i++)
	{
		if (g_stageAnimation[i].animation.state == 1)
		{
			x1 = g_stageAnimation[i].pos.x - g_cameraPos.x;
			x2 = g_stageAnimation[i].pos.x + (float)STAGE_SIZE - g_cameraPos.x;
			y1 = g_stageAnimation[i].pos.y;
			y2 = g_stageAnimation[i].pos.y + (float)STAGE_SIZE;

			DrawExtendGraphF(x1, y1, x2, y2, g_stageAnimation[i].image.handle[g_stageAnimation[i].animation.frameNum], TRUE);
		}
	}

}



//----------------------------------------------------------------------
//! @brief �X�e�[�W�I�u�W�F�N�g�̐�������
//!
//! @param[stageObject] ��������X�e�[�W�I�u�W�F�N�g
//! @param[posX] �X�e�[�W�I�u�W�F�N�g��X���W
//! @param[posY] �X�e�[�W�I�u�W�F�N�g��Y���W
//! @param[type] �X�e�[�W�I�u�W�F�N�g�̃^�C�v
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void CreateStageObject(ObjectStage *stageObject, float posX,float posY,int type)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	stageObject->pos.x = posX;
	stageObject->pos.y = posY;
	stageObject->type = type;
	stageObject->state = 1;

	g_stageObjectNumber++;
}



//----------------------------------------------------------------------
//! @brief �w�i�̃X�N���[������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ScrollBackGround(BackGround *backGround, ObjectPlayer *player)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�w�i���v���C���[�ɍ��킹�ăX�N���[��������
	if ((player->vel.x != 0) && (player->dataPos.x > SCREEN_CENTER_X / 2) && (g_cameraPos.x < (STAGE_WIDTH*STAGE_SIZE) - CAMERA_WIDTH))
	{
		backGround->pos.x += -(player->vel.x / 4);
	}
	
	//�w�i�����炷
	if (backGround->pos.x < -SCREEN_WIDTH)
	{
		backGround->pos.x = 0;
	}
	if (backGround->pos.x > 0)
	{
		backGround->pos.x = -SCREEN_WIDTH;
	}


}



//*---------------------------------------------------------------------
//* �X�e�[�W�f�[�^�̓ǂݍ���
//*
//* @param [file] �X�e�[�W�t�@�C����
//* @param [Width] �X�e�[�W�̕�
//* @param [Height] �X�e�[�W�̍���
//*
//* @return �Ȃ�
//*---------------------------------------------------------------------
void LoadStage(char *file, int width, int height)
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
	fp = fopen(file, "r");

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

				g_stageData[i][j] = (int)number;
				p++;
			}
		}
	}

	//�t�@�C�������
	fclose(fp);

}



//----------------------------------------------------------------------
//! @brief �w�i�̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void DrawBackGround(BackGround backGround)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//1����
	DrawGraphF(backGround.pos.x, backGround.pos.y, backGround.handle, TRUE);

	//2����
	DrawGraphF(backGround.pos.x + SCREEN_WIDTH, backGround.pos.y, backGround.handle, TRUE);

}



//----------------------------------------------------------------------
//! @brief �`���[�g���A�����̑������1�̏���
//!
//! @param[pos] ���W
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ExplainOperation1(Vec2D pos)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	char *text;

	float x;
	float y;

	//���[�J���ϐ��̏�����//--------------------------------------------
	
	x = 500.0f;
	y = 50.0f;

	//�����̓��e//------------------------------------------------------

	//�ړ�
	if (pos.x <= 300)
	{
		text = "���E�L�[�ňړ�";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//�W�����v
	if ((pos.x >= 300) && (pos.x <= 750))
	{
		text = "��L�[�ŃW�����v";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//�H�ׂ�
	if ((pos.x >= 750) && (pos.x <= 1120))
	{
		text = "Z�L�[�ŐH�ׂ�";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//�U��
	if ((pos.x >= 2300) && (pos.x <= 2800))
	{
		text = "Z�L�[�ōU��";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}

}



//----------------------------------------------------------------------
//! @brief �`���[�g���A�����̑������2�̏���
//!
//! @param[pos] ���W
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void ExplainOperation2(Vec2D pos)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	char *text;

	float x;
	float y;

	//���[�J���ϐ��̏�����//--------------------------------------------

	x = 500.0f;
	y = 50.0f;

	//�����̓��e//------------------------------------------------------

	//����\��
	if (pos.x <= 360)
	{
		text = "����̓G��H�ׂ��\n����\�͂��g����";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//����
	if ((pos.x >= 360) && (pos.x <= 700))
	{
		text = "�J�E���g��0�ɂȂ��\n�g���Ȃ��Ȃ�";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//�a��
	if ((pos.x >= 700) && (pos.x <= 1400))
	{
		text = "X�L�[�Ŏa�����΂���";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//��s
	if ((pos.x >= 1760) && (pos.x <= 2200))
	{
		text = "X�L�[�Ŕ�s���[�h��\n�؂�ւ���";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//����
	if ((pos.x >= 2200) && (pos.x <= 2970))
	{
		text = "�\���L�[�ňړ�";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//��
	if ((pos.x >= 3350) && (pos.x <= 4470))
	{
		text = "X�L�[�ŕX�̃u���b�N��\n��������";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//�H�ׂ�
	if ((pos.x >= 4830) && (pos.x <= 5900))
	{
		text = "X�L�[�ň�C��\n�H�ׂ邱�Ƃ��ł���";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}
	//�I��
	if (pos.x >= 6000)
	{
		text = "�ȏ�Ń`���[�g���A����\n�I���ł�";

		//�e�L�X�g
		DrawTextBox(x, y, 210.0f, 50.0f, text);
	}

}
