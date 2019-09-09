//=============================================================================
//
// ���͊Ǘ��v���O�����̒�` [inputmanager.h]
// Author : �����~��
//
//=============================================================================
#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include "main.h"

//=================================
// �}�N����`
//=================================

// �{�^�����͂̎��
enum ACTION_NAME
{
	// �����[���̃{�^��
	HIT_LEFT_LANE,
	// �^�񒆃��[���̃{�^��
	HIT_CENTER_LANE,
	// �E���[���̃{�^��
	HIT_RIGHT_LANE,
	// �������̓���
	PUSH_LEFT,
	// ������̓���
	PUSH_UP,
	// �E�����̓���
	PUSH_RIGHT,
	// �J�ڃ{�^���̓���
	HIT_START,
	// �{�^���A�N�V�����̐�
	ACTION_MAX
};


//===============================
//�v���g�^�C�v�錾
//===============================

/////////////////////////////////////////////////////////
// ���͂��m�F����֐�
// param[in] action �{�^����enum�v�f
// return	 ���͂��ꂽ�ꍇ��true
/////////////////////////////////////////////////////////
bool GetInput(int action);

#endif