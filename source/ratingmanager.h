//=============================================================================
//
// �q�b�g���̐��x�\���̊Ǘ� [hitqualetymanager.h]
// Author : GP12A_332_26_�c�����z
//
//=============================================================================
#ifndef _RATINGMANAGER_H_
#define _RATINGMANAGER_H_

#include "main.h"
#include "rating.h"


//=================================
// �N���X�錾
//=================================
class RatingManager
{
private:
	Rating	*rating;
public:
	//������
	RatingManager();
	//�I������
	~RatingManager();
	//�X�V����
	void Update();
	//�`�揈��
	void Draw();
	// ���x�]���̐ݒu
	void SetRaitng(int texNum);

};
#endif
