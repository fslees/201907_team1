//=============================================================================
//
// ���ʉ�ʂ̎��� [result.cpp]
// Author : �����~��
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "scene.h"
#include "inputmanager.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 resultTex = NULL;	//�e�N�X�`���ւ̃|�C���^
VERTEX_2D vertexResult[NUM_VERTEX];		//���_���i�[���[�N
D3DXVECTOR3 vertexPos[NUM_VERTEX];		//���_�̈ʒu���

//*****************************************************************************
// �R���X�g���N�^�@���U���g�̓ǂݍ���
//*****************************************************************************
HRESULT InitResult()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_RESULT,		// �t�@�C���̖��O
								&resultTex);		// �ǂݍ��ރ������[


	//���_�̍쐬
	MakeVertex();

	return S_OK;
}


//*****************************************************************************
// �Q�[���̏I��
//*****************************************************************************
void UninitResult()
{
	if (resultTex != NULL)
	{// �e�N�X�`���̊J��
		resultTex->Release();
		resultTex = NULL;
	}
}

//*****************************************************************************
// �Q�[���̍X�V
//*****************************************************************************
void  UpdateResult()
{
	if (GetKeyboardTrigger(DIK_1))
	{
		SetScene(0);
	}
}

//*****************************************************************************
// ���U���g��ʂ̕`��
//*****************************************************************************
void DrawResult()
{
	//texmanager->Draw(resultTex, &vertexResult[NUM_VERTEX]);
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, resultTex);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexResult, sizeof(VERTEX_2D));

}

//=========================================
//���_�̍쐬
//=========================================
void MakeVertex()
{
	// ���_���W�̐ݒ�
	vertexResult[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexResult[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	vertexResult[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	vertexResult[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexResult[0].rhw =
	vertexResult[1].rhw =
	vertexResult[2].rhw =
	vertexResult[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}