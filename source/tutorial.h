//=============================================================================
//
// �`���[�g���A���̒�` [tutorial.h]
// Author : �����~��
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//=================================
// �}�N����`
//=================================
#define TEXTURE_TUTORIAL "data/TEXTURE/tutorial.png"

//===============================
//�v���g�^�C�v�錾
//===============================

	//������
	HRESULT InitTutorial();
	//�I������
	void	UninitTutorial();
	//�X�V����
	void	UpdateTutorial();
	//�`�揈��
	void	DrawTutorial();
	//���_�̍쐬
	void MakeVertexTutorial();
#endif
