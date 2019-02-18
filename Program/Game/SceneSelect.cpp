//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneSelect.cpp
//!
//! @brief  �Z���N�g�V�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <math.h>
#include "GameMain.h"
#include "SceneSelect.h"
#include "RelateAnimation.h"
#include "RelateStage.h"
#include "RelateDetectCollition.h"


// �f�[�^�^�̒�` ==========================================================
//ObjectCursor�^
struct Tag_ObjectCursor
{
	Vec2D pos;
	float range;
};
typedef struct Tag_ObjectCursor ObjectCursor;

//ObjectChar�^
struct Tag_ObjectChar
{
	Vec2D pos;
	Vec2D vel;
	Image image;
	Animation animation;
	BOOL turn;
};
typedef struct Tag_ObjectChar ObjectChar;


// �萔�̒�` ==============================================================

//�L�����N�^�[�̈ړ����x
#define MOVE_SPEED (2.0f)


// �O���[�o���ϐ��̒�` ====================================================

//�摜
HGRP g_selectImage;

//�J�[�\��
ObjectCursor g_cursor;

//�L�����N�^�[
ObjectChar g_character;

//�T�E���h
//BGM
HSND g_selectBGM;
//SE
HSND g_selectSE[2];


// �֐��̃v���g�^�C�v�錾 ==================================================

//�J�[�\���̈ړ�
void MoveCharacter(ObjectChar *character, Vec2D target);


// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �Z���N�g�V�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeSelect(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�摜�̓ǂݍ���
	g_selectImage = LoadGraph("Resources/Images/SELECT.png");

	if (g_stageId == 5)
	{
		g_stageId = 0;
	}

	//�J�[�\��
	g_cursor.pos.x = 70.0f;
	g_cursor.pos.y = 230.0f;
	g_cursor.range = 5.0f;

	//�L�����N�^�[
	g_character.pos.x = 70.0f;
	g_character.pos.y = 230.0f;
	g_character.vel.x = 0.0f;
	g_character.vel.y = 0.0f;
	LoadDivGraph("Resources/Images/����.png", 16, 4, 4, 64, 64, g_character.image.handle);
	g_character.image.extRate = 1.0f;
	g_character.image.angle = 0.0f;
	g_character.animation.numFrames = 15;
	g_character.animation.frameDuration = (int)((0.3 * 60) / g_character.animation.numFrames);
	g_character.animation.frameNum = 0;
	g_character.animation.elapsedTime = 0;
	g_character.animation.state = 0;
	g_character.turn = FALSE;

	//�T�E���h
	//BGM
	g_selectBGM = LoadSoundMem("Resources/Sounds/Select_BGM.mp3");
	//SE
	g_selectSE[0] = LoadSoundMem("Resources/Sounds/Move_SE.mp3");
	g_selectSE[1] = LoadSoundMem("Resources/Sounds/decision_SE.mp3");

}



//----------------------------------------------------------------------
//! @brief �Z���N�g�V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateSelect(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	static BOOL selectFlag = FALSE;
	static BOOL moveFlag = FALSE;

	BOOL result;

	static int verticalPos = 1;
	static int horizontalPos = 0;

	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�L�[����
	if ((selectFlag|moveFlag) == FALSE)
	{
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_LEFT) != 0)	//���L�[
		{
			horizontalPos--;
			g_character.turn = TRUE;
			moveFlag = TRUE;
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_RIGHT) != 0)	//�E�L�[
		{
			horizontalPos++;
			g_character.turn = FALSE;
			moveFlag = TRUE;
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_UP) != 0)	//��L�[
		{
			verticalPos--;
			moveFlag = TRUE;
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_DOWN) != 0)	//���L�[
		{
			verticalPos++;
			moveFlag = TRUE;
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_1) != 0)	//Z�L�[
		{
			selectFlag = TRUE;
			//SE�̍Đ�
			PlaySoundMem(g_selectSE[1], DX_PLAYTYPE_BACK, TRUE);
		}
	}
	
	//�J�[�\���̍��W�̍X�V
	g_cursor.pos.x = 70.0f + (130.0f * (float)horizontalPos);
	g_cursor.pos.y = 80.0f + (150.0f*(float)verticalPos);

	//�L�����N�^�[�̈ړ�����шړ�����
	result = DetectCollisionBoxAndPoint(g_cursor.pos.x, g_cursor.pos.y, g_cursor.range, g_cursor.range, g_character.pos.x, g_character.pos.y);
	if (result == TRUE)
	{
		//�ړ��𒆎~
		moveFlag = FALSE;
		//���W���Œ�
		g_character.pos = g_cursor.pos;
		//���x���Ȃ���
		g_character.vel.x = g_character.vel.y = 0.0f;
		//�A�j���[�V�����̒�~
		ResetAnimation(&g_character.animation);
		//SE�̒�~
		StopSoundMem(g_selectSE[0]);
	}
	else
	{
		//�ړ���
		moveFlag = TRUE;

		//�L�����N�^�[���ړ�
		MoveCharacter(&g_character, g_cursor.pos);
		//�A�j���[�V�������Đ�
		if (g_character.animation.state == 0)
		{
			g_character.animation.state = 1;
		}
		//SE�̍Đ�
		if (CheckSoundMem(g_selectSE[0]) == 0)
		{
			PlaySoundMem(g_selectSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
	}


	// <�A�j���[�V����>
	//�A�j���[�V�����̍X�V
	UpdataAnimation(&g_character.animation);

	//�J�[�\���̐���
	//��
	if (horizontalPos <= 0)
	{
		horizontalPos = 0;
	}
	switch (verticalPos)
	{
	case 0:
		if (horizontalPos >= 1)
		{
			horizontalPos = 1;
		}
		break;
	case 1:
		if (horizontalPos >= 4)
		{
			horizontalPos = 4;
		}
		break;
	case 2:
		if (horizontalPos != 0)
		{
			horizontalPos = 0;
		}
		break;
	default:

		break;
	}
	//�c
	if (verticalPos <= 0)
	{
		verticalPos = 0;
	}
	if (verticalPos >= 2)
	{
		verticalPos = 2;
	}

	//�V�[���̈ړ�
	if ((selectFlag&~moveFlag) == TRUE)
	{
		switch (verticalPos)
		{
		case 0:
			switch (horizontalPos)
			{
			case 0:
				g_stageId = 5;
				break;
			case 1:
				g_stageId = 6;
				break;
			default:

				break;
			}
			//�v���C�V�[����
			ChangeScene(SCENE_PLAYING);
			break;
		case 1:
			switch (horizontalPos)
			{
			case 0:
				g_stageId = 0;
				break;
			case 1:
				g_stageId = 1;
				break;
			case 2:
				g_stageId = 2;
				break;
			case 3:
				g_stageId = 3;
				break;
			case 4:
				g_stageId = 4;
				break;
			default:

				break;
			}
			//�v���C�V�[����
			ChangeScene(SCENE_PLAYING);
			break;
		case 2:
			//�^�C�g���V�[����
			ChangeScene(SCENE_TITLE);
			break;
		default:

			break;
		}

		selectFlag = FALSE;
	}

#if DEBUG

#else
	//BGM�̍Đ�
	if (CheckSoundMem(g_selectBGM) == 0)
	{
		PlaySoundMem(g_selectBGM, DX_PLAYTYPE_BACK, TRUE);
	}
#endif

}



//----------------------------------------------------------------------
//! @brief �Z���N�g�V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderSelect(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�w�i�̕`��
	DrawBox(SCREEN_LEFT, SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_WHITE, TRUE);

	//�X�e�[�W�摜�̕`��
	DrawGraph(SCREEN_LEFT, SCREEN_TOP - 15, g_selectImage, TRUE);

	//�J�[�\���̕`��
	DrawRotaGraphF(g_character.pos.x, g_character.pos.y,
		g_character.image.extRate,
		g_character.image.angle,
		g_character.image.handle[g_character.animation.frameNum],
		TRUE, g_character.turn);


	//�f�o�b�O���
#if DEBUG
	DrawBoxAA(g_cursor.pos.x - g_cursor.range / 2, g_cursor.pos.y - g_cursor.range / 2, g_cursor.pos.x + g_cursor.range / 2, g_cursor.pos.y + g_cursor.range / 2, COLOR_RED, FALSE);

	DrawCircleAA(g_character.pos.x, g_character.pos.y, 1.0f, 100, COLOR_RED);
#endif

}



//----------------------------------------------------------------------
//! @brief �Z���N�g�V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeSelect(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�摜�f�[�^�̍폜
	InitGraph();

	//���f�[�^�̍폜
	InitSoundMem();

}



//----------------------------------------------------------------------
//! @brief �L�����N�^�[�̒Ǐ]�ړ�����
//!
//! @param[character] �ړ�������L�����N�^�[
//! @param[target] �ڕW
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void MoveCharacter(ObjectChar *character,Vec2D target)
{
	//���[�J���ϐ��̐錾//----------------------------------------------
	float dx;
	float dy;
	float angle;


	//���[�J���ϐ��̏�����//--------------------------------------------
	//����
	dx = target.x - character->pos.x;
	dy = target.y - character->pos.y;

	//�p�x
	angle = (float)atan2((double)dy, (double)dx);


	//�����̓��e//------------------------------------------------------
	//���x��^����
	character->vel.x = MOVE_SPEED*(float)cos((double)angle);
	character->vel.y = MOVE_SPEED*(float)sin((double)angle);

	//�����̕ύX
	if (character->vel.x < 0)
	{
		character->turn = TRUE;
	}
	if (character->vel.x > 0)
	{
		character->turn = FALSE;
	}
	
	//���W�̍X�V
	character->pos.x += character->vel.x;
	character->pos.y += character->vel.y;

}