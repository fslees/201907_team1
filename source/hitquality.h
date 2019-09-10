//=============================================================================
//
// ヒット時の精度表示の定義 [hitqualety.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _HITQUALITY_H_
#define _HITQUALITY_H_

#include "main.h"
#include "camera.h"

//=================================
// マクロ定義
//=================================
enum HitQUALETY_TEX
{
	PERFECT,
	GREAT,
	GOOD,
	TEX_MAX,
};

class HitQualety
{
private:
	Camera					camera;

	LPDIRECT3DTEXTURE9		D3DTexture[TEX_MAX] = { NULL,NULL, NULL };	//テクスチャへのポインタ
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff = NULL;		// 頂点バッファインターフェースへのポインタ
	VERTEX_3D				vertex[NUM_VERTEX];		// 頂点情報格納ワーク
	D3DXMATRIX				mtxWorld;
	D3DXVECTOR3				pos;					// 座標
	D3DXVECTOR3				rot;					// 回転量
	D3DXVECTOR3				scl;					// 大きさ
	bool					use;					// 使用状態
	int						texNum;					// テクスチャーの番号

public:
	//初期化
	HitQualety();
	//終了処理
	~HitQualety();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//頂点の作成
	HRESULT MakeVertex(LPDIRECT3DDEVICE9 pDevice);

	// 拡大アニメーション
	void SetSclAnim();

};
#endif
