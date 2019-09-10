//=============================================================================
//
// ヒット時の精度表示の管理 [hitqualetymanager.h]
// Author : GP12A_332_26_田中太陽
//
//=============================================================================
#ifndef _RATINGMANAGER_H_
#define _RATINGMANAGER_H_

#include "main.h"
#include "rating.h"


//=================================
// クラス宣言
//=================================
class RatingManager
{
private:
	Rating	*rating;
public:
	//初期化
	RatingManager();
	//終了処理
	~RatingManager();
	//更新処理
	void Update();
	//描画処理
	void Draw();
	// 精度評価の設置
	void SetRaitng(int texNum);

};
#endif
