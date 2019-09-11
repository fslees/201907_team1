//=============================================================================
//
// �^�C�g�����S�̎��� [titlelogo.cpp]
// Author : �����~��
//
//=============================================================================
#include "titlelogo.h"
#include "scene.h"
#include "input.h"
#include "inputmanager.h"

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 titlelogoTex = NULL;		//�e�N�X�`���ւ̃|�C���^
VERTEX_2D vertexTitleLogo[NUM_VERTEX];		//���_���i�[���[�N
D3DXVECTOR3 vertexTitlelogoPos[NUM_VERTEX];	//���_�̈ʒu���
float	AlphaLogo ;							//���S�̃��l
int		CountAppearLogo;
int		CountDisp;
bool	DispStart;

//*****************************************************************************
// �Q�[���̏�����
//*****************************************************************************
HRESULT InitTitleLogo()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	//���l�̏�����
	AlphaLogo = 0.0f;
	CountAppearLogo = 0;
	CountDisp = 0;
	DispStart = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
							TEXTURE_TITLELOGO,		// �t�@�C���̖��O
								&titlelogoTex);		// �ǂݍ��ރ������[

	//���_�̍쐬
	MakeVertexTitleLogo();

	return S_OK;
}

//*****************************************************************************
// �Q�[���̏I��
//*****************************************************************************
void UninitTitleLogo()
{
	if (titlelogoTex != NULL)
	{// �e�N�X�`���̊J��
		titlelogoTex->Release();
		titlelogoTex = NULL;
	}
}

//*****************************************************************************
// �Q�[���̍X�V
//*****************************************************************************
void UpdateTitleLogo()
{

	//���S�������o���Ă���
	if (AlphaLogo < 1.0f)
	{
		AlphaLogo += 0.005f;
		if (AlphaLogo >= 1.0f)
		{
			AlphaLogo = 1.0f;
		}
		SetColorLogo();
	}
	else
	{
		CountAppearLogo++;
		if (CountAppearLogo > COUNT_APPERA_LOGO)
		{
			CountDisp = (CountDisp + 1) % 80;
			if (CountDisp > INTERVAL_DISP_LOGO)
			{
				DispStart = false;
			}
			else
			{
				DispStart = true;
			}
		}
	}

	//�_�ŏ���
	if (AlphaLogo < 1.0f)
	{
		AlphaLogo += 0.010f;
		if (AlphaLogo >= 1.0f)
		{
			AlphaLogo--;
		}
		SetColorLogo();
	}
}

//*****************************************************************************
// �Q�[����ʂ̕`��
//*****************************************************************************
void DrawTitleLogo()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, titlelogoTex);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexTitleLogo, sizeof(VERTEX_2D));
}

//========================================
//���_�̍쐬
//========================================
void MakeVertexTitleLogo()
{
	// ���_���W�̐ݒ�
	vertexTitleLogo[0].vtx = D3DXVECTOR3(LOGO_POS_X, LOGO_POS_Y, 0.0f);
	vertexTitleLogo[1].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_WIDTH, LOGO_POS_Y, 0.0f);
	vertexTitleLogo[2].vtx = D3DXVECTOR3(LOGO_POS_X, LOGO_POS_Y + LOGO_HEIGHT, 0.0f);
	vertexTitleLogo[3].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_WIDTH, LOGO_POS_Y + LOGO_HEIGHT, 0.0f);


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertexTitleLogo[0].rhw =
	vertexTitleLogo[1].rhw =
	vertexTitleLogo[2].rhw =
	vertexTitleLogo[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	/*vertexTitleLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitleLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitleLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);*/
	vertexTitleLogo[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);

	// �e�N�X�`�����W�̐ݒ�
	vertexTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

}

//========================================
//�_�ŗp�̐F�̐ݒ�
//========================================
void SetColorLogo()
{
	vertexTitleLogo[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
}