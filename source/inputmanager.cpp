//=============================================================================
//
// 入力管理プログラムの実装 [inputmanager.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "input.h"
#include "inputmanager.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************

bool GetInput(int action)
{
	switch (action)
	{
	case HIT_LEFT_LANE:
		return (GetKeyboardTrigger(DIK_A) || IsButtonTriggered(0, BUTTON_C));
	break;
	case HIT_CENTER_LANE:
		return (GetKeyboardTrigger(DIK_S) || IsButtonTriggered(0, BUTTON_X));
		break;
	case HIT_RIGHT_LANE:
		return (GetKeyboardTrigger(DIK_D) || IsButtonTriggered(0, BUTTON_B));
		break;

	case PUSH_LEFT:
		return (GetKeyboardPress(DIK_LEFT) || IsButtonPressed(0, BUTTON_LEFT));
		break;
	case PUSH_UP:
		return (GetKeyboardPress(DIK_UP) || IsButtonPressed(0, BUTTON_UP));
		break;
	case PUSH_RIGHT:
		return (GetKeyboardPress(DIK_RIGHT) || IsButtonPressed(0, BUTTON_RIGHT));
		break;

	case HIT_START:
		return (GetKeyboardTrigger(DIK_RETURN) || IsButtonTriggered(0, BUTTON_START));
		break;

	default:
		break;
	}

	return false;
}