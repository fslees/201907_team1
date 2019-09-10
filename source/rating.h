//=============================================================================
//
// �q�b�g���̐��x�\���̒�` [hitqualety.h]
// Author : �����~��
//
//=============================================================================
#ifndef _RATING_H_
#define _RATING_H_

#include "main.h"
#include "camera.h"

//=================================
// �}�N����`
//=================================
enum RATING_TEX
{
	PERFECT,
	GREAT,
	GOOD,
	TEX_MAX,
};

class Rating
{
private:
	Camera					camera;

	LPDIRECT3DTEXTURE9		texture[TEX_MAX] = { NULL,NULL, NULL };	//�e�N�X�`���ւ̃|�C���^
	VERTEX_2D				vertex[NUM_VERTEX];		// ���_���i�[���[�N
	D3DXMATRIX				mtxWorld;

public:
	int						texNum;					// �e�N�X�`���[�̔ԍ�
	bool					use;					// �g�p���
	//������
	Rating();
	//�I������
	~Rating();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	//���_�̍쐬
	void MakeVertex();

};
#endif
