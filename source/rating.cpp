//=============================================================================
//
// �q�b�g���̐��x�\������ [hitqualety.cpp]
// Author : GP12A332_26_�c�����z
//
//=============================================================================
#include "rating.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �e�N�X�`���[�f�[�^
#define TEXTURE_PERFECT		("data/TEXTURE/perfect.png")
#define TEXTURE_GREAT		("data/TEXTURE/great.png")
#define TEXTURE_GOOD		("data/TEXTURE/good.png")
// ���_�T�C�Y
#define TEXTURE_SIZE_X		(100.0f)
#define TEXTURE_SIZE_Y		(35.0f)
#define TEXTURE_POS_Y		(550.0f)
// �����ʒu
#define INIT_POS_X			(0.0f)
#define INIT_POS_Y			(0.0f)
#define INIT_POS_Z			(-50.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//*****************************************************************************
// �R���X�g���N�^
//*****************************************************************************
Rating::Rating()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �ϐ��̏�����
	texNum = PERFECT;
	use = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PERFECT,	// �t�@�C���̖��O
								&texture[PERFECT]);	// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_GREAT,		// �t�@�C���̖��O
								&texture[GREAT]);	// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_GOOD,		// �t�@�C���̖��O
								&texture[GOOD]);	// �ǂݍ��ރ������[

	//���_�̍쐬
	MakeVertex();
}

//*****************************************************************************
// �Q�[���̏I��
//*****************************************************************************
Rating::~Rating()
{
	for (int i = 0; i < TEX_MAX; i++)
	{
		if (texture[i] != NULL)
		{// �e�N�X�`���̊J��
			texture[i]->Release();
			texture[i] = NULL;
		}
	}
}

//*****************************************************************************
// �Q�[���̍X�V
//*****************************************************************************
void Rating:: Update()
{
}

//*****************************************************************************
// ���U���g��ʂ̕`��
//*****************************************************************************
void Rating::Draw()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, texture[texNum]);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertex, sizeof(VERTEX_2D));
}

//=========================================
//���_�̍쐬
//=========================================
void Rating::MakeVertex()
{
	// ���_���W�̐ݒ�
	vertex[0].vtx = D3DXVECTOR3((float)(SCREEN_CENTER_X) - TEXTURE_SIZE_X, TEXTURE_POS_Y - TEXTURE_SIZE_Y, 0.0f);
	vertex[1].vtx = D3DXVECTOR3((float)(SCREEN_CENTER_X) + TEXTURE_SIZE_X, TEXTURE_POS_Y - TEXTURE_SIZE_Y, 0.0f);
	vertex[2].vtx = D3DXVECTOR3((float)(SCREEN_CENTER_X) - TEXTURE_SIZE_X, TEXTURE_POS_Y + TEXTURE_SIZE_Y, 0.0f);
	vertex[3].vtx = D3DXVECTOR3((float)(SCREEN_CENTER_X) + TEXTURE_SIZE_X, TEXTURE_POS_Y + TEXTURE_SIZE_Y, 0.0f);

	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertex[0].rhw =
		vertex[1].rhw =
		vertex[2].rhw =
		vertex[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}
