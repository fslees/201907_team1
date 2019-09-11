//=============================================================================
//
// ÉQÅ[ÉÄÇÃèàóù [game.h]
// Author : óõèÆÉ~Éì
//
//=============================================================================
#ifndef _GAME_H_
#define _GAME_H_

#include "main.h"

//
void InitGame();
//
void UninitGame();
//
void UpdateGame();
//
void DrawGame();

D3DXMATRIX GetMtxGameView();

D3DXVECTOR3	GetGameCameraPos();

D3DXVECTOR3	GetGameHitLinePos();

#endif