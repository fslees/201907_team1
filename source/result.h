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
//プロトタイプ宣言
//===============================

	//初期化
	HRESULT InitResult();
	//終了処理
	void UninitResult();
	//更新処理
	void UpdateResult();
	//描画処理
	void DrawResult();
	//頂点の作成
	void MakeVertex();
#endif
