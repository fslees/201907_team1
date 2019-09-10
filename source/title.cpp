//=============================================================================
//
// �^�C�g����ʂ̎��� [title.cpp]
// Author : �����~��
//
//=============================================================================
#include "title.h"
#include "scene.h"
#include "input.h"
#include "inputmanager.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 titleTex = NULL;	//�e�N�X�`���ւ̃|�C���^
VERTEX_2D vertexTitle[NUM_VERTEX];		//���_���i�[���[�N
D3DXVECTOR3 vertexTitlePos[NUM_VERTEX];		//���_�̈ʒu���

//*****************************************************************************
// �Q�[���̏�����
//*****************************************************************************
HRESULT InitTitle()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TITLE,		// �t�@�C���̖��O
								&titleTex);		// �ǂݍ��ރ������[

	//���_�̍쐬
	MakeVertexTitle();

	return S_OK;
}

//*****************************************************************************
// �Q�[���̏I��
//*****************************************************************************
void UninitTitle()
{
	if (titleTex != NULL)
	{// �e�N�X�`���̊J��
		titleTex->Release();
		titleTex = NULL;
	}
}

//*****************************************************************************
// �Q�[���̍X�V
//*****************************************************************************
void UpdateTitle()
{
	if (GetKeyboardTrigger(DIK_1))
	{

		SetScene(SCENE_TUTORIAL);
	}
}

//*****************************************************************************
// �Q�[����ʂ̕`��
//*****************************************************************************
void DrawTitle()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, titleTex);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexTitle, sizeof(VERTEX_2D));
}

//========================================
//���_�̍쐬
//========================================
void MakeVertexTitle()
{
	// ���_���W�̐ݒ�
	vertexTitle[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexTitle[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	vertexTitle[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	vertexTitle[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexTitle[0].rhw =
	vertexTitle[1].rhw =
	vertexTitle[2].rhw =
	vertexTitle[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}