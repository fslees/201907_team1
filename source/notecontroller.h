//==================================================
//�@�m�[�c�X�V����[notecontroller.h]
//  Author : ����@�W��
//==================================================
#ifndef _NOTECONTROLLER_H_
#define _NOTECONTROLLER_H_

class Note; 
#include "main.h"

//==================================================
//�}�N����`
//==================================================

//==================================================
//�N���X��`
//==================================================
class NoteController
{
	//�����o�[�ϐ�
public:
	Note * note;				//�m�[�c�̃|�C���^�ϐ�

private:

	//�����o�[�֐�
public:
	NoteController();			//
	~NoteController();			//
	void Update();				//
	//D3DXVECTOR3 GetNotePos();	//

private:
};


#endif

