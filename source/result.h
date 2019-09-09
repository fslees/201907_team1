//=============================================================================
//
// 結果画面の定義 [result.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _RESULT_H_
#define _RESULT_H_

#include "main.h"
#include "2Dtexmanager.h"

//=================================
// マクロ定義
//=================================
#define TEXTURE_RESULT "data/TEXTURE/field000.jpg"


//===============================
//クラス定義
//===============================
class Result
{
public://メンバー変数
	Texmanager texmanager;					//テクスチャのマネージャーのメンバー変数
	LPDIRECT3DTEXTURE9 resultTex = NULL;	//テクスチャへのポインタ
	VERTEX_2D vertexResult[NUM_VERTEX];		//頂点情報格納ワーク
	D3DXVECTOR3 vertexPos[NUM_VERTEX];		//頂点の位置情報
	


private:


public://メンバー関数
	Result();//テクスチャの読み込み

	~Result();//テクスチャの解放

	void UninitResult();
	//
	void UpdateResult();
	//
	void DrawResult();

private:

};


#endif
