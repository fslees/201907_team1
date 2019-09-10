//=============================================================================
//
// �q�b�g���̐��x�\������ [hitqualety.cpp]
// Author : �����~��
//
//=============================================================================
#include "hitquality.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
// �e�N�X�`���[�f�[�^
#define TEXTURE_PERFECT		("data/TEXTURE/perfect.png")
#define TEXTURE_GREAT		("data/TEXTURE/great.png")
#define TEXTURE_GOOD		("data/TEXTURE/good.png")
// ���_�T�C�Y
#define TEXTURE_SIZE_X		(100.0f)
#define TEXTURE_SIZE_Y		(50.0f)
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
HitQualety::HitQualety()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// �ϐ��̏�����
	texNum = PERFECT;
	pos = D3DXVECTOR3(INIT_POS_X, INIT_POS_Y, INIT_POS_Z);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	use = false;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_PERFECT,	// �t�@�C���̖��O
								&D3DTexture[PERFECT]);	// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_GREAT,		// �t�@�C���̖��O
								&D3DTexture[GREAT]);	// �ǂݍ��ރ������[
	D3DXCreateTextureFromFile(Device,				// �f�o�C�X�ւ̃|�C���^
								TEXTURE_GOOD,		// �t�@�C���̖��O
								&D3DTexture[GOOD]);	// �ǂݍ��ރ������[

	//���_�̍쐬
	MakeVertex(Device);
}

//*****************************************************************************
// �Q�[���̏I��
//*****************************************************************************
HitQualety::~HitQualety()
{
	for (int i = 0; i < TEX_MAX; i++)
	{
		if (D3DTexture[i] != NULL)
		{// �e�N�X�`���̊J��
			D3DTexture[i]->Release();
			D3DTexture[i] = NULL;
		}
	}
}

//*****************************************************************************
// �Q�[���̍X�V
//*****************************************************************************
void HitQualety:: Update()
{
	SetSclAnim();
}

//*****************************************************************************
// ���U���g��ʂ̕`��
//*****************************************************************************
void HitQualety::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// Z��r�Ȃ�
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// ���e�X�g��L����
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	// ���C���e�B���O�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (use)
	{
		// �r���[�}�g���b�N�X���擾
		mtxView = camera.GetMtxView();

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �|���S���𐳖ʂɌ�����
		mtxWorld._11 = mtxView._11;
		mtxWorld._12 = mtxView._21;
		mtxWorld._13 = mtxView._31;
		mtxWorld._21 = mtxView._12;
		mtxWorld._22 = mtxView._22;
		mtxWorld._23 = mtxView._32;
		mtxWorld._31 = mtxView._13;
		mtxWorld._32 = mtxView._23;
		mtxWorld._33 = mtxView._33;

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScale, scl.x,
			scl.y,
			scl.z);
		D3DXMatrixMultiply(&mtxWorld,
			&mtxWorld, &mtxScale);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos.x,
			pos.y,
			pos.z);
		D3DXMatrixMultiply(&mtxWorld,
			&mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// ���_�o�b�t�@���f�o�C�X�̃f�[�^�X�g���[���Ƀo�C���h
		pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

		// ���_�t�H�[�}�b�g�̐ݒ�
		pDevice->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, D3DTexture[texNum]);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX, NUM_POLYGON);
	}

	// ���C���e�B���O��L���ɂ���
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// ���e�X�g�𖳌�
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z��r����
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=========================================
//���_�̍쐬
//=========================================
HRESULT HitQualety::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
		D3DUSAGE_WRITEONLY,			// ���_�o�b�t�@�̎g�p�@�@
		FVF_VERTEX_3D,				// �g�p���钸�_�t�H�[�}�b�g
		D3DPOOL_MANAGED,			// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
		&D3DVtxBuff,	// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
		NULL)))						// NULL�ɐݒ�
	{
		return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *pVtx;

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// ���_���W�̐ݒ�
		pVtx[0].vtx = D3DXVECTOR3(-TEXTURE_SIZE_X / 2, -TEXTURE_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-TEXTURE_SIZE_X / 2, TEXTURE_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TEXTURE_SIZE_X / 2, -TEXTURE_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TEXTURE_SIZE_X / 2, TEXTURE_SIZE_Y / 2, 0.0f);

		// �@���̐ݒ�
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// ���ˌ��̐ݒ�
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// �e�N�X�`�����W�̐ݒ�
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}


//=========================================
// �g��A�j���[�V����
//=========================================
void HitQualety::SetSclAnim()
{
	if (use)
	{
		scl.x += 0.1f;
		scl.y += 0.1f;
	}

	if (scl == D3DXVECTOR3(1.0f, 1.0f, 1.0f))
	{
		use = false;
	}
}