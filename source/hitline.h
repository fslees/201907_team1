//=============================================================================
//
// ���胉�C���w�b�_�[���� [hitline.h]
// Author : GP12A332_25_����W��
//
//=============================================================================
#ifndef _HITLINE_H_
#define _HITLINE_H_

#include "main.h"



class HitLine 
{
private:
	LPDIRECT3DTEXTURE9		D3DTexture;			// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;			// ���_�o�b�t�@�ւ̃|�C���^
	D3DXVECTOR3				pos;				// ���W
	D3DXVECTOR3				rot;				// ��]
	D3DXVECTOR3				scl;				// �傫���̔{��
	D3DXMATRIX				mtxWorld;			// ���[���h�}�g���b�N�X

public:
	HitLine();
	~HitLine();
	void Update();
	void Draw();
	HRESULT MakeVertexHitLine(LPDIRECT3DDEVICE9 pDevice);

};

#endif

