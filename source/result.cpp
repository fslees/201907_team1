//=============================================================================
//
// 結果画面の実装 [result.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "result.h"
#include "input.h"
#include "scene.h"
#include "inputmanager.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 resultTex = NULL;	//テクスチャへのポインタ
VERTEX_2D vertexResult[NUM_VERTEX];		//頂点情報格納ワーク
D3DXVECTOR3 vertexPos[NUM_VERTEX];		//頂点の位置情報

//*****************************************************************************
// コンストラクタ　リザルトの読み込み
//*****************************************************************************
HRESULT InitResult()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
								TEXTURE_RESULT,		// ファイルの名前
								&resultTex);		// 読み込むメモリー


	//頂点の作成
	MakeVertex();

	return S_OK;
}


//*****************************************************************************
// ゲームの終了
//*****************************************************************************
void UninitResult()
{
	if (resultTex != NULL)
	{// テクスチャの開放
		resultTex->Release();
		resultTex = NULL;
	}
}

//*****************************************************************************
// ゲームの更新
//*****************************************************************************
void  UpdateResult()
{
	if (GetKeyboardTrigger(DIK_1))
	{
		SetScene(0);
	}
}

//*****************************************************************************
// リザルト画面の描画
//*****************************************************************************
void DrawResult()
{
	//texmanager->Draw(resultTex, &vertexResult[NUM_VERTEX]);
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, resultTex);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexResult, sizeof(VERTEX_2D));

}

//=========================================
//頂点の作成
//=========================================
void MakeVertex()
{
	// 頂点座標の設定
	vertexResult[0].vtx = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertexResult[1].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), 0.0f, 0.0f);
	vertexResult[2].vtx = D3DXVECTOR3(0.0f, (float)(SCREEN_HEIGHT), 0.0f);
	vertexResult[3].vtx = D3DXVECTOR3((float)(SCREEN_WIDTH), (float)(SCREEN_HEIGHT), 0.0f);


	// テクスチャのパースペクティブコレクト用
	vertexResult[0].rhw =
	vertexResult[1].rhw =
	vertexResult[2].rhw =
	vertexResult[3].rhw = 1.0f;

	// 反射光の設定
	vertexResult[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexResult[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexResult[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexResult[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

	// テクスチャ座標の設定
	vertexResult[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexResult[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexResult[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexResult[3].tex = D3DXVECTOR2(1.0f, 1.0f);
}