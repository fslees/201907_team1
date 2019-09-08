//========================================
// 2Dのテクスチャ作成[2Dtexmanager]
//  Author : 染矢　晃介
//========================================
#include "2Dtexmanager.h"
#include "main.h"

//========================================
// 描画処理
// 引数１[テクスチャへのポインタ]
// 引数２[頂点情報]
//========================================
void Texmanager::Draw(LPDIRECT3DTEXTURE9 p, VERTEX_2D vertex[NUM_VERTEX])
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, p);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertex, sizeof(VERTEX_2D));

}

//============================================
// 頂点作成
// 引数：頂点情報格納ワーク
//============================================
void Texmanager::MakeVertex(VERTEX_2D vertex[NUM_VERTEX])
{
	// 頂点座標の設定
	vertex[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	vertex[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	vertex[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// テクスチャのパースペクティブコレクト用
	vertex[0].rhw =
		vertex[1].rhw =
		vertex[2].rhw =
		vertex[3].rhw = 1.0f;

	// 反射光の設定
	vertex[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertex[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertex[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertex[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertex[3].tex = D3DXVECTOR2(1.0f, 1.0f);

}