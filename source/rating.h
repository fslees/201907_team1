//=============================================================================
//
// ヒット時の精度表示の定義 [hitqualety.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _RATING_H_
#define _RATING_H_

#include "main.h"
#include "camera.h"

//=================================
// マクロ定義
//=================================
enum RATING_TEX
{
	PERFECT,
	GREAT,
	GOOD,
	TEX_MAX,
};

class Rating
{
private:
	Camera					camera;

	LPDIRECT3DTEXTURE9		texture[TEX_MAX] = { NULL,NULL, NULL };	//テクスチャへのポインタ
	VERTEX_2D				vertex[NUM_VERTEX];		// 頂点情報格納ワーク
	D3DXMATRIX				mtxWorld;

public:
	int						texNum;					// テクスチャーの番号
	bool					use;					// 使用状態
	//初期化
	Rating();
	//終了処理
	~Rating();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	//頂点の作成
	void MakeVertex();

};
#endif
