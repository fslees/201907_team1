//=============================================================================
//
// ���f������ [model.cpp]
// Author : 
//
//=============================================================================
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	MODEL_AIRPLANE		"data/MODEL/airplane000.x"	// �ǂݍ��ރ��f����
#define	VALUE_MOVE_MODEL	(0.50f)						// �ړ����x
#define	RATE_MOVE_MODEL		(0.20f)						// �ړ������W��
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// ��]���x
#define	RATE_ROTATE_MODEL	(0.20f)						// ��]�����W��

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECT3DTEXTURE9	D3DTextureModel;		// �e�N�X�`���ǂݍ��ݏꏊ
LPD3DXMESH			D3DXMeshModel;			// ID3DXMesh�C���^�[�t�F�C�X�ւ̃|�C���^
LPD3DXBUFFER		D3DXBuffMatModel;		// ���b�V���̃}�e���A�������i�[
DWORD				NumMatModel;			// �������̑���

D3DXMATRIX			MtxWorldModel;			// ���[���h�}�g���b�N�X
D3DXVECTOR3			PosModel;				// ���݂̈ʒu
D3DXVECTOR3			MoveModel;				// �ړ���
D3DXVECTOR3			RotModel;				// ���݂̌���
D3DXVECTOR3			RotDestModel;			// �ړI�̌���

int					IdxShadow;				// �eID
float				SizeShadow;				// �e�̃T�C�Y
D3DXCOLOR			ColShadow;				// �e�̐F

//=============================================================================
// ����������
//=============================================================================
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DTextureModel = NULL;
	D3DXMeshModel = NULL;
	D3DXBuffMatModel = NULL;

	PosModel = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	MoveModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RotDestModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// X�t�@�C���̓ǂݍ���
	if(FAILED(D3DXLoadMeshFromX(MODEL_AIRPLANE,
								D3DXMESH_SYSTEMMEM,
								device,
								NULL,
								&D3DXBuffMatModel,
								NULL,
								&NumMatModel,
								&D3DXMeshModel)))
	{
		return E_FAIL;
	}

#if 0
	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(device,					// �f�o�C�X�ւ̃|�C���^
								TEXTURE_FILENAME,		// �t�@�C���̖��O
								&D3DTextureModel);		// �ǂݍ��ރ������[
#endif

	// �e�̐���
	IdxShadow = CreateShadow(PosModel, 25.0f, 25.0f);

	SizeShadow = 25.0f;
	ColShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	return S_OK;
}

//=============================================================================
// �I������
//=============================================================================
void UninitModel(void)
{
	if(D3DTextureModel != NULL)
	{// �e�N�X�`���̊J��
		D3DTextureModel->Release();
		D3DTextureModel = NULL;
	}

	if(D3DXMeshModel != NULL)
	{// ���b�V���̊J��
		D3DXMeshModel->Release();
		D3DXMeshModel = NULL;
	}

	if(D3DXBuffMatModel != NULL)
	{// �}�e���A���̊J��
		D3DXBuffMatModel->Release();
		D3DXBuffMatModel = NULL;
	}
}

//=============================================================================
// �X�V����
//=============================================================================
void UpdateModel(void)
{
	D3DXVECTOR3 rotCamera;
	float diffRotY;

	// �J�����̌����擾
	rotCamera = GetRotCamera();

	if(GetKeyboardPress(DIK_LEFT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// ���O�ړ�
			MoveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y + D3DX_PI * 0.75f;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// ����ړ�
			MoveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y + D3DX_PI * 0.25f;
		}
		else
		{// ���ړ�
			MoveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y + D3DX_PI * 0.50f;
		}
	}
	else if(GetKeyboardPress(DIK_RIGHT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// �E�O�ړ�
			MoveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y - D3DX_PI * 0.75f;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// �E��ړ�
			MoveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y - D3DX_PI * 0.25f;
		}
		else
		{// �E�ړ�
			MoveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y - D3DX_PI * 0.50f;
		}
	}
	else if(GetKeyboardPress(DIK_UP))
	{// �O�ړ�
		MoveModel.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
		MoveModel.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;

		RotDestModel.y = D3DX_PI + rotCamera.y;
	}
	else if(GetKeyboardPress(DIK_DOWN))
	{// ��ړ�
		MoveModel.x -= sinf(rotCamera.y) * VALUE_MOVE_MODEL;
		MoveModel.z -= cosf(rotCamera.y) * VALUE_MOVE_MODEL;

		RotDestModel.y = rotCamera.y;
	}

	if(GetKeyboardPress(DIK_LSHIFT))
	{// ����]
		RotDestModel.y -= VALUE_ROTATE_MODEL;
		if(RotDestModel.y < -D3DX_PI)
		{
			RotDestModel.y += D3DX_PI * 2.0f;
		}
	}
	if(GetKeyboardPress(DIK_RSHIFT))
	{// �E��]
		RotDestModel.y += VALUE_ROTATE_MODEL;
		if(RotDestModel.y > D3DX_PI)
		{
			RotDestModel.y -= D3DX_PI * 2.0f;
		}
	}

	if(GetKeyboardPress(DIK_I))
	{// �㏸
		MoveModel.y += VALUE_MOVE_MODEL * 0.5f;

		if(PosModel.y < 75.0f)
		{
			SizeShadow += 0.2f;
			ColShadow.a -= 0.004f;
		}
	}
	if(GetKeyboardPress(DIK_K))
	{// ���~
		MoveModel.y -= VALUE_MOVE_MODEL * 0.5f;

		if(PosModel.y > 5.0f)
		{
			SizeShadow -= 0.2f;
			ColShadow.a += 0.004f;
		}
	}

	// �ړI�̊p�x�܂ł̍���
	diffRotY = RotDestModel.y - RotModel.y;
	if(diffRotY > D3DX_PI)
	{
		diffRotY -= D3DX_PI * 2.0f;
	}
	if(diffRotY < -D3DX_PI)
	{
		diffRotY += D3DX_PI * 2.0f;
	}

	// �ړI�̊p�x�܂Ŋ�����������
	RotModel.y += diffRotY * RATE_ROTATE_MODEL;
	if(RotModel.y > D3DX_PI)
	{
		RotModel.y -= D3DX_PI * 2.0f;
	}
	if(RotModel.y < -D3DX_PI)
	{
		RotModel.y += D3DX_PI * 2.0f;
	}

	/// �ʒu�ړ�
	PosModel.x += MoveModel.x;
	PosModel.y += MoveModel.y;
	if(PosModel.y < 5.0f)
	{
		PosModel.y = 5.0f;
	}
	if(PosModel.y > 75.0f)
	{
		PosModel.y = 75.0f;
	}
	PosModel.z += MoveModel.z;

	// �ړ��ʂɊ�����������
	MoveModel.x += (0.0f - MoveModel.x) * RATE_MOVE_MODEL;
	MoveModel.y += (0.0f - MoveModel.y) * RATE_MOVE_MODEL;
	MoveModel.z += (0.0f - MoveModel.z) * RATE_MOVE_MODEL;

	if(PosModel.x < -310.0f)
	{
		PosModel.x = -310.0f;
	}
	if(PosModel.x > 310.0f)
	{
		PosModel.x = 310.0f;
	}
	if(PosModel.z < -310.0f)
	{
		PosModel.z = -310.0f;
	}
	if(PosModel.z > 310.0f)
	{
		PosModel.z = 310.0f;
	}

	// �e�̈ʒu�ݒ�
	SetPositionShadow(IdxShadow, D3DXVECTOR3(PosModel.x, 0.1f, PosModel.z));

	SetVertexShadow(IdxShadow, SizeShadow, SizeShadow);
	SetColorShadow(IdxShadow, ColShadow);

	PrintDebugProc("[��s�@�̈ʒu  �F(%f : %f : %f)]\n", PosModel.x, PosModel.y, PosModel.z);
	PrintDebugProc("[��s�@�̌���  �F(%f) < �ړI�̌���:(%f) >]\n", RotModel.y, RotDestModel.y);
	PrintDebugProc("\n");

	PrintDebugProc("*** ��s�@���� ***\n");
	PrintDebugProc("�O�ړ� : ��\n");
	PrintDebugProc("��ړ� : ��\n");
	PrintDebugProc("���ړ� : ��\n");
	PrintDebugProc("�E�ړ� : ��\n");
	PrintDebugProc("�㏸   : �h\n");
	PrintDebugProc("���~   : �j\n");
	PrintDebugProc("������ : LSHIFT\n");
	PrintDebugProc("�E���� : RSHIFT\n");
}

//=============================================================================
// �`�揈��
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *D3DXMat;
	D3DMATERIAL9 matDef;

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&MtxWorldModel);

	// ��]�𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, RotModel.y, RotModel.x, RotModel.z);
	D3DXMatrixMultiply(&MtxWorldModel, &MtxWorldModel, &mtxRot);

	// �ړ��𔽉f
	D3DXMatrixTranslation(&mtxTranslate, PosModel.x, PosModel.y, PosModel.z);
	D3DXMatrixMultiply(&MtxWorldModel, &MtxWorldModel, &mtxTranslate);

	// ���[���h�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_WORLD, &MtxWorldModel);

	// ���݂̃}�e���A�����擾
	device->GetMaterial(&matDef);

	// �}�e���A�����ɑ΂���|�C���^���擾
	D3DXMat = (D3DXMATERIAL*)D3DXBuffMatModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat < (int)NumMatModel; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		device->SetMaterial(&D3DXMat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		device->SetTexture(0, D3DTextureModel);

		// �`��
		D3DXMeshModel->DrawSubset(nCntMat);
	}

	// �}�e���A�����f�t�H���g�ɖ߂�
	device->SetMaterial(&matDef);
}

//=============================================================================
// �ʒu�擾
//=============================================================================
D3DXVECTOR3 GetPositionModel(void)
{
	return PosModel;
}

//=============================================================================
// �����擾
//=============================================================================
D3DXVECTOR3 GetRotationModel(void)
{
	return RotModel;
}

//=============================================================================
// �ړI�̌����擾
//=============================================================================
D3DXVECTOR3 GetRotationDestModel(void)
{
	return RotDestModel;
}
