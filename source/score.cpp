//=============================================================================
//
// �X�R�A�̎��� [score.cpp]
// Author : ����@�W��
//
//=============================================================================
#include "score.h"
#include "2Dtexmanager.h"


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
Score::Score()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SCORE,		// �t�@�C���̖��O
								&scoreTex);		// �ǂݍ��ރ������[

	//�\���ʒu�̏�����
	pos = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);

	//���_�̍쐬
	MakeVertex(pos);

	//�X�R�A�̎����l�̏�����
	score = SCORE_INITIAL;

	//�X�R�A�̏�����
	SetScore(score);

}

//=============================================================================
//�f�X�g���N�^
//=============================================================================
Score::~Score()
{
	if (scoreTex != NULL)
	{// �e�N�X�`���̊J��
		scoreTex->Release();
		scoreTex = NULL;
	}
}

//*****************************************************************************
// �Q�[���̏I��
//*****************************************************************************
void Score::UninitScore()
{
	
}

//*****************************************************************************
// �Q�[���̍X�V
//*****************************************************************************
void  Score::UpdateScore()
{
	
}

//*****************************************************************************
// �Q�[����ʂ̕`��
//*****************************************************************************
void  Score::DrawScore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, scoreTex);

	
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_2D);

		// �|���S���̕`��
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexScore[i], sizeof(VERTEX_2D));
	}
}


//=======================================================
// ���_�̍쐬
// ����:���_��񃏁[�N
// ����:�W���ʒu
//=======================================================
void Score::MakeVertex(D3DXVECTOR3 pos)
{
	// ��������������
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// ���_���W�̐ݒ�
		vertexScore[i][0].vtx.x = -SCORE_WIDE * i + pos.x;
		vertexScore[i][0].vtx.y = pos.y;
		vertexScore[i][0].vtx.z = 0.0f;
		vertexScore[i][1].vtx.x = -SCORE_WIDE * i + pos.x + TEXTURE_SCORE_SIZE_X;
		vertexScore[i][1].vtx.y = pos.y;
		vertexScore[i][1].vtx.z = 0.0f;
		vertexScore[i][2].vtx.x = -SCORE_WIDE * i + pos.x;
		vertexScore[i][2].vtx.y = pos.y + TEXTURE_SCORE_SIZE_Y;
		vertexScore[i][2].vtx.z = 0.0f;
		vertexScore[i][3].vtx.x = -SCORE_WIDE * i + pos.x + TEXTURE_SCORE_SIZE_X;
		vertexScore[i][3].vtx.y = pos.y + TEXTURE_SCORE_SIZE_Y;
		vertexScore[i][3].vtx.z = 0.0f;

		// rhw�̐ݒ�
		vertexScore[i][0].rhw =
		vertexScore[i][1].rhw =
		vertexScore[i][2].rhw =
		vertexScore[i][3].rhw = 1.0f;

		// ���ˌ��̐ݒ�
		vertexScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// �e�N�X�`�����W�̐ݒ�
		vertexScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vertexScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vertexScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vertexScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}


}


//===================================
// �X�R�A�̃Z�b�g
// ����:�\������X�R�A
//==================================
void Score::SetScore(int num)
{
	
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// �e�N�X�`�����W�̐ݒ�
		float x = (float)(num % 10);
		vertexScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		vertexScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		vertexScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		vertexScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		num /= 10;
	}
}


//==========================================
//�X�R�A����Get�֐�
//�߂�l�F�\�����Ă���X�R�A�̐���
//==========================================
int Score::GetScore()
{
	return score;
}