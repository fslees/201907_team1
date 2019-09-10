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
#include "rating.h"
#include "inputmanager.h"
#include "lane.h"
#include "score.h"
#include "result.h"
#include "input.h"
#include "scene.h"
#include "hitline.h"
#include "cutter.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
static const D3DXVECTOR3 INIT_POS_CAMERA = D3DXVECTOR3(0.0f, 100.0f, -110.0f);
static const D3DXVECTOR3 INIT_POS_AT = D3DXVECTOR3(0.0f, 50.0f, 200.0f);

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

	// 判定評価の初期化
	InitRating();

	// レーンの初期化
	lane = new Lane;

	// ノーツの初期化
	note = new NoteManager;

	// bmsの初期化
	bms = new BmsManager;

	// スコアの初期化
	score = new Score;
  
	// 判定ライン初期化
	hitLine = new HitLine;

	// カッターの初期化
	InitCutter(hitLine->GetPos());

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


	// 判定評価の終了処理
	UninitRating();

	// レーンの終了
	delete lane;
	// ノーツの終了
	delete note;
	// 譜面の終了
	delete bms;
	// スコアの終了
	delete score;
	// 判定ラインの終了
	delete hitLine;
	// カッターの終了
	UninitCutter();

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

	// ロングノーツの更新

	// ロングノーツの設置
	if (note->longNote)
	{
		// ロングノーツのセット 
	}

	// 判定評価の更新
	UpdateRating();

	// スコアの更新
	score->UpdateScore();

	// カッターの更新
	UpdateCutter();


#ifdef _DEBUG

	//ゲーム遷移
	if (GetKeyboardTrigger(DIK_1))
	{
		SetScene(SCENE_RESULT);
	}

#endif 
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

	// ノーツの描画
	note->Draw();


	// 判定評価の描画
	DrawRating();

	// カッターの描画
	DrawCutter();

	// スコアの描画
	score->DrawScore();

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

//*****************************************************************************
// カメラのビュー行列取得
//*****************************************************************************
D3DXMATRIX GetMtxGameView()
{
	return camera->GetMtxView();
}
