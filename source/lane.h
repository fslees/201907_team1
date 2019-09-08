//=============================================================================
//
// レーンヘッダー処理 [lane.h]
// Author : GP12A332_25_染矢晃介
//
//=============================================================================
#ifndef _LANE_H_
#define _LANE_H_

#include "main.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LANE_MAX		(4)						// レーンの最大数
// 位置の初期値
#define INIT_POS_X_LANE		(75.0f)					// レーンの初期位置X座標
#define INIT_POS_Y_LANE		(50.0f)					// Y座標
#define INIT_POS_Z_LANE		(200.0f)				// Z座標
#define LANE_SPACE			(50.0f)					// レーン間隔の調整値

//*****************************************************************************
// クラス定義
//*****************************************************************************
class Lane
{
private:
	D3DXVECTOR3			pos[LANE_MAX];				// レーンの位置
	D3DXVECTOR3			scl[LANE_MAX];				// レーンの大きさ(スケール)
	bool				use;				// レーンの使用状態
	D3DXMATRIX			mtxWorld;			// ワールドマトリックス

public:
	Lane();
    ~Lane();
	void Update(void);
	void Draw(void);
};

#endif

