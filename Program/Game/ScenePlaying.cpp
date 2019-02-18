//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   ScenePlaying.cpp
//!
//! @brief  �v���C�V�[���֘A�̃\�[�X�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include "GameMain.h"
#include "ScenePlaying.h"
#include "RelatePlayer.h"
#include "RelateStage.h"
#include "RelateCamera.h"
#include "RelateEnemy.h"
#include "RelateDetectCollition.h"
#include "RelateBullet.h"
#include "RelatePause.h"
#include "RelateUI.h"


// �f�[�^�^�̒�` ==========================================================




// �萔�̒�` ==============================================================




// �O���[�o���ϐ��̒�` ====================================================
//�T�E���h
//BGM
HSND g_playBGM;
//SE
HSND g_playSE[17];


// �֐��̃v���g�^�C�v�錾 ==================================================




// �֐��̒�` ==============================================================
//----------------------------------------------------------------------
//! @brief �v���C�V�[���̏���������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void InitializePlaying(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------
	//�T�E���h
	//BGM
	g_playBGM = LoadSoundMem("Resources/Sounds/Stage_BGM_01.mp3");
	//SE
	g_playSE[0] = LoadSoundMem("Resources/Sounds/Clear_BGM.mp3");
	g_playSE[1] = LoadSoundMem("Resources/Sounds/False.mp3");
	g_playSE[2] = LoadSoundMem("Resources/Sounds/Damage_SE.mp3");
	g_playSE[3] = LoadSoundMem("Resources/Sounds/Move_SE.mp3");
	g_playSE[4] = LoadSoundMem("Resources/Sounds/Jump(small)_SE.mp3");
	g_playSE[5] = LoadSoundMem("Resources/Sounds/Jump(big)_SE.mp3.mp3");
	g_playSE[6] = LoadSoundMem("Resources/Sounds/Jump(enemy)_SE.mp3");
	g_playSE[7] = LoadSoundMem("Resources/Sounds/Block_SE.mp3");
	g_playSE[8] = LoadSoundMem("Resources/Sounds/FIRE_SE.mp3.mp3");
	g_playSE[9] = LoadSoundMem("Resources/Sounds/Pause.mp3");
	g_playSE[10] = LoadSoundMem("Resources/Sounds/Eat.mp3");
	g_playSE[11] = LoadSoundMem("Resources/Sounds/Gluttony.mp3");
	g_playSE[12] = LoadSoundMem("Resources/Sounds/Sword.mp3");
	g_playSE[13] = LoadSoundMem("Resources/Sounds/CollisionSword.mp3");
	g_playSE[14] = LoadSoundMem("Resources/Sounds/CollisionBullet.mp3");
	g_playSE[15] = LoadSoundMem("Resources/Sounds/Fly.mp3");
	g_playSE[16] = LoadSoundMem("Resources/Sounds/Burn.mp3");


	//�X�e�[�W�̏�����
	InitializeStage();

	//�v���C���[�̏�����
	InitializePlayer();

	//�J�����̏�����
	InitializeCamera();

	//�G�̏�����
	InitializeEnemy();

	//�e�̏�����
	InitializeBullet();

	//�|�[�Y�̏�����
	InitializePause();

	//UI�̏�����
	InitializeUI();

}



//----------------------------------------------------------------------
//! @brief �v���C�V�[���̍X�V����
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void UpdatePlaying(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�|�[�Y��
	if (g_pauseFlag == TRUE)
	{
		//�|�[�Y�̍X�V
		UpdatePause();
	}
	else
	{
		//�X�e�[�W�̍X�V
		UpdateStage();

		//�J�����̍X�V
		UpdateCamera();

		//�v���C���[�̍X�V
		UpdatePlayer();

		//�G�̍X�V
		UpdateEnemy();

		//�e�̍X�V
		UpdateBullet();

		//�����蔻��
		AllDetectCollision();

		//�|�[�Y�̑���
		if (((g_lastInputState&g_currentInputState)&PAD_INPUT_10) != 0)	//�X�y�[�X�L�[
		{
			//�t���O�𗧂Ă�
			g_pauseFlag = TRUE;

			//SE�̍Đ�
			PlaySoundMem(g_playSE[9], DX_PLAYTYPE_BACK, TRUE);
		}
	}

#if DEBUG

#else
	//BGM�̍Đ�
	if (CheckSoundMem(g_playBGM) == 0)
	{
		PlaySoundMem(g_playBGM, DX_PLAYTYPE_BACK, TRUE);
	}
#endif

	//�V�[���̈ړ�
	//�v���C���[�����ꂽ
	if (g_player.state == 0)
	{
		//BGM�̒�~
		StopSoundMem(g_playBGM);
		//SE�̍Đ�
		PlaySoundMem(g_playSE[1], DX_PLAYTYPE_NORMAL, TRUE);
		//�Z���N�g�V�[����
		ChangeScene(SCENE_SELECT);
	}
	//�v���C���[���S�[������
	if (g_player.dataPos.x >= (STAGE_WIDTH - 13)*STAGE_SIZE)
	{
		//BGM�̒�~
		StopSoundMem(g_playBGM);
		//SE�̍Đ�
		PlaySoundMem(g_playSE[0], DX_PLAYTYPE_NORMAL, TRUE);
		//�Z���N�g�V�[����
		ChangeScene(SCENE_SELECT);
	}

}



//----------------------------------------------------------------------
//! @brief �v���C�V�[���̕`�揈��
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void RenderPlaying(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�X�e�[�W�̕`��
	RendarStage();

	// <�v���C���[�̕`��>
	RendarPlayer();

	//�G�̕`��
	RendarEnemy();

	//�e�̕`��
	RendarBullet();

	//�|�[�Y�̕`��
	if (g_pauseFlag == TRUE)
	{
		RenderPause();
	}

}



//----------------------------------------------------------------------
//! @brief �v���C�V�[���̏I������
//!
//! @param[in] �Ȃ�
//!
//! @return �Ȃ�
//----------------------------------------------------------------------
void FinalizePlaying(void)
{
	//���[�J���ϐ��̐錾//----------------------------------------------



	//���[�J���ϐ��̏�����//--------------------------------------------



	//�����̓��e//------------------------------------------------------

	//�摜�f�[�^�̍폜
	InitGraph();

	//���f�[�^�̍폜
	InitSoundMem();

}