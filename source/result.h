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
//�N���X��`
//===============================
class Result
{
public://�����o�[�ϐ�
	Texmanager texmanager;					//�e�N�X�`���̃}�l�[�W���[�̃����o�[�ϐ�
	LPDIRECT3DTEXTURE9 resultTex = NULL;	//�e�N�X�`���ւ̃|�C���^
	VERTEX_2D vertexResult[NUM_VERTEX];		//���_���i�[���[�N
	D3DXVECTOR3 vertexPos[NUM_VERTEX];		//���_�̈ʒu���
	


private:


public://�����o�[�֐�
	Result();//�e�N�X�`���̓ǂݍ���

	~Result();//�e�N�X�`���̉��

	void UninitResult();
	//
	void UpdateResult();
	//
	void DrawResult();

private:

};


#endif
