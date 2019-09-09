//=============================================================================
//
// 判定ライン処理 [hitline.cpp]
// Author : GP12A332_26_田中太陽
//
//=============================================================================
#include "main.h"
#include "hitline.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_LINE		"data/TEXTURE/hitLine.png"		// 読み込むテクスチャファイル名
#define INIT_POS_X			(0.0f)						// X座標の初期位置
#define INIT_POS_Y			(50.0f)						// Y座標
#define INIT_POS_Z			(0.0f)						// Z座標

#define	INIT_SIZE_X			(1.0f)						// 判定ラインのサイズ X方向
#define	INIT_SIZE_Y			(1.0f)						// Y方向
#define	INIT_SIZE_Z			(1.0f)						// Z方向

#define VTX_X				(200.0f)					// 頂点X座標
#define VTX_Z				(20.0f)					// 頂点Z座標

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//=============================================================================
// 初期化処理
//=============================================================================
HitLine::HitLine()
{	
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// 位置・回転・スケールの初期設定
	pos = D3DXVECTOR3(INIT_POS_X, INIT_POS_Y, INIT_POS_Z);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(INIT_SIZE_X, INIT_SIZE_Y, INIT_SIZE_Z);

	// 頂点情報の作成
	MakeVertexHitLine(pDevice);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(pDevice,					// デバイスへのポインタ
		TEXTURE_LINE,			// ファイルの名前
		&D3DTexture);	// 読み込むメモリー
	
}

//=============================================================================
// 終了処理
//=============================================================================
HitLine::~HitLine(void)
{
	if (D3DTexture != NULL)
	{// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}

	if (D3DVtxBuff != NULL)
	{// 頂点バッファの開放
		D3DVtxBuff->Release();
		D3DVtxBuff = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void HitLine::Update(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void HitLine::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 頂点バッファをデバイスのデータストリームにバインド
	pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	pDevice->SetTexture(0, D3DTexture);

	// ポリゴンの描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

//=============================================================================
// 頂点の作成
//=============================================================================
HRESULT HitLine::MakeVertexHitLine(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuff,			// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(VTX_X, 0.0f, 0);
		pVtx[1].vtx = D3DXVECTOR3(-VTX_X, 0.0f, 0);
		pVtx[2].vtx = D3DXVECTOR3(VTX_X, 0.0f, VTX_Z);
		pVtx[3].vtx = D3DXVECTOR3(-VTX_X, 0.0f, VTX_Z);

		// 法線ベクトルの設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}
