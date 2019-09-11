//=============================================================================
//
// タイトル画面の定義 [title.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_TITLELOGO "data/TEXTURE/number.png"
#define LOGO_POS_X			(500)	//ロゴのx座標
#define LOGO_POS_Y			(450)	//ロゴのY座標
#define LOGO_WIDTH			(280)	//幅
#define LOGO_HEIGHT			(100)	//高さ
#define	COUNT_APPERA_LOGO	(60)	// スタートボタン出現までの時間
#define	INTERVAL_DISP_LOGO	(60)	// スタートボタン点滅の時間

//===========================
//プロトタイプ宣言
//===========================
//初期化
HRESULT InitTitleLogo();
//終了処理
void UninitTitleLogo();
//更新処理
void UpdateTitleLogo();
//描画処理
void DrawTitleLogo();
//頂点作成処理
void MakeVertexTitleLogo();
//反射光の設定
void SetColorLogo();

#endif
