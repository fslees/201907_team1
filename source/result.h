//=============================================================================
//
// ���ʉ�ʂ̒�` [result.h]
// Author : �����~��
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "2Dtexmanager.h"

//=================================
// �}�N����`
//=================================
#define TEXTURE_RESULT "data/TEXTURE/field000.jpg"


//===============================
//�v���g�^�C�v�錾
//===============================

	//������
	HRESULT InitResult();
	//�I������
	void UninitResult();
	//�X�V����
	void UpdateResult();
	//�`�揈��
	void DrawResult();
	//���_�̍쐬
	void MakeVertex();
#endif
