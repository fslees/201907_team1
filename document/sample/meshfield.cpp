//=============================================================================
//
// ���b�V���n�ʂ̏��� [meshfield.cpp]
// Author : 
//
//=============================================================================
#include "meshfield.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	TEXTURE_FILENAME	"data/TEXTURE/field004.jpg"		// �ǂݍ��ރe�N�X�`���t�@�C����

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 D3DTextureField;				// �e�N�X�`���ǂݍ��ݏꏊ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffField;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECT3DINDEXBUFFER9 D3DIdxBuffField;			// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

D3DXMATRIX MtxWorldField;						// ���[���h�}�g���b�N�X
D3DXVECTOR3 PosField;							// �|���S���\���ʒu�̒��S���W
D3DXVECTOR3 RotField;							// �|���S���̉�]�p

int		NumBlockXField, NumBlockZField;			// �u���b�N��
int		NumVertexField;							// �����_��	
int		NumVertexIndexField;					// ���C���f�b�N�X��
int		NumPolygonField;						// ���|���S����
float	BlockSizeXField, BlockSizeZField;		// �u���b�N�T�C�Y

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
							int numBlockX, int numBlockZ, float blockSizeX, float blockSizeZ)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	// �|���S���\���ʒu�̒��S���W��ݒ�
	PosField = pos;

	RotField = rot;

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILENAME,		// �t�@�C���̖��O
								&D3DTextureField);		// �ǂݍ��ރ������[

	// �u���b�N���̐ݒ�
	NumBlockXField = numBlockX;
	NumBlockZField = numBlockZ;

	// ���_���̐ݒ�
	NumVertexField = (numBlockX + 1) * (numBlockZ + 1);
	int numVertexXField = numBlockX + 1;
	int numVertexZField = numBlockZ + 1;


	// �C���f�b�N�X���̐ݒ�
	NumVertexIndexField = (numBlockX + 1) * 2 * numBlockZ + (numBlockZ - 1) * 2;

	// �|���S�����̐ݒ�
	NumPolygonField = numBlockX * numBlockZ * 2 + (numBlockZ - 1) * 4;

	// �u���b�N�T�C�Y�̐ݒ�
	BlockSizeXField = blockSizeX;
	BlockSizeZField = blockSizeZ;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * NumVertexField,		// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,						// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&D3DVtxBuffField,					// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))								// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
    if(FAILED(device->CreateIndexBuffer(sizeof(WORD) * NumVertexIndexField,			// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,					// ���_�o�b�t�@�̎g�p�@�@
												D3DFMT_INDEX16,						// �g�p����C���f�b�N�X�t�H�[�}�b�g
												D3DPOOL_MANAGED,					// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&D3DIdxBuffField,					// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))								// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *vtx;
#if 0
		const float texSizeX = 1.0f / numBlockX;
		const float texSizeZ = 1.0f / numBlockZ;
#else
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;
#endif

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DVtxBuffField->Lock( 0, 0, (void**)&vtx, 0 );

		for(int cntVtxZ = 0; cntVtxZ < numVertexZField; cntVtxZ++)
		{
			for(int cntVtxX = 0; cntVtxX < numVertexXField; cntVtxX++)
			{
				int no = cntVtxZ * numVertexXField + cntVtxX;
				// ���_���W�̐ݒ�
				vtx[no].vtx.x = -(NumBlockXField / 2.0f) * BlockSizeXField + cntVtxX * BlockSizeXField;
				vtx[no].vtx.y = 0.0f;
				vtx[no].vtx.z = (NumBlockZField / 2.0f) * BlockSizeZField - cntVtxZ * BlockSizeZField;

				// �@���̐ݒ�
				vtx[no].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				// ���ˌ��̐ݒ�
				vtx[no].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// �e�N�X�`�����W�̐ݒ�
				vtx[no].tex.x = texSizeX * cntVtxX;
				vtx[no].tex.y = texSizeZ * cntVtxZ;
			}
		}

		// ���_�f�[�^���A�����b�N����
		D3DVtxBuffField->Unlock();
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD *idx;

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		D3DIdxBuffField->Lock( 0, 0, (void**)&idx, 0 );

		int cntIdx = 0;
		for(int cntVtxZ = 0; cntVtxZ < NumBlockZField; cntVtxZ++)
		{
			if(cntVtxZ > 0)
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				idx[cntIdx] = (cntVtxZ + 1) * (NumBlockXField + 1);
				cntIdx++;
			}

			for(int cntVtxX = 0; cntVtxX < (NumBlockXField + 1); cntVtxX++)
			{
				idx[cntIdx] = (cntVtxZ + 1) * (NumBlockXField + 1) + cntVtxX;
				cntIdx++;
				idx[cntIdx] = cntVtxZ * (NumBlockXField + 1) + cntVtxX;
				cntIdx++;
			}

			if(cntVtxZ < (NumBlockZField - 1))
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				idx[cntIdx] = cntVtxZ * (NumBlockXField + 1) + NumBlockXField;
				cntIdx++;
			}
		}

		// �C���f�b�N�X�f�[�^���A�����b�N����
		D3DIdxBuffField->Unlock();
	}

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshField(void)
{
	if(D3DVtxBuffField)
	{// ���_�o�b�t�@�̊J��
		D3DVtxBuffField->Release();
		D3DVtxBuffField = NULL;
	}

	if(D3DIdxBuffField)
	{// �C���f�b�N�X�o�b�t�@�̊J��
		D3DIdxBuffField->Release();
		D3DIdxBuffField = NULL;
	}

	if(D3DTextureField)
	{// �e�N�X�`���̊J��
		D3DTextureField->Release();
		D3DTextureField = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&MtxWorldField);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, RotField.y, RotField.x, RotField.z);
	D3DXMatrixMultiply(&MtxWorldField, &MtxWorldField, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, PosField.x, PosField.y, PosField.z);
	D3DXMatrixMultiply(&MtxWorldField, &MtxWorldField, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &MtxWorldField);

	// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	device->SetStreamSource(0, D3DVtxBuffField, 0, sizeof(VERTEX_3D));

	// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
	device->SetIndices(D3DIdxBuffField);

	// ���_�t�H�[�}�b�g�̐ݒ�
	device->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	device->SetTexture(0, D3DTextureField);

	// �|���S���̕`��
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, NumVertexField, 0, NumPolygonField);
}

