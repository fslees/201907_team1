//=============================================================================
//
// スコアの定義 [score.h]
// Author :染矢　晃介
//
//=============================================================================
#ifndef _RESULTSCORE_H_
#define _RESULTSCORE_H_

#include "main.h"
#include "score.h"

//=================================
// マクロ定義
//=================================
#define TEXTURE_SCORE "data/TEXTURE/number.png"
#define TEXTURE_SCORE_SIZE_X			(100)					// スコアテクスチャサイズ
#define TEXTURE_SCORE_SIZE_Y			(100)					// 同上
#define SCORE_POS_X						(1200)					// スコアの初期位置X
#define SCORE_POS_Y						(10)					// 同上
#define SCORE_WIDE				(50)                            //数字の幅
#define SCORE_MAX				(99999)							// スコアの最大値
#define SCORE_DIGIT				(5)								// 桁数

//===============================
//クラス定義
//===============================
class Resultscore:public Score
{
public://メンバー変数
	LPDIRECT3DTEXTURE9  resultScoreTex = NULL;					//テクスチャへのポインタ
	VERTEX_2D vertexResultScore[SCORE_DIGIT][NUM_VERTEX];		//頂点情報格納ワーク
	D3DXVECTOR3 vertexResultScorePos[NUM_VERTEX];				//頂点の位置情報
	D3DXVECTOR3 pos;											//表示位置
	int         resultScoreNum;									//スコアの実数値

private:


public://メンバー関数
	Resultscore();//テクスチャの読み込み

	~Resultscore();//テクスチャの解放

	void UninitResultScore();
	//
	void UpdateResultScore();
	//
	void DrawResultScore();
	//
	void MakeVertex(D3DXVECTOR3 pos);
	//
	void SetResultScore(int num);
	

private:

};


#endif


