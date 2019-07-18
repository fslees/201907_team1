//=============================================================================
//
// �J�������� [camera.cpp]
// Author : �����~��
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// ����p
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// �r���[���ʂ̃A�X�y�N�g��
#define	VIEW_NEAR_Z			(10.0f)					// �r���[���ʂ�NearZ�l
#define	VIEW_FAR_Z			(1000.0f)				// �r���[���ʂ�FarZ�l
#define	VALUE_MOVE_CAMERA	(2.0f)					// �J�����̈ړ���
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// �J�����̉�]��

#define	INTERVAL_CAMERA_R	(12.5f)					// ���f���̎����̐�܂ł̋���
#define	RATE_CHASE_CAMERA_P	(0.35f)					// �J�����̎��_�ւ̕␳�W��
#define	RATE_CHASE_CAMERA_R	(0.20f)					// �J�����̒����_�ւ̕␳�W��

#define	CHASE_HEIGHT_P		(100.0f)				// �ǐՎ��̎��_�̍���
#define	CHASE_HEIGHT_R		(10.0f)					// �ǐՎ��̒����_�̍���

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
D3DXVECTOR3		posCameraEye;				// �J�����̎��_
D3DXVECTOR3		posCameraAT;				// �J�����̒����_
D3DXVECTOR3		posCameraUp;				// �J�����̏����
D3DXVECTOR3		posCameraEyeDest;			// �J�����̎��_�̖ړI�ʒu
D3DXVECTOR3		posCameraATDest;			// �J�����̒����_�̖ړI�ʒu
D3DXVECTOR3		rotCamera;					// �J�����̉�]
float			lengthIntervalCamera;		// �J�����̎��_�ƒ����_�̋���
D3DXMATRIX		mtxView;					// �r���[�}�g���b�N�X
D3DXMATRIX		mtxProjection;				// �v���W�F�N�V�����}�g���b�N�X

//=============================================================================
// �J�����̏�����
//=============================================================================
HRESULT InitCamera(void)
{
	posCameraEye = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	posCameraAT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	posCameraEyeDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	posCameraATDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx,vz;
	vx = posCameraEye.x - posCameraAT.x;
	vz = posCameraEye.z - posCameraAT.z;
	lengthIntervalCamera = sqrtf(vx * vx + vz * vz);

	return S_OK;
}

//=============================================================================
// �J�����̏I������
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void UpdateCamera(void)
{
	if(GetKeyboardPress(DIK_A))
	{
		if(GetKeyboardPress(DIK_W))
		{// ���O�ړ�
			posCameraEye.x -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			posCameraEye.z += sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else if(GetKeyboardPress(DIK_S))
		{// ����ړ�
			posCameraEye.x -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			posCameraEye.z += sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else
		{// ���ړ�
			posCameraEye.x -= cosf(rotCamera.y) * VALUE_MOVE_CAMERA;
			posCameraEye.z += sinf(rotCamera.y) * VALUE_MOVE_CAMERA;
		}

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_D))
	{
		if(GetKeyboardPress(DIK_W))
		{// �E�O�ړ�
			posCameraEye.x += cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			posCameraEye.z -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else if(GetKeyboardPress(DIK_S))
		{// �E��ړ�
			posCameraEye.x += cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			posCameraEye.z -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else
		{// �E�ړ�
			posCameraEye.x += cosf(rotCamera.y) * VALUE_MOVE_CAMERA;
			posCameraEye.z -= sinf(rotCamera.y) * VALUE_MOVE_CAMERA;
		}

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_W))
	{// �O�ړ�
		posCameraEye.x += sinf(rotCamera.y) * VALUE_MOVE_CAMERA;
		posCameraEye.z += cosf(rotCamera.y) * VALUE_MOVE_CAMERA;

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_S))
	{// ��ړ�
		posCameraEye.x -= sinf(rotCamera.y) * VALUE_MOVE_CAMERA;
		posCameraEye.z -= cosf(rotCamera.y) * VALUE_MOVE_CAMERA;

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}

	if(GetKeyboardPress(DIK_Z))
	{// ���_����u���v
		rotCamera.y += VALUE_ROTATE_CAMERA;
		if(rotCamera.y > D3DX_PI)
		{
			rotCamera.y -= D3DX_PI * 2.0f;
		}

		posCameraEye.x = posCameraAT.x - sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraEye.z = posCameraAT.z - cosf(rotCamera.y) * lengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_C))
	{// ���_����u�E�v
		rotCamera.y -= VALUE_ROTATE_CAMERA;
		if(rotCamera.y < -D3DX_PI)
		{
			rotCamera.y += D3DX_PI * 2.0f;
		}

		posCameraEye.x = posCameraAT.x - sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraEye.z = posCameraAT.z - cosf(rotCamera.y) * lengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_Y))
	{// ���_�ړ��u��v
		posCameraEye.y += VALUE_MOVE_CAMERA;
	}
	if(GetKeyboardPress(DIK_N))
	{// ���_�ړ��u���v
		posCameraEye.y -= VALUE_MOVE_CAMERA;
	}

	if(GetKeyboardPress(DIK_Q))
	{// �����_����u���v
		rotCamera.y -= VALUE_ROTATE_CAMERA;
		if(rotCamera.y < -D3DX_PI)
		{
			rotCamera.y += D3DX_PI*2.0f;
		}

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_E))
	{// �����_����u�E�v
		rotCamera.y += VALUE_ROTATE_CAMERA;
		if(rotCamera.y > D3DX_PI)
		{
			rotCamera.y -= D3DX_PI*2.0f;
		}

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_T))
	{// �����_�ړ��u��v
		posCameraAT.y += VALUE_MOVE_CAMERA;
	}
	if(GetKeyboardPress(DIK_B))
	{// �����_�ړ��u���v
		posCameraAT.y -= VALUE_MOVE_CAMERA;
	}

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView, 
						&posCameraEye,		// �J�����̎��_
						&posCameraAT,		// �J�����̒����_
						&posCameraUp);		// �J�����̏����

	// �r���[�}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_VIEW, &mtxView);


	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
								VIEW_ANGLE,			// ����p
								VIEW_ASPECT,		// �A�X�y�N�g��
								VIEW_NEAR_Z,		// �r���[���ʂ�NearZ�l
								VIEW_FAR_Z);		// �r���[���ʂ�FarZ�l

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	device->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//=============================================================================
// �J�����̌����̎擾
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return rotCamera;
}

//=============================================================================
// �r���[�}�g���b�N�X�̎擾
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return mtxView;
}

