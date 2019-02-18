//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   SceneTitle.cpp
//!
//! @brief  �^�C�g���V�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "SceneTitle.h"
#include "RelateUI.h"
#include "RelateStage.h"


// �񋓑̂̒�` ============================================================




// �f�[�^�^�̒�` ==========================================================

//ObjectTitle�^
struct Tag_ObjectTitle
{
	Vec2D pos;
	HGRP handle;
	Size size;
};
typedef struct Tag_ObjectTitle ObjectTitle;


// �萔�̒�` ==============================================================

//UI�̕`��Ԋu
#define DRAW_SPACE (64.0f)


// �O���[�o���ϐ��̒�` ====================================================

//�^�C�g��
ObjectTitle g_title;

//UI
HGRP g_titleUiImage[2];
HGRP g_jawImage[2];

//�e�L�X�g
ObjectTitle g_titleUI[2];
//�{
ObjectJaw g_jaw;

//�T�E���h
//BGM
HSND g_titleBGM;
//SE
HSND g_titleSE[2];


// �֐��̃v���g�^�C�v�錾 ==================================================




// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �^�C�g���V�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializeTitle(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------
	
	//�^�C�g��
	g_title.pos.x = (float)SCREEN_CENTER_X;
	g_title.pos.y = (float)SCREEN_CENTER_Y / 2;
	g_title.handle = LoadGraph("Resources/Images/TITLE.png");
	g_title.size.width = 384;
	g_title.size.height = 64;


	//UI
	LoadDivGraph("Resources/Images/TITLE_STRING.png", 2, 1, 2, 128, 32, g_titleUiImage);
	//START
	g_titleUI[0].pos.x = (float)SCREEN_CENTER_X;
	g_titleUI[0].pos.y = (float)SCREEN_CENTER_Y + DRAW_SPACE;
	g_titleUI[0].handle = g_titleUiImage[0];
	g_titleUI[0].size.width = 200;
	g_titleUI[0].size.height = 32;

	//EXIT
	g_titleUI[1].pos.x = (float)SCREEN_CENTER_X;
	g_titleUI[1].pos.y = (float)SCREEN_CENTER_Y + DRAW_SPACE * 2;
	g_titleUI[1].handle = g_titleUiImage[1];
	g_titleUI[1].size.width = 200;
	g_titleUI[1].size.height = 32;


	//�{
	LoadDivGraph("Resources/Images/�{.png", 2, 1, 2, 640, 320, g_jawImage);
	g_jaw.pos = g_titleUI[0].pos;
	g_jaw.size.width = 150;
	g_jaw.size.height = 25;
	g_jaw.space = 17.0f;

	//�T�E���h
	//BGM
	g_titleBGM = LoadSoundMem("Resources/Sounds/Title_BGM.mp3");
	//SE
	g_titleSE[0] = LoadSoundMem("Resources/Sounds/Cusor_SE.mp3");
	g_titleSE[1] = LoadSoundMem("Resources/Sounds/decision_SE.mp3");

}



//----------------------------------------------------------------------
//! @brief �^�C�g���V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdateTitle(void)
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
			selectId = 0;
			g_jaw.pos = g_titleUI[0].pos;
			//SE�̍Đ�
			PlaySoundMem(g_titleSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
		else if (((g_lastInputState&g_currentInputState)&PAD_INPUT_DOWN) != 0)	//���L�[
		{
			selectId = 1;
			g_jaw.pos = g_titleUI[1].pos;
			//SE�̍Đ�
			PlaySoundMem(g_titleSE[0], DX_PLAYTYPE_BACK, TRUE);
		}
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_1) != 0)	//Z�L�[
		{
			selectFlag = TRUE;
			//SE�̍Đ�
			PlaySoundMem(g_titleSE[1], DX_PLAYTYPE_BACK, TRUE);
		}
	}

	//�V�[���̈ړ�
	if (selectFlag == TRUE)
	{
		g_jaw.space--;

		if (g_jaw.space <= 0)
		{
			if (selectId == 0)
			{
				selectId = 0;
				g_stageId = 0;
				//�Z���N�g�V�[����
				ChangeScene(SCENE_SELECT);

				selectFlag = FALSE;
			}
			else
			{
				selectId = 0;
				selectFlag = FALSE;
				//�Q�[�����I��
				ExitGame();
			}
		}
	}

	//BGM�̍Đ�
#if DEBUG

#else
	if (CheckSoundMem(g_titleBGM) == 0)
	{
		PlaySoundMem(g_titleBGM, DX_PLAYTYPE_BACK, TRUE);
	}
#endif

}



//----------------------------------------------------------------------
//! @brief �^�C�g���V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderTitle(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------
	
	//�w�i�̕`��
	DrawBox(SCREEN_LEFT, SCREEN_TOP, SCREEN_RIGHT, SCREEN_BOTTOM, COLOR_WHITE, TRUE);

	//�^�C�g���̕`��
	DrawRotaGraphF(g_title.pos.x, g_title.pos.y, 1.0, 0.0, g_title.handle, TRUE, FALSE);

	//�e�L�X�g�̕`��
	//START
	DrawRotaGraphF(g_titleUI[0].pos.x, g_titleUI[0].pos.y, 1.0, 0.0, g_titleUI[0].handle, TRUE, FALSE);
	//EXIT
	DrawRotaGraphF(g_titleUI[1].pos.x, g_titleUI[1].pos.y, 1.0, 0.0, g_titleUI[1].handle, TRUE, FALSE);

	//�{�̕`��
	DrawJaw(g_jaw.pos.x, g_jaw.pos.y, (float)g_jaw.size.width, (float)g_jaw.size.height, g_jaw.space, g_jawImage[0], g_jawImage[1]);

}



//----------------------------------------------------------------------
//! @brief �^�C�g���V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizeTitle(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------
	
	//�摜�f�[�^�̍폜
	InitGraph();

	//���f�[�^�̍폜
	InitSoundMem();

}
