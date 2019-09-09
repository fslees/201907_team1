//=============================================================================
//
// ���胉�C������ [hitline.cpp]
// Author : GP12A332_26_�c�����z
//
//=============================================================================
#include "main.h"
#include "hitline.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_LINE		"data/TEXTURE/hitLine.png"		// �ǂݍ��ރe�N�X�`���t�@�C����
#define INIT_POS_X			(0.0f)						// X���W�̏����ʒu
#define INIT_POS_Y			(50.0f)						// Y���W
#define INIT_POS_Z			(0.0f)						// Z���W

#define	INIT_SIZE_X			(1.0f)						// ���胉�C���̃T�C�Y X����
#define	INIT_SIZE_Y			(1.0f)						// Y����
#define	INIT_SIZE_Z			(1.0f)						// Z����

#define VTX_X				(200.0f)					// ���_X���W
#define VTX_Z				(20.0f)					// ���_Z���W

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************

//=============================================================================
// ����������
//=============================================================================
HitLine::HitLine()
{	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �ʒu�E��]�E�X�P�[���̏����ݒ�
	pos = D3DXVECTOR3(INIT_POS_X, INIT_POS_Y, INIT_POS_Z);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(INIT_SIZE_X, INIT_SIZE_Y, INIT_SIZE_Z);

	// ���_���̍쐬
	MakeVertexHitLine(pDevice);

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_LINE,			// �t�@�C���̖��O
		&D3DTexture);	// �ǂݍ��ރ������[
	
}

//=============================================================================
// �I������
//=============================================================================
HitLine::~HitLine(void)
{
	if (D3DTexture != NULL)
	{// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	if (D3DVtxBuff != NULL)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void HitLine::Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void HitLine::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxWorld);

	// �X�P�[���𔽉f
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
	pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, D3DTexture);

	// �|���S���̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// ���_�̍쐬
//=============================================================================
HRESULT HitLine::MakeVertexHitLine(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuff,			// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(VTX_X, 0.0f, 0);
		pVtx[1].vtx = D3DXVECTOR3(-VTX_X, 0.0f, 0);
		pVtx[2].vtx = D3DXVECTOR3(VTX_X, 0.0f, VTX_Z);
		pVtx[3].vtx = D3DXVECTOR3(-VTX_X, 0.0f, VTX_Z);

		// �@���x�N�g���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}
