//=============================================================================
//
// チュートリアルの定義 [tutorial.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _TUTORIAL_H_
#define _TUTORIAL_H_

#include "main.h"

//=================================
// マクロ定義
//=================================
#define TEXTURE_TUTORIAL "data/TEXTURE/tutorial.png"

//===============================
//プロトタイプ宣言
//===============================

	//初期化
	HRESULT InitTutorial();
	//終了処理
	void	UninitTutorial();
	//更新処理
	void	UpdateTutorial();
	//描画処理
	void	DrawTutorial();
	//頂点の作成
	void MakeVertexTutorial();
#endif
