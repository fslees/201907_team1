//==================================================
//�@�m�[�c����[note.h]
//  Author : ����@�W��
//==================================================
#ifndef _NOTE_H_
#define _NOTE_H_

#include "noteview.h"
#include "notecontroller.h"
#include "main.h"

//==================================================
//�}�N����`
//==================================================

//==================================================
//�N���X��`
//==================================================
class Note
{
	//�����o�[�ϐ�
public:
	NoteView * view;		//view�̃|�C���^�ϐ�
	NoteController *ctrl;	//controller�̃|�C���^�ϐ�
	D3DXVECTOR3 pos;

private:

	//�����o�[�֐�
public:
	 Note();				//�R���X�g���N�^
	 ~Note();				//�f�X�g���N�^
	 void Update();			//�X�V�������Ă�
	 void Draw();			//�`�揈�����Ă�


private:
};


#endif

