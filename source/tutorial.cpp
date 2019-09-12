//=============================================================================
//
// �`���[�g���A���̎��� [tutorial.cpp]
// Author : GP12A332_26_�c�����z
//
//=============================================================================
#include "scene.h"
#include "inputmanager.h"
#include "tutorial.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_TUTORIAL ("data/TEXTURE/tutorial.png")

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void MakeVertexTutorial();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 TutorialTex = NULL;	//�e�N�X�`���ւ̃|�C���^
VERTEX_2D VertexTutorial[NUM_VERTEX];		//���_���i�[���[�N
D3DXVECTOR3 VertexTutorialPos[NUM_VERTEX];		//���_�̈ʒu���

//*****************************************************************************
// �`���[�g���A���̏�����
//*****************************************************************************
HRESULT InitTutorial()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
		TEXTURE_TUTORIAL,		// �t�@�C���̖��O
		&TutorialTex);		// �ǂݍ��ރ������[

//���_�̍쐬
	MakeVertexTutorial();


	return S_OK;
}


//*****************************************************************************
// �`���[�g���A���̏I��
//*****************************************************************************
void UninitTutorial()
{
	if (TutorialTex != NULL)
	{// �e�N�X�`���̊J��
		TutorialTex->Release();
		TutorialTex = NULL;
	}
}

//*****************************************************************************
// �`���[�g���A���̍X�V
//*****************************************************************************
void  UpdateTutorial()
{
	if (GetInput(HIT_START))
	{
		SetScene(SCENE_GAME);
		SetTitleBGM();
	}
}

//*****************************************************************************
// �`���[�g���A���̕`��
//*****************************************************************************
void DrawTutorial()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, TutorialTex);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexTutorial, sizeof(VERTEX_2D));
}

//========================================
//���_�̍쐬
//========================================
void MakeVertexTutorial()
{
	// ���_���W�̐ݒ�
	VertexTutorial[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VertexTutorial[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	VertexTutorial[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	VertexTutorial[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	VertexTutorial[0].rhw =
		VertexTutorial[1].rhw =
		VertexTutorial[2].rhw =
		VertexTutorial[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	VertexTutorial[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexTutorial[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexTutorial[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexTutorial[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	VertexTutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	VertexTutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	VertexTutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	VertexTutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}