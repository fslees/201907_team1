//=============================================================================
//
// スコアの定義 [score.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _SCORE_H_
#define _SCORE_H_

#include "main.h"
#include "2Dtexmanager.h"

//=================================
// マクロ定義
//=================================
#define TEXTURE_SCORE "data/TEXTURE/field001.jpg"


//===============================
//クラス定義
//===============================
class Score
{
public://メンバー変数
	Texmanager texmanager;					//テクスチャのマネージャーのメンバー変数
	LPDIRECT3DTEXTURE9 scoreTex = NULL;		//テクスチャへのポインタ
	VERTEX_2D vertexScore[NUM_VERTEX];		//頂点情報格納ワーク
	D3DXVECTOR3 vertexScorePos[NUM_VERTEX];	//頂点の位置情報

private:


public://メンバー関数
	Score();//テクスチャの読み込み

	~Score();//テクスチャの解放

	void UninitScore();
	//
	void UpdateScore();
	//
	void DrawScore();

private:

};


#endif

