//=============================================================================
//
// ヒット時の精度表示の定義 [hitqualety.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _RATING_H_
#define _RATING_H_

#include "main.h"

//=================================
// マクロ定義
//=================================
#define PERFECT_POS		(20.0f)
#define GREATE_POS		(40.0f)
#define GOOD_POS		(50.0f)

enum RATING_TEX
{
	PERFECT,
	GREAT,
	GOOD,
	TEX_MAX,
};

//=================================
// 構造体宣言
//=================================
struct Rating
{
	int			texNum;					// テクスチャーの番号
	bool		use;					// 使用状態
	int			frameCnt;
};

//=================================
// プロトタイプ宣言
//=================================
//初期化
HRESULT InitRating();
//終了処理
void UninitRating();
//更新処理
void UpdateRating();
//描画処理
void DrawRating();
//判定評価の設置
void SetRatingTex(int texNum);

#endif
