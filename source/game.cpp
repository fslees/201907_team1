//=============================================================================
//
// �Q�[���̏��� [game.cpp]
// Author : �����~��
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "notemanager.h"
#include "bmsmanager.h"
#include "rating.h"
#include "inputmanager.h"
#include "lane.h"
#include "score.h"
#include "result.h"
#include "input.h"
#include "scene.h"
#include "hitline.h"
#include "cutter.h"
#include "star.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
static const D3DXVECTOR3 INIT_POS_CAMERA = D3DXVECTOR3(0.0f, 100.0f, -110.0f);
static const D3DXVECTOR3 INIT_POS_AT = D3DXVECTOR3(0.0f, 50.0f, 200.0f);

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
void InitCamera();

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static Camera	*camera;
BmsManager		*bms;
Lane			*lane;
NoteManager		*note;
Score           *score;
HitLine			*hitLine;

//*****************************************************************************
// �Q�[���̏�����
//*****************************************************************************
void InitGame()
{
	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	// ����]���̏�����
	InitRating();

	// ���[���̏�����
	lane = new Lane;

	// �m�[�c�̏�����
	note = new NoteManager;

	// bms�̏�����
	bms = new BmsManager;

	// �X�R�A�̏�����
	score = new Score;
  
	// ���胉�C��������
	hitLine = new HitLine;

	// �J�b�^�[�̏�����
	InitCutter(hitLine->GetPos());

	// �����O�m�[�c�̏�����	
	InitStar();

}

//*****************************************************************************
// �Q�[���̏I��
//*****************************************************************************
void UninitGame()
{
	// �J�����̉��
	delete camera;

	// ���C�g�̏I��
	UninitLight();


	// ����]���̏I������
	UninitRating();

	// ���[���̏I��
	delete lane;
	// �m�[�c�̏I��
	delete note;
	// ���ʂ̏I��
	delete bms;
	// �X�R�A�̏I��
	delete score;
	// ���胉�C���̏I��
	delete hitLine;
	// �J�b�^�[�̏I��
	UninitCutter();

	// �����O�m�[�c�̏I��
	UninitStar();

}



//*****************************************************************************
// �Q�[���̍X�V
//*****************************************************************************
void UpdateGame()
{
	// �J�����̍X�V
	camera->Update();

	// ���C�g�̍X�V
	UpdateLight();


	// �m�[�c�̍X�V
	note->Update();

	// �����O�m�[�c�̍X�V


	// ����]���̍X�V
	UpdateRating();

	// �X�R�A�̍X�V
	score->UpdateScore();

	// �J�b�^�[�̍X�V
	UpdateCutter();

	// �����O�m�[�c�̍X�V
	UpdateStar();

	// ���ʃf�[�^�̍X�V
	bms->Update(note);
	// �����O�m�[�c�̐ݒu
	if (note->longNote)
	{
		// �����O�m�[�c�̃Z�b�g 
		SetLongNote(-5.0f);
	}

#ifdef _DEBUG

	//�Q�[���J��
	if (GetKeyboardTrigger(DIK_1))
	{
		SetScene(SCENE_RESULT);
	}

#endif 
}

//*****************************************************************************
// �Q�[����ʂ̕`��
//*****************************************************************************
void DrawGame()
{
	// �J�����̃Z�b�g
	camera->Set();

	// ���[���̕`��
	lane->Draw();

	// �m�[�c�̕`��
	note->Draw();

	// ���胉�C���̕`��
	hitLine->Draw();

	// ����]���̕`��
	DrawRating();

	// �����O�m�[�c�̕`��
	DrawStar();

	// �J�b�^�[�̕`��
	DrawCutter();

	// �X�R�A�̕`��
	score->DrawScore();

}


//*****************************************************************************
// �J�����̏�����
//*****************************************************************************
void InitCamera()
{
	CameraData InitData;
	InitData.posEye = INIT_POS_CAMERA;
	InitData.posAT = INIT_POS_AT;

	camera = new Camera(InitData);
}

//*****************************************************************************
// �J�����̃r���[�s��擾
//*****************************************************************************
D3DXMATRIX GetMtxGameView()
{
	return camera->GetMtxView();
}

//*****************************************************************************
// �J�����̈ʒu����
//*****************************************************************************
D3DXVECTOR3	GetGameCameraPos()
{
	return camera->GetPosEye();
}

//*****************************************************************************
// �J�����̈ʒu����
//*****************************************************************************
D3DXVECTOR3	GetGameHitLinePos()
{
	return hitLine->GetPos();
}
