//========================================
// 2D�̃e�N�X�`���쐬[2Dtexmanager]
//  Author : ����@�W��
//========================================
#include "2Dtexmanager.h"
#include "main.h"

//========================================
// �`�揈��
// �����P[�e�N�X�`���ւ̃|�C���^]
// �����Q[���_���]
//========================================
void Texmanager::Draw(LPDIRECT3DTEXTURE9 p, VERTEX_2D vertex[NUM_VERTEX])
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, p);

	// �|���S���̕`��
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertex, sizeof(VERTEX_2D));

}

//============================================
// ���_�쐬
// �����F���_���i�[���[�N
//============================================
void Texmanager::MakeVertex(VERTEX_2D vertex[NUM_VERTEX])
{
	// ���_���W�̐ݒ�
	vertex[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	vertex[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	vertex[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// �e�N�X�`���̃p�[�X�y�N�e�B�u�R���N�g�p
	vertex[0].rhw =
		vertex[1].rhw =
		vertex[2].rhw =
		vertex[3].rhw = 1.0f;

	// ���ˌ��̐ݒ�
	vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// �e�N�X�`�����W�̐ݒ�
	vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

}