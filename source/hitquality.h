//=============================================================================
//
// �q�b�g���̐��x�\���̒�` [hitqualety.h]
// Author : �����~��
//
//=============================================================================
#ifndef _HITQUALITY_H_
#define _HITQUALITY_H_

#include "main.h"
#include "camera.h"

//=================================
// �}�N����`
//=================================
enum HitQUALETY_TEX
{
	PERFECT,
	GREAT,
	GOOD,
	TEX_MAX,
};

class HitQualety
{
private:
	Camera					camera;

	LPDIRECT3DTEXTURE9		D3DTexture[TEX_MAX] = { NULL,NULL, NULL };	//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;		// ���_�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^
	VERTEX_3D				vertex[NUM_VERTEX];		// ���_���i�[���[�N
	D3DXMATRIX				mtxWorld;
	D3DXVECTOR3				pos;					// ���W
	D3DXVECTOR3				rot;					// ��]��
	D3DXVECTOR3				scl;					// �傫��
	bool					use;					// �g�p���
	int						texNum;					// �e�N�X�`���[�̔ԍ�

public:
	//������
	HitQualety();
	//�I������
	~HitQualety();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//���_�̍쐬
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	// �g��A�j���[�V����
	void SetSclAnim();

};
#endif
