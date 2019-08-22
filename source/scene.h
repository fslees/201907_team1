//=============================================================================
//
// シーンの処理 [scene.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _SCENE_H_
#define _SCENE_H_

#include "main.h"

typedef enum
{
	SCENE_GAME,
	SCENE_MAX
}NameScene;

//
void InitScene();
//
void UninitScene();
//
void UpdateScene();
//
void DrawScene();

// シーン遷移の処理
// noScene : 遷移するシーンの番号
void SetScene(int noScene);


#endif