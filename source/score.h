//=============================================================================
//
// �X�R�A�̒�` [score.h]
// Author : �����~��
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "2Dtexmanager.h"

//=================================
// �}�N����`
//=================================
#define TEXTURE_SCORE "data/TEXTURE/field001.jpg"


//===============================
//�N���X��`
//===============================
class Score
{
public://�����o�[�ϐ�
	Texmanager texmanager;					//�e�N�X�`���̃}�l�[�W���[�̃����o�[�ϐ�
	LPDIRECT3DTEXTURE9 scoreTex = NULL;		//�e�N�X�`���ւ̃|�C���^
	VERTEX_2D vertexScore[NUM_VERTEX];		//���_���i�[���[�N
	D3DXVECTOR3 vertexScorePos[NUM_VERTEX];	//���_�̈ʒu���

private:


public://�����o�[�֐�
	Score();//�e�N�X�`���̓ǂݍ���

	~Score();//�e�N�X�`���̉��

	void UninitScore();
	//
	void UpdateScore();
	//
	void DrawScore();

private:

};


#endif

