//=============================================================================
//
// �J�������� [camera.h]
// Author : �����~��
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//=============================================================================
// �J�����f�[�^�N���X�̒�`
// posEye			: �J�����̈ʒu
// posAT			: �J�����̒����_
//=============================================================================
struct CameraData
{
	D3DXVECTOR3		posEye;
	D3DXVECTOR3		posAT;
};


//=============================================================================
// �J�����N���X�̒�`
//=============================================================================
class Camera
{
private:
	D3DXVECTOR3		posEye;				// �J�����̎��_
	D3DXVECTOR3		posAT;				// �J�����̒����_
	D3DXVECTOR3		vecUp;				// �J�����̏����
	D3DXVECTOR3		rot;				// �J�����̉�]
	float			lengthInterval;		// �J�����̎��_�ƒ����_�̋���
	D3DXMATRIX		mtxView;			// �r���[�}�g���b�N�X
	D3DXMATRIX		mtxProjection;		// �v���W�F�N�V�����}�g���b�N�X

public:
	Camera(CameraData initData);

	void Update(void);
	void Set(void);

	D3DXVECTOR3	GetPosEye();
	D3DXMATRIX	GetMtxView();
	D3DXMATRIX	GetMtxProjection();
};


#endif
