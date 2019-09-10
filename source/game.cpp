//=============================================================================
//
// $B%2!<%`$N=hM}(B [game.cpp]
// Author : $BM{>0%_%s(B
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
// $B%^%/%mDj5A(B
//*****************************************************************************
static const D3DXVECTOR3 INIT_POS_CAMERA = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
static const D3DXVECTOR3 INIT_POS_AT = D3DXVECTOR3(0.0f, 0.0f, 200.0f);

//*****************************************************************************
// $B%W%m%H%?%$%W@k8@(B
//*****************************************************************************
void InitCamera();

//*****************************************************************************
// $B%0%m!<%P%kJQ?t(B
//*****************************************************************************
static Camera	*camera;
BmsManager		*bms;
Lane			*lane;
NoteManager		*note;
Score           *score;
HitLine			*hitLine;
RatingManager	*rating;

//*****************************************************************************
// $B%2!<%`$N=i4|2=(B
//*****************************************************************************
void InitGame()
{
	// $B%+%a%i$N=i4|2=(B
	InitCamera();

	// $B%i%$%H$N=i4|2=(B
	InitLight();

	// $B%l!<%s$N=i4|2=(B
	lane = new Lane;

	// $B%N!<%D$N=i4|2=(B
	note = new NoteManager;

	// bms$B$N=i4|2=(B
	bms = new BmsManager;

	// $B%9%3%"$N=i4|2=(B
	score = new Score;
  
	hitLine = new HitLine;

	rating = new RatingManager;
}

//*****************************************************************************
// $B%2!<%`$N=*N;(B
//*****************************************************************************
void UninitGame()
{
	// $B%+%a%i$N2rJ|(B
	delete camera;

	// $B%i%$%H$N=*N;(B
	UninitLight();

	// note$B$N=*N;(B
	delete lane;

	delete note;

	delete bms;

	delete score;
	
	delete hitLine;

	delete rating;
}



//*****************************************************************************
// $B%2!<%`$N99?7(B
//*****************************************************************************
void UpdateGame()
{
	// $B%+%a%i$N99?7(B
	camera->Update();

	// $B%i%$%H$N99?7(B
	UpdateLight();

	// $BIhLL%G!<%?$N99?7(B
	bms->Update();
	bms->CheckSetCount(note);

	// $B%N!<%D$N99?7(B
	note->Update();

	// $B%m%s%0%N!<%D$N99?7(B

	// $B%m%s%0%N!<%D$N@_CV(B
	if (note->longNote)
	{
		// $B%m%s%0%N!<%D$N%;%C%H(B 
	}

	score->UpdateScore();

	rating->SetRaitng(note->note->delRating);

#ifdef _DEBUG

	//$B%2!<%`A+0\(B
	if (GetKeyboardTrigger(DIK_1))
	{
		SetScene(SCENE_RESULT);
	}

#endif 
}

//*****************************************************************************
// $B%2!<%`2hLL$NIA2h(B
//*****************************************************************************
void DrawGame()
{
	// $B%+%a%i$N%;%C%H(B
	camera->Set();
	
	// $B%l!<%s$NIA2h(B
	lane->Draw();

	// $BH=Dj%i%$%s$NIA2h(B
	hitLine->Draw();

	lane->Draw();

	// $B%N!<%D$NIA2h(B
	note->Draw();

	score->DrawScore();

	rating->Draw();
}


//*****************************************************************************
// $B%+%a%i$N=i4|2=(B
//*****************************************************************************
void InitCamera()
{
	CameraData InitData;
	InitData.posEye = INIT_POS_CAMERA;
	InitData.posAT = INIT_POS_AT;

	camera = new Camera(InitData);
}
