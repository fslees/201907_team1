//======================================
// �m�[�c�̏���[note.cpp]
// Author : ����@�W��
//======================================
#include "note.h"


//=====================================
//�R���X�g���N�^
//=====================================
Note::Note()
{
	ctrl = new NoteController();
	view = new NoteView();

	ctrl->note = this;
	view->note = this;
}