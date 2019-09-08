//=============================================================================
//
// ���[���̏��� [lane.cpp]
// Author : 
//
//=============================================================================
#include "lane.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	LANE_MODEL		"data/MODEL/car000.x"	// �ǂݍ��ރ��f����
// �X�P�[���̏����l
#define INIT_SCL_X_LANE		(1.0f)					
#define INIT_SCL_Y_LANE		(1.0f)
#define INIT_SCL_Z_LANE		(100000.0f)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	D3DTextureLane;		// �e�N�X�`���ւ̃|�C���^
LPD3DXMESH			D3DXMeshLane;		// ���b�V�����ւ̃|�C���^
LPD3DXBUFFER		D3DXBuffMatLane;	// �}�e���A�����ւ̃|�C���^
DWORD				NumMatLane;			// �}�e���A�����̐�

//=============================================================================
// ����������
//=============================================================================
Lane :: Lane()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DTextureLane = NULL;
	D3DXMeshLane = NULL;
	D3DXBuffMatLane = NULL;
	NumMatLane = 0;
	
	for (int cnt = 0; cnt < LANE_NUM_MAX; cnt++)
	{
		// �ʒu�E�X�P�[���̏����ݒ�
		pos[cnt] = D3DXVECTOR3(-INIT_POS_X_LANE + LANE_SPACE * cnt, INIT_POS_Y_LANE, -INIT_POS_Z_LANE);
		scl[cnt] = D3DXVECTOR3(INIT_SCL_X_LANE, INIT_SCL_Y_LANE, INIT_SCL_Z_LANE);
	}

	// X�t�@�C���̓ǂݍ���
	if (FAILED(D3DXLoadMeshFromX(LANE_MODEL,				// �ǂݍ��ރ��f���t�@�C����(X�t�@�C��)
								D3DXMESH_SYSTEMMEM,		// ���b�V���̍쐬�I�v�V�������w��
								pDevice,				// IDirect3DDevice9�C���^�[�t�F�C�X�ւ̃|�C���^
								NULL,					// �אڐ��f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								&D3DXBuffMatLane,	// �}�e���A���f�[�^���܂ރo�b�t�@�ւ̃|�C���^
								NULL,					// �G�t�F�N�g�C���X�^���X�̔z����܂ރo�b�t�@�ւ̃|�C���^
								&NumMatLane,		// D3DXMATERIAL�\���̂̐�
								&D3DXMeshLane)))	// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^�̃A�h���X
	{
		return;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice,					// �f�o�C�X�ւ̃|�C���^
		TEXTURE_FILENAME,		// �t�@�C���̖��O
		&D3DTextureLane);	// �ǂݍ��ރ������[
#endif
}

//=============================================================================
// �I������
//=============================================================================
 Lane :: ~Lane()
{
	if (D3DTextureLane != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureLane->Release();
		D3DTextureLane = NULL;
	}

	if (D3DXMeshLane != NULL)
	{// ���b�V���̊J��
		D3DXMeshLane->Release();
		D3DXMeshLane = NULL;
	}

	if (D3DXBuffMatLane != NULL)
	{// �}�e���A���̊J��
		D3DXBuffMatLane->Release();
		D3DXBuffMatLane = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void Lane :: Update(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void Lane :: Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int cnt = 0; cnt < LANE_NUM_MAX; cnt++)
	{
		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxWorld);

		// �X�P�[���𔽉f
		D3DXMatrixScaling(&mtxScl, scl[cnt].x, scl[cnt].y, scl[cnt].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, pos[cnt].x, pos[cnt].y, pos[cnt].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �}�e���A�����ɑ΂���|�C���^���擾
		pD3DXMat = (D3DXMATERIAL*)D3DXBuffMatLane->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)NumMatLane; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// �e�N�X�`���̐ݒ�
			pDevice->SetTexture(0, D3DTextureLane);

			// �`��
			D3DXMeshLane->DrawSubset(nCntMat);
		}

		// �}�e���A�����f�t�H���g�ɖ߂�
		pDevice->SetMaterial(&matDef);
	}
}

