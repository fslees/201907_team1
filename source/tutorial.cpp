//=============================================================================
//
// チュートリアルの実装 [tutorial.cpp]
// Author : GP12A332_26_田中太陽
//
//=============================================================================
#include "scene.h"
#include "inputmanager.h"
#include "tutorial.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define TEXTURE_TUTORIAL ("data/TEXTURE/tutorial.png")

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
void MakeVertexTutorial();

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 TutorialTex = NULL;	//テクスチャへのポインタ
VERTEX_2D VertexTutorial[NUM_VERTEX];		//頂点情報格納ワーク
D3DXVECTOR3 VertexTutorialPos[NUM_VERTEX];		//頂点の位置情報

//*****************************************************************************
// チュートリアルの初期化
//*****************************************************************************
HRESULT InitTutorial()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
		TEXTURE_TUTORIAL,		// ファイルの名前
		&TutorialTex);		// 読み込むメモリー

//頂点の作成
	MakeVertexTutorial();


	return S_OK;
}


//*****************************************************************************
// チュートリアルの終了
//*****************************************************************************
void UninitTutorial()
{
	if (TutorialTex != NULL)
	{// テクスチャの開放
		TutorialTex->Release();
		TutorialTex = NULL;
	}
}

//*****************************************************************************
// チュートリアルの更新
//*****************************************************************************
void  UpdateTutorial()
{
	if (GetInput(HIT_START))
	{
		SetScene(SCENE_GAME);
		SetTitleBGM();
	}
}

//*****************************************************************************
// チュートリアルの描画
//*****************************************************************************
void DrawTutorial()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, TutorialTex);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, VertexTutorial, sizeof(VERTEX_2D));
}

//========================================
//頂点の作成
//========================================
void MakeVertexTutorial()
{
	// 頂点座標の設定
	VertexTutorial[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	VertexTutorial[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	VertexTutorial[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	VertexTutorial[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// テクスチャのパースペクティブコレクト用
	VertexTutorial[0].rhw =
		VertexTutorial[1].rhw =
		VertexTutorial[2].rhw =
		VertexTutorial[3].rhw = 1.0f;

	// 反射光の設定
	VertexTutorial[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexTutorial[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexTutorial[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	VertexTutorial[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	VertexTutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	VertexTutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	VertexTutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	VertexTutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}