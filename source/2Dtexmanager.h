//================================================
// 2Dのテクスチャ作成処理[2Dtexmanager.h]
// Author : 染矢　晃介
//================================================
#ifndef _2DTEXMANAGER_H_
#define _2DTEXMANAGER_H_


#include "main.h"

//================================
// クラス定義
//================================
class Texmanager
{
public: //メンバー変数

private:

public: //メンバー関数


	void Draw(LPDIRECT3DTEXTURE9 p, VERTEX_2D vertex[NUM_VERTEX]); //描画処理

	void MakeVertex(VERTEX_2D vertex[NUM_VERTEX]);  //頂点の作成

	//void DrawNumber(LPDIRECT3DTEXTURE9 p, VERTEX_2D vertex[NUM_VERTEX][SCORE_DIGIT]);

	//void MakeVertexNumber(VERTEX_2D vertex[NUM_VERTEX][SCORE_DIGIT], D3DXVECTOR3 pos); //スコアとコンボ用の頂点の作成

private:


};

#endif

