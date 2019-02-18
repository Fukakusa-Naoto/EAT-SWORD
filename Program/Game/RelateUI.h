//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   RelateUI.h
//!
//! @brief UI�֘A�̃w�b�_�t�@�C��
//!
//! @date   2017.10.01
//!
//! @author GF1.21.�[�����l
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// ���d�C���N���[�h�̖h�~ ==================================================
#pragma once




// �f�[�^�^�̒�` ==========================================================





// �萔�̒�` ==============================================================





// �O���[�o���ϐ��̒�` ====================================================





// �֐��̐錾 ==============================================================

// UI�̏���������
void InitializeUI(void);

// HP�Q�[�W�̕`��
void DrawHPGauge(float x, float y, float width, float height, int max, int now);

// ���Ԃ̕`��
void DrawTimer(float x, float y, int time, HGRP handle[], Type type);

// �{�̕`��
void DrawJaw(float x, float y, float width, float height, float spece, HGRP upperHandle, HGRP lowerHandle);

// �e�L�X�g�{�b�N�X�̕`��
void DrawTextBox(float x, float y, float width, float height, char *text);
