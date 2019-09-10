//=============================================================================
//
// タイトル画面の実装 [title.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "title.h"
#include "scene.h"
#include "input.h"
#include "inputmanager.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 titleTex = NULL;	//テクスチャへのポインタ
VERTEX_2D vertexTitle[NUM_VERTEX];		//頂点情報格納ワーク
D3DXVECTOR3 vertexTitlePos[NUM_VERTEX];		//頂点の位置情報

//*****************************************************************************
// ゲームの初期化
//*****************************************************************************
HRESULT InitTitle()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
								TEXTURE_TITLE,		// ファイルの名前
								&titleTex);		// 読み込むメモリー

	//頂点の作成
	MakeVertexTitle();

	return S_OK;
}

//*****************************************************************************
// ゲームの終了
//*****************************************************************************
void UninitTitle()
{
	if (titleTex != NULL)
	{// テクスチャの開放
		titleTex->Release();
		titleTex = NULL;
	}
}

//*****************************************************************************
// ゲームの更新
//*****************************************************************************
void UpdateTitle()
{
	if (GetKeyboardTrigger(DIK_1))
	{

		SetScene(SCENE_TUTORIAL);
	}
}

//*****************************************************************************
// ゲーム画面の描画
//*****************************************************************************
void DrawTitle()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, titleTex);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexTitle, sizeof(VERTEX_2D));
}

//========================================
//頂点の作成
//========================================
void MakeVertexTitle()
{
	// 頂点座標の設定
	vertexTitle[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexTitle[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	vertexTitle[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	vertexTitle[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// テクスチャのパースペクティブコレクト用
	vertexTitle[0].rhw =
	vertexTitle[1].rhw =
	vertexTitle[2].rhw =
	vertexTitle[3].rhw = 1.0f;

	// 反射光の設定
	vertexTitle[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitle[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitle[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitle[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexTitle[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexTitle[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexTitle[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexTitle[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}