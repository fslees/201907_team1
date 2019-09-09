//=============================================================================
//
// �V�[���̏��� [scene.cpp]
// Author : �����~��
//
//=============================================================================
#include "scene.h"
#include "game.h"
#include "result.h"
#include "title.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define NAME_INIT_SCENE (SCENE_TITLE)

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************


//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
static int SceneState;



//*****************************************************************************
// ������
//*****************************************************************************
void InitScene()
{
	
	SceneState = NAME_INIT_SCENE;

	switch (SceneState)
	{
	case SCENE_TITLE:
		InitTitle();
		break;

	case SCENE_GAME:
		InitGame();
		break;

	case SCENE_RESULT:
		InitResult();
		break;
	
	default:
		break;
	}

}

//*****************************************************************************
// �I��
//*****************************************************************************
void UninitScene()
{
	switch (SceneState)
	{
	case SCENE_TITLE:
		UninitTitle();
		break;

	case SCENE_GAME:
		UninitGame();
		break;

	case SCENE_RESULT:
		//result.UninitResult();
		UninitResult();
		break;

	default:

		break;
	}

}

//*****************************************************************************
// �X�V
//*****************************************************************************
void UpdateScene()
{
	switch (SceneState)
	{
	case SCENE_TITLE:
		UpdateTitle();
		break;

	case SCENE_GAME:
		UpdateGame();
		break;

	case SCENE_RESULT:
		UpdateResult();
		break;

	default:
		break;
	}


}

//*****************************************************************************
// ��ʂ̕`��
//*****************************************************************************
void DrawScene()
{
	switch (SceneState)
	{
	case SCENE_TITLE:
		DrawTitle();
		break;

	case SCENE_GAME:
		DrawGame();
		break;

	case SCENE_RESULT:
		DrawResult();
		break;

	default:
		break;
	}

}


//*****************************************************************************
// �V�[���J�ڏ���
//*****************************************************************************
void SetScene(int noScene)
{
	// ���݂̃V�[�����I������
	UninitScene();

	// �V�[����ύX
	SceneState = noScene;

	// �V�����V�[����������
	InitScene();
}

