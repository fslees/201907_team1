//=============================================================================
//
// �V�[���̏��� [scene.h]
// Author : �����~��
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

// �V�[���J�ڂ̏���
// noScene : �J�ڂ���V�[���̔ԍ�
void SetScene(int noScene);


#endif