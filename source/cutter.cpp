//=============================================================================
//
// �J�b�^�[�̎��� [cutter.cpp]
// Author : �����~��
//
//=============================================================================
#include "cutter.h"
#include "inputmanager.h"
#include "game.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_CUTTER	"data/TEXTURE/lightSaber.png"	// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexCutter(LPDIRECT3DDEVICE9 device);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureCutter = NULL;	// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffCutter = NULL;	// ���_�o�b�t�@�ւ̃|�C���^

D3DXMATRIX				mtxWorldCutter;				// ���[���h�}�g���b�N�X
D3DXVECTOR3				posCutter;					// ���݂̈ʒu
D3DXVECTOR3				rotCutter;					// ���݂̌���

const static D3DXVECTOR3	RANGE_CUTTER[4] =
{
	D3DXVECTOR3(150.0f, 0.0f, -100.0f),
	D3DXVECTOR3(150.0f, 0.0f, 100.0f),
	D3DXVECTOR3(80.0f, 0.0f, -100.0f),
	D3DXVECTOR3(80.0f, 0.0f, 100.0f)
};

const static float		MIN_VALUE_ROT_Z = 0.7f;
const static float		MAX_VALUE_ROT_Z = 2.4f;
const static float		MOVE_SPEED_ROT_Z = 0.02f;

//=============================================================================
// ����������
//=============================================================================
HRESULT InitCutter(D3DXVECTOR3 pos)
{
	LPDIRECT3DDEVICE9 device = GetDevice(); 
	HRESULT hr;

	// �ʒu�A�����̏����ݒ�
	posCutter = D3DXVECTOR3(0.0f, 0.0f, pos.z);
	rotCutter = D3DXVECTOR3(0.0f, 0.0f, MIN_VALUE_ROT_Z);
	
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_CUTTER,			// �t�@�C���̖��O
								&D3DTextureCutter);	// �ǂݍ��ރ������[

	// ���_���̍쐬
	hr = MakeVertexCutter(device);

	return hr;
}

//=============================================================================
// �I������
//=============================================================================
void UninitCutter(void)
{
	if(D3DTextureCutter != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureCutter->Release();
		D3DTextureCutter = NULL;
	}

	if(D3DVtxBuffCutter != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuffCutter->Release();
		D3DVtxBuffCutter = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateCutter(void)
{
	if (GetInput(PUSH_LEFT) && rotCutter.z <= MAX_VALUE_ROT_Z)
	{
		rotCutter.z += MOVE_SPEED_ROT_Z;
	}
	if (GetInput(PUSH_RIGHT) && rotCutter.z >= MIN_VALUE_ROT_Z)
	{
		rotCutter.z -= MOVE_SPEED_ROT_Z;
	}	

}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawCutter(void)
{

	LPDIRECT3DDEVICE9 device = GetDevice(); 
	D3DXMATRIX mtxRot, mtxTranslate, mtxView;

	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	device->SetRenderState(D3DRS_LIGHTING, FALSE);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);				// ���ʂ��J�����O


	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorldCutter);

	//// �r���[�}�g���b�N�X���擾
	//mtxView = GetMtxGameView();

	//// �t�s������Ƃ߂�
	//D3DXMatrixInverse(&mtxWorldCutter, NULL, &mtxView);
	//mtxWorldCutter._41 = 0.0f;
	//mtxWorldCutter._42 = 0.0f;
	//mtxWorldCutter._43 = 0.0f;

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotCutter.y, rotCutter.x, rotCutter.z);
	D3DXMatrixMultiply(&mtxWorldCutter, &mtxWorldCutter, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, posCutter.x, posCutter.y, posCutter.z);
	D3DXMatrixMultiply(&mtxWorldCutter, &mtxWorldCutter, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &mtxWorldCutter);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
    device->SetStreamSource(0, D3DVtxBuffCutter, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, D3DTextureCutter);

	// �|���S���̕`��
	device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);

	device->SetRenderState(D3DRS_LIGHTING, TRUE);
	//device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);				// ���ʂ��J�����O

}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT MakeVertexCutter(LPDIRECT3DDEVICE9 device)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&D3DVtxBuffCutter,		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))						// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *vtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffCutter->Lock(0, 0, (void**)&vtx, 0);

		// ���_���W�̐ݒ�
		vtx[0].vtx = D3DXVECTOR3(RANGE_CUTTER[0].x, RANGE_CUTTER[0].y, -5.0f);
		vtx[1].vtx = D3DXVECTOR3(RANGE_CUTTER[1].x, RANGE_CUTTER[1].y, 5.0f);
		vtx[2].vtx = D3DXVECTOR3(RANGE_CUTTER[2].x, RANGE_CUTTER[2].y, -5.0f);
		vtx[3].vtx = D3DXVECTOR3(RANGE_CUTTER[3].x, RANGE_CUTTER[3].y, 5.0f);

		// �@���x�N�g���̐ݒ�
		vtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		vtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		vtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffCutter->Unlock();
	}

	return S_OK;
}

//LINE GetCutterLine(void)
//{
//	LINE wkLine;
//
//	PLANE wkPlane;
//
//	wkLine.vtx[0] = wkPlane.vtx[0] + (wkPlane.vtx[1] - wkPlane.vtx[0]) / 2.0f;
//	wkLine.vtx[1] = wkPlane.vtx[2] + (wkPlane.vtx[3] - wkPlane.vtx[2]) / 2.0f;
//
//	return wkLine;
//}

D3DXVECTOR3 GetCutterPos(void)
{
	return posCutter;
}

PLANE GetCutterState(void)
{
	PLANE wk;
	D3DXMATRIX mtxTranslate, mtxRot, mtxWk;
	D3DXVECTOR3 vec01, vec02, nor;


	D3DXMatrixIdentity(&mtxWk);

	D3DXMatrixRotationYawPitchRoll(&mtxRot, rotCutter.y, rotCutter.x, rotCutter.z);
	D3DXMatrixMultiply(&mtxWk, &mtxWk, &mtxRot);

	D3DXMatrixTranslation(&mtxTranslate, posCutter.x, posCutter.y, posCutter.z);
	D3DXMatrixMultiply(&mtxWk, &mtxWk, &mtxTranslate);

	for (int cntVtx = 0; cntVtx < 4; cntVtx++)
	{// �u���b�N�̃��[�J�����W�����[���h���W�ɕϊ�
		D3DXVec3TransformCoord(&wk.vtx[cntVtx], &RANGE_CUTTER[cntVtx], &mtxWk);
	}


	vec01 = wk.vtx[1] - wk.vtx[0];
	vec02 = wk.vtx[2] - wk.vtx[0];

	D3DXVec3Cross(&nor, &vec01, &vec02);
	D3DXVec3Normalize(&wk.nor, &nor);


	return wk;
	
}
