//=============================================================================
//
// �J�b�^�[�̒�` [field.h]
// Author : �����~��
//
//=============================================================================
#ifndef _CUTTER_H_
#define _CUTTER_H_

#include "main.h"

typedef struct
{
	D3DXVECTOR3 vtx[4];
	D3DXVECTOR3 nor;
}PLANE;

typedef struct
{
	D3DXVECTOR3 vtx[3];
}TRIANGLE;

struct LINE
{
	D3DXVECTOR3 vtx[2];
};


//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitCutter(D3DXVECTOR3 pos);
void UninitCutter(void);
void UpdateCutter(void);
void DrawCutter(void);

//LINE GetCutterLine(void);
PLANE GetCutterState(void);
D3DXVECTOR3 GetCutterPos(void);

/*			
if (star[i].block[j].pos.z < GetCutterPos().z)
{
	ClippingStar(GetCutterState());
	continue;
}

if (GetKeyboardTrigger(DIK_C))
{
SetStar(D3DXVECTOR3(0.0f, 100.0f, 100.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f));
}

*/
#endif
