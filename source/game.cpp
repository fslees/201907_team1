//=============================================================================
//
// ゲームの処理 [game.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "game.h"
#include "light.h"
#include "camera.h"
#include "notemanager.h"
#include "bmsmanager.h"
#include "lane.h"
#include "score.h"
#include "result.h"
#include "input.h"
#include "scene.h"
#include "hitline.h"
#include "inputmanager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
static const D3DXVECTOR3 INIT_POS_CAMERA = D3DXVECTOR3(0.0f, 100.0f, -100.0f);
static const D3DXVECTOR3 INIT_POS_AT = D3DXVECTOR3(0.0f, 0.0f, 200.0f);

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void InitCamera();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
static Camera	*camera;
BmsManager		*bms;
Lane			*lane;
NoteManager		*note;
Score           *score;
HitLine			*hitLine;

//*****************************************************************************
// ゲームの初期化
//*****************************************************************************
void InitGame()
{
	// カメラの初期化
	InitCamera();

	// ライトの初期化
	InitLight();

	// レーンの初期化
	lane = new Lane;

	// ノーツの初期化
	note = new NoteManager;

	// bmsの初期化
	bms = new BmsManager;

	// スコアの初期化
	score = new Score;
  
	hitLine = new HitLine;
}

//*****************************************************************************
// ゲームの終了
//*****************************************************************************
void UninitGame()
{
	// カメラの解放
	delete camera;

	// ライトの終了
	UninitLight();

	// noteの終了
	delete lane;

	delete note;

	delete bms;

	delete score;
	
	delete hitLine;
}



//*****************************************************************************
// ゲームの更新
//*****************************************************************************
void UpdateGame()
{
	// カメラの更新
	camera->Update();

	// ライトの更新
	UpdateLight();

	// 譜面データの更新
	bms->Update();
	bms->CheckSetCount(note);

	// ノーツの更新
	note->Update();

	lane->Update();

	score->UpdateScore();
	
	//ゲーム遷移
	if (GetKeyboardTrigger(DIK_1))
	{
		SetScene(2);
	}

}

//*****************************************************************************
// ゲーム画面の描画
//*****************************************************************************
void DrawGame()
{
	// カメラのセット
	camera->Set();
	
	// レーンの描画
	lane->Draw();

	// 判定ラインの描画
	hitLine->Draw();

	lane->Draw();

	score->DrawScore();

	// ノーツの描画
	note->Draw();
}


//*****************************************************************************
// カメラの初期化
//*****************************************************************************
void InitCamera()
{
	CameraData InitData;
	InitData.posEye = INIT_POS_CAMERA;
	InitData.posAT = INIT_POS_AT;

	camera = new Camera(InitData);
}
