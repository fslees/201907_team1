//=============================================================================
//
// タイトルロゴの実装 [titlelogo.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "titlelogo.h"
#include "scene.h"
#include "input.h"
#include "inputmanager.h"

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 titlelogoTex = NULL;		//テクスチャへのポインタ
VERTEX_2D vertexTitleLogo[NUM_VERTEX];		//頂点情報格納ワーク
D3DXVECTOR3 vertexTitlelogoPos[NUM_VERTEX];	//頂点の位置情報
float	AlphaLogo ;							//ロゴのα値
int		CountAppearLogo;
int		CountDisp;
bool	DispStart;

//*****************************************************************************
// ゲームの初期化
//*****************************************************************************
HRESULT InitTitleLogo()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	//α値の初期化
	AlphaLogo = 0.0f;
	CountAppearLogo = 0;
	CountDisp = 0;
	DispStart = false;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
							TEXTURE_TITLELOGO,		// ファイルの名前
								&titlelogoTex);		// 読み込むメモリー

	//頂点の作成
	MakeVertexTitleLogo();

	return S_OK;
}

//*****************************************************************************
// ゲームの終了
//*****************************************************************************
void UninitTitleLogo()
{
	if (titlelogoTex != NULL)
	{// テクスチャの開放
		titlelogoTex->Release();
		titlelogoTex = NULL;
	}
}

//*****************************************************************************
// ゲームの更新
//*****************************************************************************
void UpdateTitleLogo()
{

	//ロゴが浮き出してくる
	if (AlphaLogo < 1.0f)
	{
		AlphaLogo += 0.005f;
		if (AlphaLogo >= 1.0f)
		{
			AlphaLogo = 1.0f;
		}
		SetColorLogo();
	}
	else
	{
		CountAppearLogo++;
		if (CountAppearLogo > COUNT_APPERA_LOGO)
		{
			CountDisp = (CountDisp + 1) % 80;
			if (CountDisp > INTERVAL_DISP_LOGO)
			{
				DispStart = false;
			}
			else
			{
				DispStart = true;
			}
		}
	}

	//点滅処理
	if (AlphaLogo < 1.0f)
	{
		AlphaLogo += 0.010f;
		if (AlphaLogo >= 1.0f)
		{
			AlphaLogo--;
		}
		SetColorLogo();
	}
}

//*****************************************************************************
// ゲーム画面の描画
//*****************************************************************************
void DrawTitleLogo()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 頂点フォーマットの設定
	Device->SetFVF(FVF_VERTEX_2D);

	// テクスチャの設定
	Device->SetTexture(0, titlelogoTex);

	// ポリゴンの描画
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexTitleLogo, sizeof(VERTEX_2D));
}

//========================================
//頂点の作成
//========================================
void MakeVertexTitleLogo()
{
	// 頂点座標の設定
	vertexTitleLogo[0].vtx = D3DXVECTOR3(LOGO_POS_X, LOGO_POS_Y, 0.0f);
	vertexTitleLogo[1].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_WIDTH, LOGO_POS_Y, 0.0f);
	vertexTitleLogo[2].vtx = D3DXVECTOR3(LOGO_POS_X, LOGO_POS_Y + LOGO_HEIGHT, 0.0f);
	vertexTitleLogo[3].vtx = D3DXVECTOR3(LOGO_POS_X + LOGO_WIDTH, LOGO_POS_Y + LOGO_HEIGHT, 0.0f);


	// テクスチャのパースペクティブコレクト用
	vertexTitleLogo[0].rhw =
	vertexTitleLogo[1].rhw =
	vertexTitleLogo[2].rhw =
	vertexTitleLogo[3].rhw = 1.0f;

	// 反射光の設定
	/*vertexTitleLogo[0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitleLogo[1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitleLogo[2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
	vertexTitleLogo[3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);*/
	vertexTitleLogo[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);

	// テクスチャ座標の設定
	vertexTitleLogo[0].tex = D3DXVECTOR2(0.0f, 0.0f);
	vertexTitleLogo[1].tex = D3DXVECTOR2(1.0f, 0.0f);
	vertexTitleLogo[2].tex = D3DXVECTOR2(0.0f, 1.0f);
	vertexTitleLogo[3].tex = D3DXVECTOR2(1.0f, 1.0f);

}

//========================================
//点滅用の色の設定
//========================================
void SetColorLogo()
{
	vertexTitleLogo[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
	vertexTitleLogo[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, AlphaLogo);
}