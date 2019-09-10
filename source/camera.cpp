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

//=============================================================================
// �J�����̏�����(����錾)
//=============================================================================
Camera::Camera()
{
}

//=============================================================================
// �J�����̏�����
//=============================================================================
Camera::Camera(CameraData initData)
{
	posEye = initData.posEye;
	posAT = initData.posAT;
	vecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx, vz;
	vx = posEye.x - posAT.x;
	vz = posEye.z - posAT.z;
	lengthInterval = sqrtf(vx * vx + vz * vz);
}

//=============================================================================
// �J�����̍X�V����
//=============================================================================
void Camera::Update()
{

}

//=============================================================================
// �J�����̐ݒ菈��
//=============================================================================
void Camera::Set(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(&mtxView,
		&posEye,		// �J�����̎��_
		&posAT,		// �J�����̒����_
		&vecUp);		// �J�����̏����

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

//*****************************************************************************
// �J�������_�̃Q�b�g�֐�
//*****************************************************************************
D3DXVECTOR3 Camera::GetPosEye()
{
	return posEye;
}

//*****************************************************************************
// �r���[�s��̃Q�b�g�֐�
//*****************************************************************************
D3DXMATRIX Camera::GetMtxView()
{
	return mtxView;
}

//*****************************************************************************
// �v���W�F�N�V�����s��̃Q�b�g�֐�
//*****************************************************************************
D3DXMATRIX Camera::GetMtxProjection()
{
	return mtxProjection;
}