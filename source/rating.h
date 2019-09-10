//=============================================================================
//
// �q�b�g���̐��x�\���̒�` [hitqualety.h]
// Author : �����~��
//
//=============================================================================
#ifndef _RATING_H_
#define _RATING_H_

#include "main.h"

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

//=================================
// �\���̐錾
//=================================
struct Rating
{
	int			texNum;					// �e�N�X�`���[�̔ԍ�
	bool		use;					// �g�p���
	int			frameCnt;
};

//=================================
// �v���g�^�C�v�錾
//=================================
//������
HRESULT InitRating();
//�I������
void UninitRating();
//�X�V����
void UpdateRating();
//�`�揈��
void DrawRating();
//����]���̐ݒu
void SetRatingTex(int texNum);

#endif
