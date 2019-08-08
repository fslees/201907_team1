//=============================================================================
//
// �e���� [Shadow.cpp]
// Author : 
//
//=============================================================================
#include "Shadow.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_SHADOW		"data/TEXTURE/shadow000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	SHADOW_SIZE_X		(50.0f)							// �e�̕�
#define	SHADOW_SIZE_Z		(50.0f)							// �e�̍���

#define	MAX_SHADOW			(128)							// �e�ő吔

//*****************************************************************************
// �\���̒�`
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ��]
	bool use;				// �g�p���Ă��邩�ǂ���
} SHADOW;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 device);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureShadow = NULL;		// �e�N�X�`���ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffShadow = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

SHADOW					Shadow[MAX_SHADOW];				// �e���[�N

//=============================================================================
// ����������
//=============================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	// ���_���̍쐬
	MakeVertexShadow(device);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(device,						// �f�o�C�X�ւ̃|�C���^
								TEXTURE_SHADOW,				// �t�@�C���̖��O
								&D3DTextureShadow);			// �ǂݍ��ރ������[

	for(int cntShadow = 0; cntShadow < MAX_SHADOW; cntShadow++)
	{
		Shadow[cntShadow].pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		Shadow[cntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Shadow[cntShadow].use = false;
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitShadow(void)
{
	if(D3DTextureShadow != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureShadow->Release();
		D3DTextureShadow = NULL;
	}

	if(D3DVtxBuffShadow != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuffShadow->Release();
		D3DVtxBuffShadow = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateShadow(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
#if 0
	D3DXQUATERNION quat;
	D3DXVECTOR3 vecUpObj, vecUpField, outVec;
	float fDotProduct,fRot;
#endif

	// ���Z����
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);	// ���� = �]����(DEST) - �]����(SRC)
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z��r�Ȃ�
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for(int cntShadow = 0; cntShadow < MAX_SHADOW; cntShadow++)
	{
		if(Shadow[cntShadow].use)
		{
			// ���[���h�}�g���b�N�X�̏�����
			D3DXMatrixIdentity(&Shadow[cntShadow].mtxWorld);

#if 0
			// ��]�𔽉f
			D3DXQuaternionIdentity(&quat);

			vecUpObj = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �I�u�W�F�N�g�̏����
			vecUpField = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// �n�ʂ̖@��

			// �I�u�W�F�N�g�̏�����ƒn�ʂ̖@���̊O�ς����]�������߂�
			D3DXVec3Cross(&outVec, &vecUpObj, &vecUpField);

			// �I�u�W�F�N�g�̏�����ƒn�ʂ̖@���̂Ȃ��p�����߂�
			fDotProduct = D3DXVec3Dot(&vecUpObj, &vecUpField);
			fRot = acosf(fDotProduct / (sqrtf(vecUpObj.x * vecUpObj.x + vecUpObj.y * vecUpObj.y + vecUpObj.z * vecUpObj.z)
														* sqrtf(vecUpField.x * vecUpField.x + vecUpField.y * vecUpField.y + vecUpField.z * vecUpField.z)));

			// ��]���ƂȂ��p����N�H�[�^�j�I�������߁A��]�}�g���b�N�X���Z�o
			D3DXQuaternionRotationAxis(&quat, &outVec, fRot);
			D3DXMatrixRotationQuaternion(&mtxRot, &quat);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);
#endif
			// ��]�𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, Shadow[cntShadow].rot.y, Shadow[cntShadow].rot.x, Shadow[cntShadow].rot.z);
			D3DXMatrixMultiply(&Shadow[cntShadow].mtxWorld, &Shadow[cntShadow].mtxWorld, &mtxRot);

			// �ړ��𔽉f
			D3DXMatrixTranslation(&mtxTranslate, Shadow[cntShadow].pos.x,
													Shadow[cntShadow].pos.y,
													Shadow[cntShadow].pos.z);
			D3DXMatrixMultiply(&Shadow[cntShadow].mtxWorld,
										&Shadow[cntShadow].mtxWorld, &mtxTranslate);

			// ���[���h�}�g���b�N�X�̐ݒ�
			device->SetTransform(D3DTS_WORLD, &Shadow[cntShadow].mtxWorld);

			// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
			device->SetStreamSource(0, D3DVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// ���_�t�H�[�}�b�g�̐ݒ�
			device->SetFVF(FVF_VERTEX_3D);

			// �e�N�X�`���̐ݒ�
			device->SetTexture(0, D3DTextureShadow);

			// �|���S���̕`��
			device->DrawPrimitive(D3DPT_TRIANGLESTRIP, (cntShadow * 4), NUM_POLYGON);
		}
	}

	// �ʏ�u�����h
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// ���� = �]����(SRC) + �]����(DEST)
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z��r����
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// ���_���̍쐬
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 device)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SHADOW,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,						// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,							// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,						// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&D3DVtxBuffShadow,						// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))									// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *vtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffShadow->Lock(0, 0, (void**)&vtx, 0);

		for(int cntShadow = 0; cntShadow < MAX_SHADOW; cntShadow++, vtx += 4)
		{
			// ���_���W�̐ݒ�
			vtx[0].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			vtx[1].vtx = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			vtx[2].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			vtx[3].vtx = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

			// �@���̐ݒ�
			vtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// ���ˌ��̐ݒ�
			vtx[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			vtx[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			vtx[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			vtx[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

			// �e�N�X�`�����W�̐ݒ�
			vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffShadow->Unlock();
	}

	return S_OK;
}

//=============================================================================
// ���_���W�̐ݒ�
//=============================================================================
void SetVertexShadow(int idxShadow, float sizeX, float sizeZ)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *vtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffShadow->Lock(0, 0, (void**)&vtx, 0);

		vtx += (idxShadow * 4);

		// ���_���W�̐ݒ�
		vtx[0].vtx = D3DXVECTOR3(-sizeX / 2, 0.0f, sizeZ / 2);
		vtx[1].vtx = D3DXVECTOR3(sizeX / 2, 0.0f, sizeZ / 2);
		vtx[2].vtx = D3DXVECTOR3(-sizeX / 2, 0.0f, -sizeZ / 2);
		vtx[3].vtx = D3DXVECTOR3(sizeX / 2, 0.0f, -sizeZ / 2);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// ���_�J���[�̐ݒ�
//=============================================================================
void SetColorShadow(int idxShadow, D3DXCOLOR col)
{
	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *vtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffShadow->Lock(0, 0, (void**)&vtx, 0);

		vtx += (idxShadow * 4);

		// ���_���W�̐ݒ�
		vtx[0].diffuse =
		vtx[1].diffuse =
		vtx[2].diffuse =
		vtx[3].diffuse = col;

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// �e�̍쐬
//=============================================================================
int CreateShadow(D3DXVECTOR3 pos, float sizeX, float sizeZ)
{
	int idxShadow = -1;

	for(int cntShadow = 0; cntShadow < MAX_SHADOW; cntShadow++)
	{
		if(!Shadow[cntShadow].use)
		{
			Shadow[cntShadow].pos = pos;
			Shadow[cntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Shadow[cntShadow].use = true;

			SetVertexShadow(cntShadow, sizeX, sizeZ);

			idxShadow = cntShadow;
			break;
		}
	}

	return idxShadow;
}

//=============================================================================
// �e�̔j��
//=============================================================================
void ReleaseShadow(int idxShadow)
{
	if(idxShadow >= 0 && idxShadow < MAX_SHADOW)
	{
		Shadow[idxShadow].use = false;
	}
}

//=============================================================================
// �ʒu�̐ݒ�
//=============================================================================
void SetPositionShadow(int idxShadow, D3DXVECTOR3 pos)
{
	Shadow[idxShadow].pos = pos;
}

