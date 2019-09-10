//=============================================================================
//
// �`���[�g���A���̎��� [tutorial.cpp]
// Author : �����~��
//
//=============================================================================
#include "scene.h"
#include "inputmanager.h"
#include "tutorial.h"
#include "input.h"


//*****************************************************************************
// �}�N����`
//*****************************************************************************


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 tutorialTex = NULL;	//�e�N�X�`���ւ̃|�C���^
VERTEX_2D vertexTutorial[NUM_VERTEX];		//���_���i�[���[�N
D3DXVECTOR3 vertexTutorialPos[NUM_VERTEX];		//���_�̈ʒu���

//*****************************************************************************
// �`���[�g���A���̏�����
//*****************************************************************************
HRESULT InitTutorial()
{

	LPDIRECT3DDEVICE9 Device = GetDevice();


	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_TUTORIAL,	// �t�@�C���̖��O
								&tutorialTex);		// �ǂݍ��ރ������[

							

	//���_�̍쐬
	MakeVertexTutorial();

	return S_OK;
}


//*****************************************************************************
// �`���[�g���A���̏I��
//*****************************************************************************
void UninitTutorial()
{
}

//*****************************************************************************
// �`���[�g���A���̍X�V
//*****************************************************************************
void  UpdateTutorial()
{
	if (GetKeyboardTrigger(DIK_1))
	{
		SetScene(SCENE_GAME);
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
	Device->SetTexture(0, tutorialTex);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexTutorial, sizeof(VERTEX_2D));
}

//=====================================
//�`���[�g���A���p�̒��_�쐬
//=====================================
void MakeVertexTutorial()
{
	// ���_���W�̐ݒ�
	vertexTutorial[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexTutorial[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	vertexTutorial[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	vertexTutorial[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexTutorial[0].rhw =
	vertexTutorial[1].rhw =
	vertexTutorial[2].rhw =
	vertexTutorial[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertexTutorial[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTutorial[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTutorial[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTutorial[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertexTutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexTutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexTutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexTutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}