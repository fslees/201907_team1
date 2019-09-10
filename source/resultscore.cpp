//=============================================================================
//
// ���U���g�p�X�R�A�̎��� [resultscore.cpp]
// Author : ����@�W��
//
//=============================================================================
#include "resultscore.h"
#include "score.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************


//*****************************************************************************
// �R���X�g���N�^�@�X�R�A�̓ǂݍ���
//*****************************************************************************
Resultscore::Resultscore()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
									&resultScoreTex);// �ǂݍ��ރ������[

						//�\���ʒu�̏�����
	pos = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);

	//���_�̍쐬
	MakeVertex(pos);

	//�X�R�A�̎����l�̏�����
	resultScoreNum = GetScore();

	//�X�R�A�̏�����
	SetResultScore(resultScoreNum);

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
Resultscore::~Resultscore()
{
	if (resultScoreTex != NULL)
	{// �e�N�X�`���̊J��
		resultScoreTex->Release();
		resultScoreTex = NULL;
	}
}

//*****************************************************************************
// �Q�[���̏I��
//*****************************************************************************
void Resultscore::UninitResultScore()
{
	
}

//*****************************************************************************
// �Q�[���̍X�V
//*****************************************************************************
void  Resultscore::UpdateResultScore()
{

}

//*****************************************************************************
// �Q�[����ʂ̕`��
//*****************************************************************************
void  Resultscore::DrawResultScore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, resultScoreTex);


	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexResultScore[i], sizeof(VERTEX_2D));
	}
}


//=======================================================
// ���_�̍쐬
// ����:���_��񃏁[�N
// ����:�W���ʒu
//=======================================================
void Resultscore::MakeVertex(D3DXVECTOR3 pos)
{
	// ��������������
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		vertexResultScore[i][0].vtx.x = -SCORE_WIDE * i + pos.x;
		vertexResultScore[i][0].vtx.y = pos.y;
		vertexResultScore[i][0].vtx.z = 0.0f;
		vertexResultScore[i][1].vtx.x = -SCORE_WIDE * i + pos.x + TEXTURE_SCORE_SIZE_X;
		vertexResultScore[i][1].vtx.y = pos.y;
		vertexResultScore[i][1].vtx.z = 0.0f;
		vertexResultScore[i][2].vtx.x = -SCORE_WIDE * i + pos.x;
		vertexResultScore[i][2].vtx.y = pos.y + TEXTURE_SCORE_SIZE_Y;
		vertexResultScore[i][2].vtx.z = 0.0f;
		vertexResultScore[i][3].vtx.x = -SCORE_WIDE * i + pos.x + TEXTURE_SCORE_SIZE_X;
		vertexResultScore[i][3].vtx.y = pos.y + TEXTURE_SCORE_SIZE_Y;
		vertexResultScore[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		vertexResultScore[i][0].rhw =
		vertexResultScore[i][1].rhw =
		vertexResultScore[i][2].rhw =
		vertexResultScore[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		vertexResultScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexResultScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexResultScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexResultScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		vertexResultScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vertexResultScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vertexResultScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vertexResultScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}


}


//===================================
// �X�R�A�̃Z�b�g
// ����:�\������X�R�A
//==================================
void Resultscore::SetResultScore(int num)
{

	resultScoreNum = num;

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(resultScoreNum % 10);
		vertexResultScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		vertexResultScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		vertexResultScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		vertexResultScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		resultScoreNum /= 10;
	}
}


