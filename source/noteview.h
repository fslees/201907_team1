//==================================================
//�@�m�[�c�`�揈��[noteview.h]
//  Author : ����@�W��
//==================================================
#ifndef _NOTEVIEW_H_
#define _NOTEVIEW_H_

class Note;					
#include "main.h"


//==================================================
//�}�N����`
//==================================================
#define NOTE_MODEL		"data/MODEL/airplane000.x"


//==================================================
//�N���X��`
//==================================================
class NoteView
{
	//�����o�[�ϐ�
public:
	Note * note;		//�m�[�c�̃|�C���^�ϐ�

private:
	
	D3DXVECTOR3 pos;							//�ʒu
	D3DXVECTOR3 scl;							//�傫��
	D3DXMATRIX  mtxWorld ;						//���[���h�}�g���N�X

	//�����o�[�֐�
public:
	NoteView();			//�R���X�g���N�^�E���f���̓ǂݍ��݂Ə�����
	~NoteView();		//�f�X�g���N�^�E�I������
	void Draw();		//�`�揈��
	


private:
};


#endif

