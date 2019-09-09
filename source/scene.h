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
	SCENE_TITLE,
	SCENE_TUTORIAL,
	SCENE_GAME,
	SCENE_RESULT,
	SCENE_MAX
}NameScene;

// �V�[���̏�����
void InitScene();
// �V�[���̏I��
void UninitScene();
// �V�[���̍X�V
void UpdateScene();
// �V�[���̕`��
void DrawScene();

// �V�[���J�ڂ̏���
// noScene : �J�ڂ���V�[���̔ԍ�
void SetScene(int noScene);


#endif