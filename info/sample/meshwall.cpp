//=============================================================================
//
// ���b�V���ǂ̏��� [meshwall.cpp]
// Author : 
//
//=============================================================================
#include "meshwall.h"
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MAX_MESH_WALL		(10)						// �ǂ̑���
#define	TEXTURE_FILENAME	"data/TEXTURE/wall000.jpg"	// �ǂݍ��ރe�N�X�`���t�@�C����
#define	VALUE_MOVE_WALL		(5.0f)						// �ړ����x
#define	VALUE_ROTATE_WALL	(D3DX_PI * 0.001f)			// ��]���x

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9 D3DTexture = NULL;		// �e�N�X�`���ǂݍ��ݏꏊ

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9 D3DIdxBuff;		// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^

	D3DXMATRIX mtxWorld;					// ���[���h�}�g���b�N�X
	D3DXVECTOR3 pos;						// �|���S���\���ʒu�̒��S���W
	D3DXVECTOR3 rot;						// �|���S���̉�]�p
	int numBlockX, numBlockY;				// �u���b�N��
	int numVertex;							// �����_��	
	int numVertexIndex;						// ���C���f�b�N�X��
	int numPolygon;							// ���|���S����
	float blockSizeX, blockSizeY;			// �u���b�N�T�C�Y
} MESH_WALL;

MESH_WALL MeshWall[MAX_MESH_WALL];			// ���b�V���ǃ��[�N
int NumMeshField = 0;						// ���b�V���ǂ̐�

//=============================================================================
// ����������
//=============================================================================
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
							int numBlockX, int numBlockY, float blockSizeX, float blockSizeZ)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	MESH_WALL *mesh;

	if(NumMeshField >= MAX_MESH_WALL)
	{
		return E_FAIL;
	}

	// �e�N�X�`���̓ǂݍ���
	if(!D3DTexture)
	{
		D3DXCreateTextureFromFile(device,				// �f�o�C�X�ւ̃|�C���^
									TEXTURE_FILENAME,	// �t�@�C���̖��O
									&D3DTexture);		// �ǂݍ��ރ������[
	}

	mesh = &MeshWall[NumMeshField];
	NumMeshField++;

	// �|���S���\���ʒu�̒��S���W��ݒ�
	mesh->pos = pos;

	mesh->rot = rot;

	// �u���b�N���̐ݒ�
	mesh->numBlockX = numBlockX;
	mesh->numBlockY = numBlockY;

	// ���_���̐ݒ�
	mesh->numVertex = (numBlockX + 1) * (numBlockY + 1);

	// �C���f�b�N�X���̐ݒ�
	mesh->numVertexIndex = (numBlockX + 1) * 2 * numBlockY + (numBlockY - 1) * 2;

	// �|���S�����̐ݒ�
	mesh->numPolygon = numBlockX * numBlockY * 2 + (numBlockY - 1) * 4;

	// �u���b�N�T�C�Y�̐ݒ�
	mesh->blockSizeX = blockSizeX;
	mesh->blockSizeY = blockSizeZ;

	// �I�u�W�F�N�g�̒��_�o�b�t�@�𐶐�
    if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * mesh->numVertex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
												FVF_VERTEX_3D,					// �g�p���钸�_�t�H�[�}�b�g
												D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&mesh->D3DVtxBuff,				// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))							// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	// �I�u�W�F�N�g�̃C���f�b�N�X�o�b�t�@�𐶐�
    if(FAILED(device->CreateIndexBuffer(sizeof(WORD) * mesh->numVertexIndex,	// ���_�f�[�^�p�Ɋm�ۂ���o�b�t�@�T�C�Y(�o�C�g�P��)
												D3DUSAGE_WRITEONLY,				// ���_�o�b�t�@�̎g�p�@�@
												D3DFMT_INDEX16,					// �g�p����C���f�b�N�X�t�H�[�}�b�g
												D3DPOOL_MANAGED,				// ���\�[�X�̃o�b�t�@��ێ����郁�����N���X���w��
												&mesh->D3DIdxBuff,				// �C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
												NULL)))							// NULL�ɐݒ�
	{
        return E_FAIL;
	}

	{//���_�o�b�t�@�̒��g�𖄂߂�
		VERTEX_3D *vtx;
#if 0
		const float texSizeX = 1.0f / g_nNumBlockX;
		const float texSizeZ = 1.0f / g_nNumBlockY;
#else
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;
#endif

		// ���_�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		mesh->D3DVtxBuff->Lock( 0, 0, (void**)&vtx, 0 );

		for(int cntVtxY = 0; cntVtxY < (mesh->numBlockY + 1); cntVtxY++)
		{
			for(int cntVtxX = 0; cntVtxX < (mesh->numBlockX + 1); cntVtxX++)
			{
				// ���_���W�̐ݒ�
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].vtx.x = -(mesh->numBlockX / 2.0f) * mesh->blockSizeX + cntVtxX * mesh->blockSizeX;
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].vtx.y = mesh->numBlockY * mesh->blockSizeY - cntVtxY * mesh->blockSizeY;
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].vtx.z = 0.0f;

				// �@���̐ݒ�
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				// ���ˌ��̐ݒ�
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].diffuse = col;

				// �e�N�X�`�����W�̐ݒ�
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].tex.x = texSizeX * cntVtxX;
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].tex.y = texSizeZ * cntVtxY;
			}
		}

		// ���_�f�[�^���A�����b�N����
		mesh->D3DVtxBuff->Unlock();
	}

	{//�C���f�b�N�X�o�b�t�@�̒��g�𖄂߂�
		WORD *idx;

		// �C���f�b�N�X�f�[�^�͈̔͂����b�N���A���_�o�b�t�@�ւ̃|�C���^���擾
		mesh->D3DIdxBuff->Lock( 0, 0, (void**)&idx, 0 );

		int cntIdx = 0;
		for(int cntVtxY = 0; cntVtxY < mesh->numBlockY; cntVtxY++)
		{
			if(cntVtxY > 0)
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				idx[cntIdx] = (cntVtxY + 1) * (mesh->numBlockX + 1);
				cntIdx++;
			}

			for(int cntVtxX = 0; cntVtxX < (mesh->numBlockX + 1); cntVtxX++)
			{
				idx[cntIdx] = (cntVtxY + 1) * (mesh->numBlockX + 1) + cntVtxX;
				cntIdx++;
				idx[cntIdx] = cntVtxY * (mesh->numBlockX + 1) + cntVtxX;
				cntIdx++;
			}

			if(cntVtxY < (mesh->numBlockY - 1))
			{// �k�ރ|���S���̂��߂̃_�u��̐ݒ�
				idx[cntIdx] = cntVtxY * (mesh->numBlockX + 1) + mesh->numBlockX;
				cntIdx++;
			}
		}

		// �C���f�b�N�X�f�[�^���A�����b�N����
		mesh->D3DIdxBuff->Unlock();
	}



	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitMeshWall(void)
{
	MESH_WALL *mesh;
	int nCntMeshField;

	for(nCntMeshField = 0; nCntMeshField < NumMeshField; nCntMeshField++)
	{
		mesh = &MeshWall[nCntMeshField];

		if(mesh->D3DVtxBuff)
		{// ���_�o�b�t�@�̊J��
			mesh->D3DVtxBuff->Release();
			mesh->D3DVtxBuff = NULL;
		}

		if(mesh->D3DIdxBuff)
		{// �C���f�b�N�X�o�b�t�@�̊J��
			mesh->D3DIdxBuff->Release();
			mesh->D3DIdxBuff = NULL;
		}
	}

	if(D3DTexture)
	{// �e�N�X�`���̊J��
		D3DTexture->Release();
		D3DTexture = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	MESH_WALL *mesh;
	int nCntMeshField;

	for(nCntMeshField = 0; nCntMeshField < NumMeshField; nCntMeshField++)
	{
		mesh = &MeshWall[nCntMeshField];

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mesh->mtxWorld);

		// ��]�𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, mesh->rot.y, mesh->rot.x, mesh->rot.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxRot);

		// �ړ��𔽉f
		D3DXMatrixTranslation(&mtxTranslate, mesh->pos.x, mesh->pos.y, mesh->pos.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxTranslate);

		// ���[���h�}�g���b�N�X�̐ݒ�
		device->SetTransform(D3DTS_WORLD, &mesh->mtxWorld);

		// ���_�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		device->SetStreamSource(0, mesh->D3DVtxBuff, 0, sizeof(VERTEX_3D));

		// �C���f�b�N�X�o�b�t�@�������_�����O�p�C�v���C���ɐݒ�
		device->SetIndices(mesh->D3DIdxBuff);

		// ���_�t�H�[�}�b�g�̐ݒ�
		device->SetFVF(FVF_VERTEX_3D);

		// �e�N�X�`���̐ݒ�
		device->SetTexture(0, D3DTexture);

		// �|���S���̕`��
		device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, mesh->numVertex, 0, mesh->numPolygon);
	}
}

