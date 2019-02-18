//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateStage.h
//!
//! @brief  �X�e�[�W�֘A�̃w�b�_�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �f�[�^�^�̒�` ==========================================================

// StageAnimation�^ --------------------------------------------------------
struct Tag_StageAnimation
{
	Vec2D pos;
	Image image;
	Animation animation;
};
typedef struct Tag_StageAnimation StageAnimation;


// �萔�̒�` ==============================================================

// <�X�e�[�W�̃T�C�Y>
// ��
#define STAGE_WIDTH (210)
// ����
#define STAGE_HEIGHT (15)
// �`�b�v�T�C�Y
#define STAGE_SIZE (32)

//�X�e�[�W�̍ő吔
#define MAX_STAGE (7)

//�}�b�v�`�b�v�̍ő吔
#define MAX_STAGECHIP (3150)


// <�n�`����> ---------------------------------------------------------
// �n��
#define GRAND_LINE (400)

// �d�͉����x
#define GRAVITY (4.9f)

// �ő嗎�����x
#define MAX_FALL_SPEED (10.0f)


// �O���[�o���ϐ��̒�` ====================================================

// �X�e�[�W�f�[�^
extern int g_stageData[STAGE_HEIGHT][STAGE_WIDTH];

extern ObjectStage g_objectStage[MAX_STAGECHIP];

// �X�e�[�WID
extern int g_stageId;

// �g�p���̃X�e�[�W�I�u�W�F�N�g�̐�
extern int g_stageObjectNumber;

//�A�j���[�V����
extern StageAnimation g_stageAnimation[100];

// �֐��̐錾 ==============================================================

// �X�e�[�W�̏���������
void InitializeStage(void);

// �X�e�[�W�̍X�V����
void UpdateStage(void);

// �X�e�[�W�̕`�揈��
void RendarStage(void);

// �X�e�[�W�I�u�W�F�N�g�̐���
void CreateStageObject(ObjectStage *stageObject, float posX, float posY, int type);
