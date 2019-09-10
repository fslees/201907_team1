//=============================================================================
//
// チュートリアルの実装 [tutorial.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "scene.h"
#include "inputmanager.h"
#include "tutorial.h"
#include "input.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 tutorialTex = NULL;	//テクスチャへのポインタ
VERTEX_2D vertexTutorial[NUM_VERTEX];		//頂点情報格納ワーク
D3DXVECTOR3 vertexTutorialPos[NUM_VERTEX];		//頂点の位置情報

//*****************************************************************************
// チュートリアルの初期化
//*****************************************************************************
HRESULT InitTutorial()
{

	LPDIRECT3DDEVICE9 Device = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
								TEXTURE_TUTORIAL,	// ファイルの名前
								&tutorialTex);		// 読み込むメモリー

							

	//頂点の作成
	MakeVertexTutorial();

	return S_OK;
}


//*****************************************************************************
// チュートリアルの終了
//*****************************************************************************
void UninitTutorial()
{
}

//*****************************************************************************
// チュートリアルの更新
//*****************************************************************************
void  UpdateTutorial()
{
	if (GetKeyboardTrigger(DIK_1))
	{
		SetScene(SCENE_GAME);
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
	Device->SetTexture(0, tutorialTex);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexTutorial, sizeof(VERTEX_2D));
}

//=====================================
//チュートリアル用の頂点作成
//=====================================
void MakeVertexTutorial()
{
	// 頂点座標の設定
	vertexTutorial[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexTutorial[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	vertexTutorial[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	vertexTutorial[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// テクスチャのパースペクティブコレクト用
	vertexTutorial[0].rhw =
	vertexTutorial[1].rhw =
	vertexTutorial[2].rhw =
	vertexTutorial[3].rhw = 1.0f;

	// 反射光の設定
	vertexTutorial[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTutorial[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTutorial[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTutorial[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexTutorial[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexTutorial[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexTutorial[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexTutorial[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}