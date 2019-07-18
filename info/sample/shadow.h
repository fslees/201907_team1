//=============================================================================
//
// 影処理 [shadow.h]
// Author : 
//
//=============================================================================
#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "main.h"

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitShadow(void);
void UninitShadow(void);
void UpdateShadow(void);
void DrawShadow(void);

int	CreateShadow(D3DXVECTOR3 pos, float sizeX, float sizeZ);
void ReleaseShadow(int idxShadow);
void SetPositionShadow(int idxShadow, D3DXVECTOR3 pos);
void SetVertexShadow(int idxShadow, float sizeX, float sizeZ);
void SetColorShadow(int idxShadow, D3DXCOLOR col);

#endif
