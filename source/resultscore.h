//=============================================================================
//
// ���U���g�X�R�A�̒�` [resultscore.h]
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
#define TEXTURE_RESULTSCORE "data/TEXTURE/number.png"
#define TEXTURE_RESULTSCORE_SIZE_X	(200)				// �X�R�A�e�N�X�`���T�C�Y
#define TEXTURE_RESULTSCORE_SIZE_Y	(200)				// ����
#define RESULTSCORE_POS_X		(850)					// �X�R�A�̏����ʒuX
#define RESULTSCORE_POS_Y		(500)					// ����
#define RESULTSCORE_WIDE		(150)                    //�����̕�
#define RESULTSCORE_MAX			(99999)					// �X�R�A�̍ő�l
#define RESULTSCORE_DIGIT		(5)						// ����

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
	int         resultScore;									//�X�R�A�̎����l

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


