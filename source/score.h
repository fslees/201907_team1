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
#define TEXTURE_SCORE "data/TEXTURE/number.png"
#define TEXTURE_SCORE_SIZE_X			(100)					// �X�R�A�e�N�X�`���T�C�Y
#define TEXTURE_SCORE_SIZE_Y			(100)					// ����
#define SCORE_POS_X						(1200)					// �X�R�A�̏����ʒuX
#define SCORE_POS_Y						(10)					// ����
#define SCORE_WIDE				(50)                            //�����̕�
#define SCORE_MAX				(99999)							// �X�R�A�̍ő�l
#define SCORE_DIGIT				(5)								// ����

//===============================
//�N���X��`
//===============================
class Score
{
public://�����o�[�ϐ�
	Texmanager texmanager;								//�e�N�X�`���̃}�l�[�W���[�̃����o�[�ϐ�
	LPDIRECT3DTEXTURE9 scoreTex = NULL;					//�e�N�X�`���ւ̃|�C���^
	VERTEX_2D vertexScore[SCORE_DIGIT][NUM_VERTEX];		//���_���i�[���[�N
	D3DXVECTOR3 vertexScorePos[NUM_VERTEX];				//���_�̈ʒu���
	D3DXVECTOR3 pos;									//�\���ʒu

private:


public://�����o�[�֐�
	Score();//�e�N�X�`���̓ǂݍ���

	~Score();//�e�N�X�`���̉��

	void UninitScore();
	//
	void UpdateScore();
	//
	void DrawScore();
    //
	void MakeVertex(D3DXVECTOR3 pos);
	//
	void SetScore(int num);

private:

};


#endif
