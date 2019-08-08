//=============================================================================
//
// 影処理 [Shadow.cpp]
// Author : 
//
//=============================================================================
#include "Shadow.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_SHADOW		"data/TEXTURE/shadow000.jpg"	// 読み込むテクスチャファイル名
#define	SHADOW_SIZE_X		(50.0f)							// 弾の幅
#define	SHADOW_SIZE_Z		(50.0f)							// 弾の高さ

#define	MAX_SHADOW			(128)							// 影最大数

//*****************************************************************************
// 構造体定義
//*****************************************************************************
typedef struct
{
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 回転
	bool use;				// 使用しているかどうか
} SHADOW;

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 device);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9		D3DTextureShadow = NULL;		// テクスチャへのポインタ
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffShadow = NULL;		// 頂点バッファインターフェースへのポインタ

SHADOW					Shadow[MAX_SHADOW];				// 影ワーク

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitShadow(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	// 頂点情報の作成
	MakeVertexShadow(device);

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,						// デバイスへのポインタ
								TEXTURE_SHADOW,				// ファイルの名前
								&D3DTextureShadow);			// 読み込むメモリー

	for(int cntShadow = 0; cntShadow < MAX_SHADOW; cntShadow++)
	{
		Shadow[cntShadow].pos = D3DXVECTOR3(0.0f, 0.1f, 0.0f);
		Shadow[cntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Shadow[cntShadow].use = false;
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitShadow(void)
{
	if(D3DTextureShadow != NULL)
	{// テクスチャの開放
		D3DTextureShadow->Release();
		D3DTextureShadow = NULL;
	}

	if(D3DVtxBuffShadow != NULL)
	{// 頂点バッファの開放
		D3DVtxBuffShadow->Release();
		D3DVtxBuffShadow = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateShadow(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawShadow(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
#if 0
	D3DXQUATERNION quat;
	D3DXVECTOR3 vecUpObj, vecUpField, outVec;
	float fDotProduct,fRot;
#endif

	// 減算合成
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);	// 結果 = 転送先(DEST) - 転送元(SRC)
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);

	// Z比較なし
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	for(int cntShadow = 0; cntShadow < MAX_SHADOW; cntShadow++)
	{
		if(Shadow[cntShadow].use)
		{
			// ワールドマトリックスの初期化
			D3DXMatrixIdentity(&Shadow[cntShadow].mtxWorld);

#if 0
			// 回転を反映
			D3DXQuaternionIdentity(&quat);

			vecUpObj = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// オブジェクトの上方向
			vecUpField = D3DXVECTOR3(0.0f, 1.0f, 0.0f);		// 地面の法線

			// オブジェクトの上方向と地面の法線の外積から回転軸を求める
			D3DXVec3Cross(&outVec, &vecUpObj, &vecUpField);

			// オブジェクトの上方向と地面の法線のなす角を求める
			fDotProduct = D3DXVec3Dot(&vecUpObj, &vecUpField);
			fRot = acosf(fDotProduct / (sqrtf(vecUpObj.x * vecUpObj.x + vecUpObj.y * vecUpObj.y + vecUpObj.z * vecUpObj.z)
														* sqrtf(vecUpField.x * vecUpField.x + vecUpField.y * vecUpField.y + vecUpField.z * vecUpField.z)));

			// 回転軸となす角からクォータニオンを求め、回転マトリックスを算出
			D3DXQuaternionRotationAxis(&quat, &outVec, fRot);
			D3DXMatrixRotationQuaternion(&mtxRot, &quat);
			D3DXMatrixMultiply(&g_mtxWorldShadow, &g_mtxWorldShadow, &mtxRot);
#endif
			// 回転を反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, Shadow[cntShadow].rot.y, Shadow[cntShadow].rot.x, Shadow[cntShadow].rot.z);
			D3DXMatrixMultiply(&Shadow[cntShadow].mtxWorld, &Shadow[cntShadow].mtxWorld, &mtxRot);

			// 移動を反映
			D3DXMatrixTranslation(&mtxTranslate, Shadow[cntShadow].pos.x,
													Shadow[cntShadow].pos.y,
													Shadow[cntShadow].pos.z);
			D3DXMatrixMultiply(&Shadow[cntShadow].mtxWorld,
										&Shadow[cntShadow].mtxWorld, &mtxTranslate);

			// ワールドマトリックスの設定
			device->SetTransform(D3DTS_WORLD, &Shadow[cntShadow].mtxWorld);

			// 頂点バッファをレンダリングパイプラインに設定
			device->SetStreamSource(0, D3DVtxBuffShadow, 0, sizeof(VERTEX_3D));

			// 頂点フォーマットの設定
			device->SetFVF(FVF_VERTEX_3D);

			// テクスチャの設定
			device->SetTexture(0, D3DTextureShadow);

			// ポリゴンの描画
			device->DrawPrimitive(D3DPT_TRIANGLESTRIP, (cntShadow * 4), NUM_POLYGON);
		}
	}

	// 通常ブレンド
	device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);			// 結果 = 転送元(SRC) + 転送先(DEST)
	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// Z比較あり
	device->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=============================================================================
// 頂点情報の作成
//=============================================================================
HRESULT MakeVertexShadow(LPDIRECT3DDEVICE9 device)
{
	// オブジェクトの頂点バッファを生成
    if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * MAX_SHADOW,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,						// 頂点バッファの使用法　
												FVF_VERTEX_3D,							// 使用する頂点フォーマット
												D3DPOOL_MANAGED,						// リソースのバッファを保持するメモリクラスを指定
												&D3DVtxBuffShadow,						// 頂点バッファインターフェースへのポインタ
												NULL)))									// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *vtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffShadow->Lock(0, 0, (void**)&vtx, 0);

		for(int cntShadow = 0; cntShadow < MAX_SHADOW; cntShadow++, vtx += 4)
		{
			// 頂点座標の設定
			vtx[0].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			vtx[1].vtx = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, SHADOW_SIZE_Z / 2);
			vtx[2].vtx = D3DXVECTOR3(-SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);
			vtx[3].vtx = D3DXVECTOR3(SHADOW_SIZE_X / 2, 0.0f, -SHADOW_SIZE_Z / 2);

			// 法線の設定
			vtx[0].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vtx[1].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vtx[2].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
			vtx[3].nor = D3DXVECTOR3(0.0f, 1.0f, 0.0f);

			// 反射光の設定
			vtx[0].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			vtx[1].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			vtx[2].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
			vtx[3].diffuse = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

			// テクスチャ座標の設定
			vtx[0].tex = D3DXVECTOR2(0.0f, 0.0f);
			vtx[1].tex = D3DXVECTOR2(1.0f, 0.0f);
			vtx[2].tex = D3DXVECTOR2(0.0f, 1.0f);
			vtx[3].tex = D3DXVECTOR2(1.0f, 1.0f);
		}

		// 頂点データをアンロックする
		D3DVtxBuffShadow->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 頂点座標の設定
//=============================================================================
void SetVertexShadow(int idxShadow, float sizeX, float sizeZ)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *vtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffShadow->Lock(0, 0, (void**)&vtx, 0);

		vtx += (idxShadow * 4);

		// 頂点座標の設定
		vtx[0].vtx = D3DXVECTOR3(-sizeX / 2, 0.0f, sizeZ / 2);
		vtx[1].vtx = D3DXVECTOR3(sizeX / 2, 0.0f, sizeZ / 2);
		vtx[2].vtx = D3DXVECTOR3(-sizeX / 2, 0.0f, -sizeZ / 2);
		vtx[3].vtx = D3DXVECTOR3(sizeX / 2, 0.0f, -sizeZ / 2);

		// 頂点データをアンロックする
		D3DVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// 頂点カラーの設定
//=============================================================================
void SetColorShadow(int idxShadow, D3DXCOLOR col)
{
	{//頂点バッファの中身を埋める
		VERTEX_3D *vtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffShadow->Lock(0, 0, (void**)&vtx, 0);

		vtx += (idxShadow * 4);

		// 頂点座標の設定
		vtx[0].diffuse =
		vtx[1].diffuse =
		vtx[2].diffuse =
		vtx[3].diffuse = col;

		// 頂点データをアンロックする
		D3DVtxBuffShadow->Unlock();
	}
}

//=============================================================================
// 影の作成
//=============================================================================
int CreateShadow(D3DXVECTOR3 pos, float sizeX, float sizeZ)
{
	int idxShadow = -1;

	for(int cntShadow = 0; cntShadow < MAX_SHADOW; cntShadow++)
	{
		if(!Shadow[cntShadow].use)
		{
			Shadow[cntShadow].pos = pos;
			Shadow[cntShadow].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
			Shadow[cntShadow].use = true;

			SetVertexShadow(cntShadow, sizeX, sizeZ);

			idxShadow = cntShadow;
			break;
		}
	}

	return idxShadow;
}

//=============================================================================
// 影の破棄
//=============================================================================
void ReleaseShadow(int idxShadow)
{
	if(idxShadow >= 0 && idxShadow < MAX_SHADOW)
	{
		Shadow[idxShadow].use = false;
	}
}

//=============================================================================
// 位置の設定
//=============================================================================
void SetPositionShadow(int idxShadow, D3DXVECTOR3 pos)
{
	Shadow[idxShadow].pos = pos;
}

