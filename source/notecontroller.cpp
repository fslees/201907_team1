//======================================
// �m�[�c�̏���[note.cpp]
// Author : ����@�W��
//======================================
#include "notecontroller.h"
#include "notemanager.h"
#include "note.h"
#include "inputmanager.h"
#include "rating.h"

//======================================
//�}�N����`
//======================================
#define NOTE_DELETE_POS		(100)

//======================================
//�R���X�g���N�^
//======================================
NoteController::NoteController()
{

}

//=====================================
//�f�X�g���N�^
//=====================================
NoteController::~NoteController()
{

}

//=====================================
//�X�V����
//=====================================
void NoteController::Update()
{
	// �m�[�c�̑���
	InputNote();

	// ���W���ړ�
	note->pos.z -= note->move;

	// ���W�����x�𒴂���ƃf���[�g
	if (note->pos.z < -NOTE_DELETE_POS)
	{
		note->use = false;
	}
}

//================================================
//�ʏ�m�[�c�̓����蔻��
//��P�����FNote *note(�Ώۃm�[�c�̃A�h���X)
//��Q�����FD3DXVECTOR3 linePos(���[���̒��S���W)
//�߂�l�@�F�Ȃ�
//================================================
void NoteController::InputNote()
{
	// �����[���̑���
	if (GetInput(HIT_LEFT_LANE))
	{
		CheckHit(note, D3DXVECTOR3(-NOTE_SET_POS_X, NOTE_SET_POS_Y, NOTE_SET_POS_Z));
	}
	// �������[���̑���
	if (GetInput(HIT_CENTER_LANE))
	{
		CheckHit(note, D3DXVECTOR3(0, NOTE_SET_POS_Y, NOTE_SET_POS_Z));
	}
	// �E���[���̑���
	if (GetInput(HIT_RIGHT_LANE))
	{
		CheckHit(note, D3DXVECTOR3(NOTE_SET_POS_X, NOTE_SET_POS_Y, NOTE_SET_POS_Z));
	}
}

//================================================
//�ʏ�m�[�c�̓����蔻��
//��P�����FNote *note(�Ώۃm�[�c�̃A�h���X)
//��Q�����FD3DXVECTOR3 linePos(���[���̒��S���W)
//�߂�l�@�F�Ȃ�
//================================================
void NoteController::CheckHit(Note *note, D3DXVECTOR3 linePos)
{
	D3DXVECTOR3 pos = note->GetPos();

	// X���Ń��[���𔻒�,Z���W�Ő����p�^�[���̔���
	if (pos.x == linePos.x && pos.z <= 10 && pos.z >= 0)
	{	//�p�[�t�F�N�g
		note->use = false;
		SetRatingTex(PERFECT);
	}
	else if (pos.x == linePos.x && pos.z <= 30 && pos.z >= -10)
	{	//�O���[�g
		note->use = false;
		SetRatingTex(GREAT);
	}
	else if (pos.x == linePos.x && pos.z <= 50 && pos.z >= -15)
	{	//�O�b�h
		note->use = false;
		SetRatingTex(GOOD);
	}
}