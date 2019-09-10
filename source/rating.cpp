//=============================================================================
//
// ヒット時の精度表示処理 [hitqualety.cpp]
// Author : GP12A332_26_田中太陽
//
//=============================================================================
#include "rating.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define RATING_MAX			(10) 
#define DELETE_CNT			(30)
// テクスチャーデータ
#define TEXTURE_PERFECT		("data/TEXTURE/perfect.png")
#define TEXTURE_GREAT		("data/TEXTURE/great.png")
#define TEXTURE_GOOD		("data/TEXTURE/good.png")
// 頂点サイズ
#define TEXTURE_SIZE_X		(100.0f)
#define TEXTURE_SIZE_Y		(35.0f)
#define TEXTURE_POS_Y		(550.0f)
// 初期位置
#define INIT_POS_X			(0.0f)
#define INIT_POS_Y			(0.0f)
#define INIT_POS_Z			(-50.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexRating(int rno);
void DeleteRating(int frame, int rno);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		texture[TEX_MAX] = { NULL,NULL, NULL };	//テクスチャへのポインタ
VERTEX_2D				vertex[RATING_MAX][NUM_VERTEX];		// 頂点情報格納ワーク
Rating					rating[RATING_MAX];
//*****************************************************************************
// 初期化
//*****************************************************************************
HRESULT InitRating()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	for (int i = 0; i < RATING_MAX; i++)
	{
		// 変数の初期化
		rating[i].texNum = PERFECT;
		rating[i].use = false;
		rating[i].frameCnt = 0;
		//頂点の作成
		MakeVertexRating(i);
	}

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
		TEXTURE_PERFECT,	// ファイルの名前
		&texture[PERFECT]);	// 読み込むメモリー
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
		TEXTURE_GREAT,		// ファイルの名前
		&texture[GREAT]);	// 読み込むメモリー
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
		TEXTURE_GOOD,		// ファイルの名前
		&texture[GOOD]);	// 読み込むメモリー

	return S_OK;
}

//*****************************************************************************
// ゲームの終了
//*****************************************************************************
void UninitRating()
{
	for (int i = 0; i < TEX_MAX; i++)
	{
		if (texture[i] != NULL)
		{// テクスチャの開放
			texture[i]->Release();
			texture[i] = NULL;
		}
	}
}

//*****************************************************************************
// ゲームの更新
//*****************************************************************************
void  UpdateRating()
{
	for (int i = 0; i < RATING_MAX; i++)
	{
		if (rating[i].use)
		{
			rating[i].frameCnt++;

			DeleteRating(rating[i].frameCnt, i);
		}
	}
}

//*****************************************************************************
// リザルト画面の描画
//*****************************************************************************
void DrawRating()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	for (int i = 0; i < RATING_MAX; i++)
	{
		if (rating[i].use)
		{
			// 頂点フォーマットの設定
			Device->SetFVF(FVF_VERTEX_2D);

			// テクスチャの設定
			Device->SetTexture(0, texture[rating[i].texNum]);

			// ポリゴンの描画
			Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertex[i], sizeof(VERTEX_2D));
		}
	}
}

//=========================================
//頂点の作成
//=========================================
void MakeVertexRating(int rno)
{
	// 頂点座標の設定
	vertex[rno][0].vtx = D3DXVECTOR3((float)(SCREEN_CENTER_X)-TEXTURE_SIZE_X, TEXTURE_POS_Y - TEXTURE_SIZE_Y, 0.0f);
	vertex[rno][1].vtx = D3DXVECTOR3((float)(SCREEN_CENTER_X)+TEXTURE_SIZE_X, TEXTURE_POS_Y - TEXTURE_SIZE_Y, 0.0f);
	vertex[rno][2].vtx = D3DXVECTOR3((float)(SCREEN_CENTER_X)-TEXTURE_SIZE_X, TEXTURE_POS_Y + TEXTURE_SIZE_Y, 0.0f);
	vertex[rno][3].vtx = D3DXVECTOR3((float)(SCREEN_CENTER_X)+TEXTURE_SIZE_X, TEXTURE_POS_Y + TEXTURE_SIZE_Y, 0.0f);

	// テクスチャのパースペクティブコレクト用
	vertex[rno][0].rhw =
		vertex[rno][1].rhw =
		vertex[rno][2].rhw =
		vertex[rno][3].rhw = 1.0f;

	// 反射光の設定
	vertex[rno][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[rno][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[rno][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertex[rno][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertex[rno][0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertex[rno][1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertex[rno][2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertex[rno][3].tex = D3DXVECTOR2(1.0f, 1.0f);
}

//=========================================
//評価表示の設置
//=========================================
void SetRatingTex(int texNum)
{
	for (int i = 0; i < RATING_MAX; i++)
	{
		if (!rating[i].use)
		{
			rating[i].texNum = texNum;
			rating[i].use = true;

			break;
		}
	}
}

//=========================================
//評価表示の設置
//=========================================
void DeleteRating(int frame, int rno)
{
	if (frame % DELETE_CNT == 0)
	{
		rating[rno].use = false;
	}
}