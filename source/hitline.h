//=============================================================================
//
// 判定ラインヘッダー処理 [hitline.h]
// Author : GP12A332_25_染矢晃介
//
//=============================================================================
#ifndef _HITLINE_H_
#define _HITLINE_H_

#include "main.h"



class HitLine 
{
private:
	LPDIRECT3DTEXTURE9		D3DTexture;			// テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;			// 頂点バッファへのポインタ
	D3DXVECTOR3				pos;				// 座標
	D3DXVECTOR3				rot;				// 回転
	D3DXVECTOR3				scl;				// 大きさの倍率
	D3DXMATRIX				mtxWorld;			// ワールドマトリックス

public:
	HitLine();
	~HitLine();
	void Update();
	void Draw();
	HRESULT MakeVertexHitLine(LPDIRECT3DDEVICE9 pDevice);

};

#endif

