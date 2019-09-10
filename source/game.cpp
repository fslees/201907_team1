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
#include "ratingmanager.h"
#include "inputmanager.h"
#include "lane.h"
#include "score.h"
#include "result.h"
#include "input.h"
#include "scene.h"
#include "hitline.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
static const D3DXVECTOR3 INIT_POS_CAMERA = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
static const D3DXVECTOR3 INIT_POS_AT = D3DXVECTOR3(0.0f, 0.0f, 200.0f);

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
RatingManager	*rating;

//*****************************************************************************
// �Q�[���̏�����
//*****************************************************************************
void InitGame()
{
	// �J�����̏�����
	InitCamera();

	// ���C�g�̏�����
	InitLight();

	// ���[���̏�����
	lane = new Lane;

	// �m�[�c�̏�����
	note = new NoteManager;

	// bms�̏�����
	bms = new BmsManager;

	// �X�R�A�̏�����
	score = new Score;
  
	hitLine = new HitLine;

	rating = new RatingManager;
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

	// note�̏I��
	delete lane;

	delete note;

	delete bms;

	delete score;
	
	delete hitLine;

	delete rating;
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

	// ���ʃf�[�^�̍X�V
	bms->Update();
	bms->CheckSetCount(note);

	// �m�[�c�̍X�V
	note->Update();

	// �����O�m�[�c�̍X�V

	// �����O�m�[�c�̐ݒu
	if (note->longNote)
	{
		// �����O�m�[�c�̃Z�b�g 
	}

	score->UpdateScore();

	rating->SetRaitng(note->note->delRating);

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

	// ���胉�C���̕`��
	hitLine->Draw();

	lane->Draw();

	// �m�[�c�̕`��
	note->Draw();

	score->DrawScore();

	rating->Draw();
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
