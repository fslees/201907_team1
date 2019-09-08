//=============================================================================
//
// レーンの処理 [lane.cpp]
// Author : 
//
//=============================================================================
#include "lane.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	LANE_MODEL		"data/MODEL/car000.x"	// 読み込むモデル名
// スケールの初期値
#define INIT_SCL_X_LANE		(1.0f)					
#define INIT_SCL_Y_LANE		(1.0f)
#define INIT_SCL_Z_LANE		(100000.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	D3DTextureLane;		// テクスチャへのポインタ
LPD3DXMESH			D3DXMeshLane;		// メッシュ情報へのポインタ
LPD3DXBUFFER		D3DXBuffMatLane;	// マテリアル情報へのポインタ
DWORD				NumMatLane;			// マテリアル情報の数

//=============================================================================
// 初期化処理
//=============================================================================
Lane :: Lane()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	D3DTextureLane = NULL;
	D3DXMeshLane = NULL;
	D3DXBuffMatLane = NULL;
	NumMatLane = 0;
	
	for (int cnt = 0; cnt < LANE_NUM_MAX; cnt++)
	{
		// 位置・スケールの初期設定
		pos[cnt] = D3DXVECTOR3(-INIT_POS_X_LANE + LANE_SPACE * cnt, INIT_POS_Y_LANE, -INIT_POS_Z_LANE);
		scl[cnt] = D3DXVECTOR3(INIT_SCL_X_LANE, INIT_SCL_Y_LANE, INIT_SCL_Z_LANE);
	}

	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(LANE_MODEL,				// 読み込むモデルファイル名(Xファイル)
								D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
								pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
								NULL,					// 隣接性データを含むバッファへのポインタ
								&D3DXBuffMatLane,	// マテリアルデータを含むバッファへのポインタ
								NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
								&NumMatLane,		// D3DXMATERIAL構造体の数
								&D3DXMeshLane)))	// ID3DXMeshインターフェイスへのポインタのアドレス
	{
		return;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_FILENAME,		// ファイルの名前
		&D3DTextureLane);	// 読み込むメモリー
#endif
}

//=============================================================================
// 終了処理
//=============================================================================
 Lane :: ~Lane()
{
	if (D3DTextureLane != NULL)
	{// テクスチャの開放
		D3DTextureLane->Release();
		D3DTextureLane = NULL;
	}

	if (D3DXMeshLane != NULL)
	{// メッシュの開放
		D3DXMeshLane->Release();
		D3DXMeshLane = NULL;
	}

	if (D3DXBuffMatLane != NULL)
	{// マテリアルの開放
		D3DXBuffMatLane->Release();
		D3DXBuffMatLane = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void Lane :: Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void Lane :: Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;

	for (int cnt = 0; cnt < LANE_NUM_MAX; cnt++)
	{
		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// スケールを反映
		D3DXMatrixScaling(&mtxScl, scl[cnt].x, scl[cnt].y, scl[cnt].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos[cnt].x, pos[cnt].y, pos[cnt].z);
		D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// マテリアル情報に対するポインタを取得
		pD3DXMat = (D3DXMATERIAL*)D3DXBuffMatLane->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)NumMatLane; nCntMat++)
		{
			// マテリアルの設定
			pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

			// テクスチャの設定
			pDevice->SetTexture(0, D3DTextureLane);

			// 描画
			D3DXMeshLane->DrawSubset(nCntMat);
		}

		// マテリアルをデフォルトに戻す
		pDevice->SetMaterial(&matDef);
	}
}

