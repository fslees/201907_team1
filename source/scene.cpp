//=============================================================================
//
// シーンの処理 [scene.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "scene.h"
#include "game.h"
#include "result.h"
#include "title.h"
#include "tutorial.h"
#include "resultscore.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define NAME_INIT_SCENE (SCENE_GAME)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
static int SceneState = NAME_INIT_SCENE;
Resultscore  *resultscore;


//*****************************************************************************
// 初期化
//*****************************************************************************
void InitScene()
{
	switch (SceneState)
	{
	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_TUTORIAL:
		InitTutorial();
		break;

	case SCENE_GAME:
		InitGame();
		break;

	case SCENE_RESULT:
		InitResult();
		resultscore = new Resultscore;
		break;
	
	default:
		break;
	}
}

//*****************************************************************************
// 終了
//*****************************************************************************
void UninitScene()
{
	switch (SceneState)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_TUTORIAL:
		UninitTutorial();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		//result.UninitResult();
		UninitResult();
		delete resultscore;
		break;

	default:

		break;
	}
}

//*****************************************************************************
// 更新
//*****************************************************************************
void UpdateScene()
{
	switch (SceneState)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_TUTORIAL:
		UpdateTutorial();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_RESULT:
		UpdateResult();
		resultscore->UpdateResultScore();
		break;

	default:
		break;
	}
}

//*****************************************************************************
// 画面の描画
//*****************************************************************************
void DrawScene()
{
	switch (SceneState)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_TUTORIAL:
		DrawTutorial();
		break;

	case SCENE_GAME:
		DrawGame();
		break;

	case SCENE_RESULT:
		DrawResult();
		resultscore->DrawResultScore();
		break;

	default:
		break;
	}
}


//*****************************************************************************
// シーン遷移処理
//*****************************************************************************
void SetScene(int noScene)
{
	// 現在のシーンを終了する
	UninitScene();

	// シーンを変更
	SceneState = noScene;

	// 新しいシーンを初期化
	InitScene();
}

