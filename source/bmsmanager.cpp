//=============================================================================
//
// 譜面データの管理処理 [bmsmanager.cpp]
// Author : GP12A332_26_田中太陽
//
//=============================================================================
#include "bmsmanager.h"
#include "sound.h"
#include "scene.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define BMS_CHANNEL_MAX		(6)		// BMSファイルのチャンネル数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
const int BmsManager::index[BMS_CHANNEL_MAX] = { 0,2,4,1,3,5 };

//====================================================================
// コンストラクタ
//====================================================================
BmsManager::BmsManager()
{
	// 各変数の初期化
	scrMulti = 5.0f;
	startTime = 0;
	globalFreq = 0;
	elapsedTime = 0;
	scrZ = 0;
	ZeroMemory(&startNum, sizeof(startNum));

	// BMSロード
	bms.Load("data/BMS/test2.bms");

	// サウンドのロード
	BGM = LoadSound(BGM_NULL);
	PlaySound(BGM, E_DS8_FLAG_LOOP);

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
void BmsManager::Update(NoteManager *note)
{
	// 開始時から経過した時間を算出
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	elapsedTime = (double)(li.QuadPart - startTime) / globalFreq;

	// 経過した時間から進んだBMSカウント値を算出
	nowCount = bms.GetCountFromTime(elapsedTime);

	// BMSカウンタが曲の最大カウント+1小節を超えたら終了
	if (bms.GetMaxCount() + BMS_RESOLUTION <= nowCount)
	{
		StopSound(BGM);
		SetScene(SCENE_RESULT);
		return;
	}

	// BGMをタイミングにあわせて再生する
	for (int i = startNum[BMS_BACKMUSIC]; i < bms.GetObjeNum(BMS_BACKMUSIC); i++) {
		LPBMSDATA b = bms.GetObje(BMS_BACKMUSIC, i);
		if (nowCount < b->lTime)
			break;
		if (b->bFlag) {
			if (nowCount >= (b->lTime * (scrMulti / 2)))
			{
				StopSound(BGM);
				BGM = LoadSound(BGM_GAME);
				PlaySound(BGM, E_DS8_FLAG_NONE);
				b->bFlag = FALSE;				// 通過したBGMフラグをfalse
				startNum[BMS_BACKMUSIC] = i + 1;
			}
		}
	}

	// スクリーン座標上でのスクロール量を算出
	scrZ = (int)((double)nowCount / (BMS_RESOLUTION / (scrMulti * 192)));

	CheckSetCount(note);
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
				note->SetNote(j, scrMulti);
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
