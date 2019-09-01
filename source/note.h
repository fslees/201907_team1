//==================================================
//�@�m�[�c����[note.h]
//  Author : ����@�W��
//==================================================
#ifndef _NOTE_H_
#define _NOTE_H_

#include "main.h"
#include "noteview.h"
#include "notecontroller.h"

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
	NoteView * view;			//view�̃|�C���^�ϐ�
	NoteController *ctrl;		//controller�̃|�C���^�ϐ�
	D3DXVECTOR3 pos;			//���W(�R���X�g���N�^���Œl�̉��������j
	D3DXVECTOR3 scl;			//�傫��(�R���X�g���N�^���Œl�̉��������j
	D3DXMATRIX	mtxWorld;		//���[���h�}�g���N�X
	

private:

	//�����o�[�֐�
public:
	 Note();					//�R���X�g���N�^
	 ~Note();					//�f�X�g���N�^
	 void Update();				//�X�V�������Ă�
	 void Draw();				//�`�揈�����Ă�
	 D3DXVECTOR3 GetPos();		//pos���擾
	 D3DXVECTOR3 GetScl();		//scl���擾
	 D3DXMATRIX  GetMtxWorld();	//mtxWorld���擾


private:
};

#endif

