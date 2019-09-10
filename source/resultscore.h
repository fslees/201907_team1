//=============================================================================
//
// �X�R�A�̒�` [score.h]
// Author :����@�W��
//
//=============================================================================
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_

#include "main.h"
#include "score.h"

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
class Resultscore:public Score
{
public://�����o�[�ϐ�
	LPDIRECT3DTEXTURE9  resultScoreTex = NULL;					//�e�N�X�`���ւ̃|�C���^
	VERTEX_2D vertexResultScore[SCORE_DIGIT][NUM_VERTEX];		//���_���i�[���[�N
	D3DXVECTOR3 vertexResultScorePos[NUM_VERTEX];				//���_�̈ʒu���
	D3DXVECTOR3 pos;											//�\���ʒu
	int         resultScoreNum;									//�X�R�A�̎����l

private:


public://�����o�[�֐�
	Resultscore();//�e�N�X�`���̓ǂݍ���

	~Resultscore();//�e�N�X�`���̉��

	void UninitResultScore();
	//
	void UpdateResultScore();
	//
	void DrawResultScore();
	//
	void MakeVertex(D3DXVECTOR3 pos);
	//
	void SetResultScore(int num);
	

private:

};


#endif


