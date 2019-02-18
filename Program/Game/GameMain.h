//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMain.h
//!
//! @brief  �Q�[���֘A�̃w�b�_�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �񋓑̂̒�` ============================================================

// <�Q�[���ɕK�v�ȃV�[����ID��o�^> -----------------------------------
enum tag_SceneId
{
	SCENE_NONE,		//�Ȃ�
	SCENE_LOGO,		//���S
	SCENE_TITLE,	//�^�C�g��
	SCENE_SELECT,	//�X�e�[�W�I��
	SCENE_PLAYING,	//�v���C

};
typedef enum tag_SceneId SceneId;

// <���샊�X�g>--------------------------------------------------------
enum Tag_Action
{
	RUN,		//����
	EAT,		//�H�ׂ�
	SWING,		//����U��
	FLYING,		//��s
	GLUTTONY	//�\�H
};
typedef enum Tag_Action Action;

// <�^�C�v>------------------------------------------------------------
enum Tag_Type
{
	NONE,	//�Ȃ�
	NORMAL,	//�m�[�}��
	SWORD,	//�\�[�h
	FIRE,	//�t�@�C�A
	FLY,	//�t���C
	BIG		//�r�b�O
};
typedef enum Tag_Type Type;


// �f�[�^�^�̒�` ==========================================================

// <Vec2D�^> ----------------------------------------------------------
struct Tag_Vec2D
{
	float x;	//x����
	float y;	//y����
};
typedef struct Tag_Vec2D Vec2D;

// <Size�^> -----------------------------------------------------------
struct Tag_Size
{
	int width;	//��
	int height;	//����
};
typedef struct Tag_Size Size;

// <Image�^> ----------------------------------------------------------
struct Tag_Image
{
	HGRP handle[100];		//�O���t�B�b�N�n���h��
	float extRate;			//�g�嗦
	float angle;			//�p�x
};
typedef struct Tag_Image Image;

// <Animation�^> -----------------------------------------------------
struct Tag_Animation
{
	int numFrames;		// �A�j���[�V�����̑��t���[����
	int frameDuration;	// 1�t���[����\�����鎞��
	int frameNum;		// ���݂̃t���[���ԍ�
	int elapsedTime;	// ���݂̃t���[���̕\������
	int state;			//�A�j���[�V�����̏��
};
typedef struct Tag_Animation Animation;

// <BackGround�^> ----------------------------------------------------
struct Tag_BackGround
{
	Vec2D pos;		//���W
	HGRP handle;	//�O���t�B�b�N�n���h��
};
typedef struct Tag_BackGround BackGround;

// <ObjectPlayer�^> ---------------------------------------------------
struct Tag_ObjectPlayer
{
	Vec2D pos;					//���W
	Vec2D dataPos;				//�f�[�^��̍��W
	Vec2D vel;					//���x
	Image image[10];			//�摜
	Animation animation[10];	//�A�j���[�V����
	Action action;				//����
	BOOL turn;					//���]
	int state;					//���
	Type type;					//�^�C�v
	int count;					//����\�͂̎g�p����
	int hp;						//�̗�
};
typedef struct Tag_ObjectPlayer ObjectPlayer;

// <ObjectEnemy�^> ----------------------------------------------------
struct Tag_ObjectEnemy
{
	Vec2D pos;					//���W
	Vec2D vel;					//���x
	HGRP image;					//�摜
	float extRate;				//�g�嗦
	float angle;				//�p�x
	int state;					//���
	Type type;					//�^�C�v
	int actionInterval;			//����̊Ԋu
};
typedef struct Tag_ObjectEnemy ObjectEnemy;

// <ObjectStage�^> ----------------------------------------------------
struct Tag_ObjectStage
{
	Vec2D pos;		//���W
	int state;		//���
	int type;		//�^�C�v
};
typedef struct Tag_ObjectStage ObjectStage;

// <ObjectJaw�^> ------------------------------------------------------
struct Tag_ObjectJaw
{
	Vec2D pos;	//���W
	Size size;	//�T�C�Y
	float space;	//�X�y�[�X
};
typedef struct Tag_ObjectJaw ObjectJaw;


// �萔�̒�` ==============================================================

// <�V�X�e��> ----------------------------------------------------------
#define GAME_TITLE "EAT SWORD"        // �Q�[���^�C�g��


// <���> --------------------------------------------------------------
#define SCREEN_WIDTH    (640)                  // ��ʂ̕�[pixel]
#define SCREEN_HEIGHT   (480)                  // ��ʂ̍���[pixel]

#define SCREEN_TOP      (0)                    // ��ʂ̏�[
#define SCREEN_BOTTOM   (SCREEN_HEIGHT)        // ��ʂ̉��[
#define SCREEN_LEFT     (0)                    // ��ʂ̍��[
#define SCREEN_RIGHT    (SCREEN_WIDTH)         // ��ʂ̉E�[

#define SCREEN_CENTER_X (SCREEN_WIDTH  / 2)    // ��ʂ̒���(X���W)
#define SCREEN_CENTER_Y (SCREEN_HEIGHT / 2)    // ��ʂ̒���(Y���W)


// <�f�o�b�O> ---------------------------------------------------------
#define DEBUG (0)		// 0 : �f�o�b�O���Ȃ�
						// 1 : �f�o�b�O��񂠂�


// �O���[�o���ϐ��̒�` ====================================================

// <�V�[���Ǘ�> -------------------------------------------------------
extern SceneId g_currentSceneId;	//���݂̃V�[����ID

// <�L�[�̓��͏��> ---------------------------------------------------
extern int g_currentInputState;	//����
extern int g_lastInputState;	//�O��


// �֐��̐錾 ==============================================================

// �Q�[���̏���������
void InitializeGame(void);

// �Q�[���̍X�V����
void UpdateGame(void);

// �Q�[���̕`�揈��
void RenderGame(void);

// �Q�[���̏I������
void FinalizeGame(void);

//�V�[���̐؂�ւ�
void ChangeScene(SceneId nextSceneId);
