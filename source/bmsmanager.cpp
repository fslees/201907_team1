//=============================================================================
//
// 譜面データの管理処理 [bmsmanager.cpp]
// Author : GP12A332_26_田中太陽
//
//=============================================================================
#include "bmsmanager.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define LANE_MAX		(3)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
const int BmsManager::index[BMS_CHANNEL_MAX] = { 0,2,4,1,3,5 };
D3DXVECTOR3	LinePos[LANE_MAX];

//====================================================================
// コンストラクタ
//====================================================================
BmsManager::BmsManager()
{
	// 各変数の初期化
	scrMulti = 1.0f;
	startTime = 0;
	globalFreq = 0;
	elapsedTime = 0;
	scrZ = 0;
	ZeroMemory(&startNum, sizeof(startNum));

	//出現位置のposの初期化
	for (int i = 0; i < LANE_MAX; i++)
	{
		LinePos[i] = D3DXVECTOR3(50 - 50 * i, 0, 0);
	}

	// BMSロード
	bms.Load("data/BMS/test2.bms");

	// マシンの周波数を取得
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	globalFreq = freq.QuadPart;

	// 現在の時間を開始時間とする
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	startTime = li.QuadPart;
}

//====================================================================
// デストラクタ
//====================================================================
BmsManager::~BmsManager()
{
	bms.Clear();
}

//====================================================================
// 譜面データの更新処理
//====================================================================
void BmsManager::Update()
{
	// 開始時から経過した時間を算出
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	elapsedTime = (double)(li.QuadPart - startTime) / globalFreq;

	// 経過した時間から進んだBMSカウント値を算出
	nowCount = bms.GetCountFromTime(elapsedTime);

	// BMSカウンタが曲の最大カウント+1小節を超えたら終了
	if (bms.GetMaxCount() + BMS_RESOLUTION <= nowCount)
		return;

	// BGMをタイミングにあわせて再生する
	for (int i = startNum[BMS_BACKMUSIC]; i < bms.GetObjeNum(BMS_BACKMUSIC); i++) {
		LPBMSDATA b = bms.GetObje(BMS_BACKMUSIC, i);
		if (nowCount < b->lTime)
			break;
		if (b->bFlag) {
			if (nowCount >= b->lTime) 
			{
				b->bFlag = FALSE;				// 通過したBGMフラグをfalse
				startNum[BMS_BACKMUSIC] = i + 1;
			}
		}
	}

	// スクリーン座標上でのスクロール量を算出
	scrZ = (int)((double)nowCount / (BMS_RESOLUTION / (scrMulti * 192)));
}

//====================================================================
// 譜面データのノーツ発生時間の確認処理
//====================================================================
bool BmsManager::CheckSetCount(NoteManager *note)
{
	for (int j = 0; j < 6; j++)
	{
		for (int i = startNum[0x11 + index[j]]; i < bms.GetObjeNum(0x11 + index[j]); i++)
		{
			LPBMSDATA b = bms.GetObje(0x11 + index[j], i);
			if (nowCount > b->lTime)
			{
				note->SetNote(j);
			}

			int objZ = (int)((double)b->lTime / (BMS_RESOLUTION / (scrMulti * 192)));
			// スクロールを考慮した現在のZ座標を算出
			offZ = objZ - scrZ;
			// 判定ラインより下ならもう表示はせず、次回からその次のオブジェから参照する
			if (offZ < 0) 
			{
				startNum[index[j] + 0x11] = i + 1;
				continue;
			}
		}
	}

	return false;
}
