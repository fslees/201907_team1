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
	SCENE_TITLE,
	SCENE_TUTORIAL,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_MAX
}NameScene;

// シーンの初期化
void InitScene();
// シーンの終了
void UninitScene();
// シーンの更新
void UpdateScene();
// シーンの描画
void DrawScene();

// シーン遷移の処理
// noScene : 遷移するシーンの番号
void SetScene(int noScene);


#endif