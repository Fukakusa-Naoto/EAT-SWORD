//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/
//! @file   GameMath.cpp
//!
//! @brief  DxLib�̐��w�֘A�ւ̒ǉ��@�\�̃\�[�X�t�@�C��
//!
//! @date   2017/3/27
//!
//! @author ���� �W
//__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/__/

// �w�b�_�t�@�C���̓ǂݍ��� ================================================
#include <DxLib.h>




// �֐��̒�` ==============================================================

//----------------------------------------------------------------------
//! @brief �p�x�̒P�ʕϊ�([�x]��[���W�A��])
//!
//! @param[in] degree �p�x[�x]
//!
//! @return �p�x[���W�A��]
//----------------------------------------------------------------------
float ToRadians(float degree)
{
	return degree * DX_PI_F / 180.0f;
}



//----------------------------------------------------------------------
//! @brief �p�x�̒P�ʕϊ�([���W�A��]��[�x])
//!
//! @param[in] radian �p�x[���W�A��]
//!
//! @return �p�x[�x]
//----------------------------------------------------------------------
float ToDegrees(float radian)
{
	return radian * 180.0f / DX_PI_F;
}



//----------------------------------------------------------------------
//! @brief �w�肵���l�������`����͈͓̔��Ɏ��߂�(int�^��)
//!
//! @param[in] x   �͈͓��Ɏ��߂����l�̌��ݒl
//! @param[in] min ����
//! @param[in] max ���
//!
//! @return �����`����͈͓̔��Ɏ��߂��l
//----------------------------------------------------------------------
int ClampI(int x, int min, int max)
{
	if (x < min)
	{
		x = min;
	}
	else if (x > max)
	{
		x = max;
	}

	return x;
}



//----------------------------------------------------------------------
//! @brief �w�肵���l���A�����`����͈͓̔��Ɏ��߂�(float�^��)
//!
//! @param[in] x   �͈͓��Ɏ��߂����l�̌��ݒl 
//! @param[in] min ����
//! @param[in] max ���
//!
//! @return �����`����͈͓̔��Ɏ��߂��l
//----------------------------------------------------------------------
float ClampF(float x, float min, float max)
{
	if (x < min)
	{
		x = min;
	}
	else if (x > max)
	{
		x = max;
	}

	return x;
}