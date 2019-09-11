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
#include "notemanager.h"

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
class Score
{
public://メンバー変数
private:
	Texmanager texmanager;								//テクスチャのマネージャーのメンバー変数
	D3DXVECTOR3 pos;									//表示位置
	LPDIRECT3DTEXTURE9 scoreTex = NULL;					//テクスチャへのポインタ
	VERTEX_2D vertexScore[SCORE_DIGIT][NUM_VERTEX];		//頂点情報格納ワーク
	D3DXVECTOR3 vertexScorePos[NUM_VERTEX];				//頂点の位置情報

public://メンバー関数
	Score();//テクスチャの読み込み

	~Score();//テクスチャの解放

	void UninitScore();
	//更新処理
	void UpdateScore();
	//描画処理
	void DrawScore();
    //頂点の作成
	void MakeVertex(D3DXVECTOR3 pos);
	//スコアの設置
	void SetScore(int num);
	//スコアの獲得
	int GetScore();

};

	//=================================================
	// スコア加算関数
	// 第１引数：int rate(判定評価)
	// 戻り値　：無し
	//=================================================
	void AddScore(int rate);

#endif

