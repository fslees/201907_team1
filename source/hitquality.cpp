//=============================================================================
//
// ヒット時の精度表示処理 [hitqualety.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "hitquality.h"
//*****************************************************************************
// マクロ定義
//*****************************************************************************
// テクスチャーデータ
#define TEXTURE_PERFECT		("data/TEXTURE/perfect.png")
#define TEXTURE_GREAT		("data/TEXTURE/great.png")
#define TEXTURE_GOOD		("data/TEXTURE/good.png")
// 頂点サイズ
#define TEXTURE_SIZE_X		(100.0f)
#define TEXTURE_SIZE_Y		(50.0f)
// 初期位置
#define INIT_POS_X			(0.0f)
#define INIT_POS_Y			(0.0f)
#define INIT_POS_Z			(-50.0f)

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************

//*****************************************************************************
// グローバル変数
//*****************************************************************************

//*****************************************************************************
// コンストラクタ
//*****************************************************************************
HitQualety::HitQualety()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();

	// 変数の初期化
	texNum = PERFECT;
	pos = D3DXVECTOR3(INIT_POS_X, INIT_POS_Y, INIT_POS_Z);
	rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
	use = false;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
								TEXTURE_PERFECT,	// ファイルの名前
								&D3DTexture[PERFECT]);	// 読み込むメモリー
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
								TEXTURE_GREAT,		// ファイルの名前
								&D3DTexture[GREAT]);	// 読み込むメモリー
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
								TEXTURE_GOOD,		// ファイルの名前
								&D3DTexture[GOOD]);	// 読み込むメモリー

	//頂点の作成
	MakeVertex(Device);
}

//*****************************************************************************
// ゲームの終了
//*****************************************************************************
HitQualety::~HitQualety()
{
	for (int i = 0; i < TEX_MAX; i++)
	{
		if (D3DTexture[i] != NULL)
		{// テクスチャの開放
			D3DTexture[i]->Release();
			D3DTexture[i] = NULL;
		}
	}
}

//*****************************************************************************
// ゲームの更新
//*****************************************************************************
void HitQualety:: Update()
{
	SetSclAnim();
}

//*****************************************************************************
// リザルト画面の描画
//*****************************************************************************
void HitQualety::Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxView, mtxScale, mtxTranslate;

	// Z比較なし
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);

	// αテストを有効に
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_ALPHAREF, 100);
	pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);

	// ラインティングを無効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	if (use)
	{
		// ビューマトリックスを取得
		mtxView = camera.GetMtxView();

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxWorld);

		// ポリゴンを正面に向ける
		mtxWorld._11 = mtxView._11;
		mtxWorld._12 = mtxView._21;
		mtxWorld._13 = mtxView._31;
		mtxWorld._21 = mtxView._12;
		mtxWorld._22 = mtxView._22;
		mtxWorld._23 = mtxView._32;
		mtxWorld._31 = mtxView._13;
		mtxWorld._32 = mtxView._23;
		mtxWorld._33 = mtxView._33;

		// スケールを反映
		D3DXMatrixScaling(&mtxScale, scl.x,
			scl.y,
			scl.z);
		D3DXMatrixMultiply(&mtxWorld,
			&mtxWorld, &mtxScale);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, pos.x,
			pos.y,
			pos.z);
		D3DXMatrixMultiply(&mtxWorld,
			&mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

		// 頂点バッファをデバイスのデータストリームにバインド
		pDevice->SetStreamSource(0, D3DVtxBuff, 0, sizeof(VERTEX_3D));

		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		pDevice->SetTexture(0, D3DTexture[texNum]);

		// ポリゴンの描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, NUM_VERTEX, NUM_POLYGON);
	}

	// ラインティングを有効にする
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);

	// αテストを無効
	pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);

	// Z比較あり
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
}

//=========================================
//頂点の作成
//=========================================
HRESULT HitQualety::MakeVertex(LPDIRECT3DDEVICE9 pDevice)
{
	// オブジェクトの頂点バッファを生成
	if (FAILED(pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX,	// 頂点データ用に確保するバッファサイズ(バイト単位)
		D3DUSAGE_WRITEONLY,			// 頂点バッファの使用法　
		FVF_VERTEX_3D,				// 使用する頂点フォーマット
		D3DPOOL_MANAGED,			// リソースのバッファを保持するメモリクラスを指定
		&D3DVtxBuff,	// 頂点バッファインターフェースへのポインタ
		NULL)))						// NULLに設定
	{
		return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *pVtx;

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuff->Lock(0, 0, (void**)&pVtx, 0);

		// 頂点座標の設定
		pVtx[0].vtx = D3DXVECTOR3(-TEXTURE_SIZE_X / 2, -TEXTURE_SIZE_Y / 2, 0.0f);
		pVtx[1].vtx = D3DXVECTOR3(-TEXTURE_SIZE_X / 2, TEXTURE_SIZE_Y / 2, 0.0f);
		pVtx[2].vtx = D3DXVECTOR3(TEXTURE_SIZE_X / 2, -TEXTURE_SIZE_Y / 2, 0.0f);
		pVtx[3].vtx = D3DXVECTOR3(TEXTURE_SIZE_X / 2, TEXTURE_SIZE_Y / 2, 0.0f);

		// 法線の設定
		pVtx[0].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[1].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[2].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		pVtx[3].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

		// 反射光の設定
		pVtx[0].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[1].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[2].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		pVtx[3].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

		// テクスチャ座標の設定
		pVtx[0].tex = D3DXVECTOR2(0.0f, 1.0f);
		pVtx[1].tex = D3DXVECTOR2(0.0f, 0.0f);
		pVtx[2].tex = D3DXVECTOR2(1.0f, 1.0f);
		pVtx[3].tex = D3DXVECTOR2(1.0f, 0.0f);

		// 頂点データをアンロックする
		D3DVtxBuff->Unlock();
	}

	return S_OK;
}


//=========================================
// 拡大アニメーション
//=========================================
void HitQualety::SetSclAnim()
{
	if (use)
	{
		scl.x += 0.1f;
		scl.y += 0.1f;
	}

	if (scl == D3DXVECTOR3(1.0f, 1.0f, 1.0f))
	{
		use = false;
	}
}