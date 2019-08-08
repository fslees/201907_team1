//=============================================================================
//
// メッシュ地面の処理 [meshfield.cpp]
// Author : 
//
//=============================================================================
#include "meshfield.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	TEXTURE_FILENAME	"data/TEXTURE/field004.jpg"		// 読み込むテクスチャファイル名

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 D3DTextureField;				// テクスチャ読み込み場所
LPDIRECT3DVERTEXBUFFER9 D3DVtxBuffField;		// 頂点バッファインターフェースへのポインタ
LPDIRECT3DINDEXBUFFER9 D3DIdxBuffField;			// インデックスバッファインターフェースへのポインタ

D3DXMATRIX MtxWorldField;						// ワールドマトリックス
D3DXVECTOR3 PosField;							// ポリゴン表示位置の中心座標
D3DXVECTOR3 RotField;							// ポリゴンの回転角

int		NumBlockXField, NumBlockZField;			// ブロック数
int		NumVertexField;							// 総頂点数	
int		NumVertexIndexField;					// 総インデックス数
int		NumPolygonField;						// 総ポリゴン数
float	BlockSizeXField, BlockSizeZField;		// ブロックサイズ

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMeshField(D3DXVECTOR3 pos, D3DXVECTOR3 rot,
							int numBlockX, int numBlockZ, float blockSizeX, float blockSizeZ)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	// ポリゴン表示位置の中心座標を設定
	PosField = pos;

	RotField = rot;

	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,					// デバイスへのポインタ
								TEXTURE_FILENAME,		// ファイルの名前
								&D3DTextureField);		// 読み込むメモリー

	// ブロック数の設定
	NumBlockXField = numBlockX;
	NumBlockZField = numBlockZ;

	// 頂点数の設定
	NumVertexField = (numBlockX + 1) * (numBlockZ + 1);
	int numVertexXField = numBlockX + 1;
	int numVertexZField = numBlockZ + 1;


	// インデックス数の設定
	NumVertexIndexField = (numBlockX + 1) * 2 * numBlockZ + (numBlockZ - 1) * 2;

	// ポリゴン数の設定
	NumPolygonField = numBlockX * numBlockZ * 2 + (numBlockZ - 1) * 4;

	// ブロックサイズの設定
	BlockSizeXField = blockSizeX;
	BlockSizeZField = blockSizeZ;

	// オブジェクトの頂点バッファを生成
    if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * NumVertexField,		// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
												FVF_VERTEX_3D,						// 使用する頂点フォーマット
												D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
												&D3DVtxBuffField,					// 頂点バッファインターフェースへのポインタ
												NULL)))								// NULLに設定
	{
        return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
    if(FAILED(device->CreateIndexBuffer(sizeof(WORD) * NumVertexIndexField,			// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,					// 頂点バッファの使用法　
												D3DFMT_INDEX16,						// 使用するインデックスフォーマット
												D3DPOOL_MANAGED,					// リソースのバッファを保持するメモリクラスを指定
												&D3DIdxBuffField,					// インデックスバッファインターフェースへのポインタ
												NULL)))								// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *vtx;
#if 0
		const float texSizeX = 1.0f / numBlockX;
		const float texSizeZ = 1.0f / numBlockZ;
#else
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;
#endif

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		D3DVtxBuffField->Lock( 0, 0, (void**)&vtx, 0 );

		for(int cntVtxZ = 0; cntVtxZ < numVertexZField; cntVtxZ++)
		{
			for(int cntVtxX = 0; cntVtxX < numVertexXField; cntVtxX++)
			{
				int no = cntVtxZ * numVertexXField + cntVtxX;
				// 頂点座標の設定
				vtx[no].vtx.x = -(NumBlockXField / 2.0f) * BlockSizeXField + cntVtxX * BlockSizeXField;
				vtx[no].vtx.y = 0.0f;
				vtx[no].vtx.z = (NumBlockZField / 2.0f) * BlockSizeZField - cntVtxZ * BlockSizeZField;

				// 法線の設定
				vtx[no].nor = D3DXVECTOR3(0.0f, 1.0, 0.0f);

				// 反射光の設定
				vtx[no].diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

				// テクスチャ座標の設定
				vtx[no].tex.x = texSizeX * cntVtxX;
				vtx[no].tex.y = texSizeZ * cntVtxZ;
			}
		}

		// 頂点データをアンロックする
		D3DVtxBuffField->Unlock();
	}

	{//インデックスバッファの中身を埋める
		WORD *idx;

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		D3DIdxBuffField->Lock( 0, 0, (void**)&idx, 0 );

		int cntIdx = 0;
		for(int cntVtxZ = 0; cntVtxZ < NumBlockZField; cntVtxZ++)
		{
			if(cntVtxZ > 0)
			{// 縮退ポリゴンのためのダブりの設定
				idx[cntIdx] = (cntVtxZ + 1) * (NumBlockXField + 1);
				cntIdx++;
			}

			for(int cntVtxX = 0; cntVtxX < (NumBlockXField + 1); cntVtxX++)
			{
				idx[cntIdx] = (cntVtxZ + 1) * (NumBlockXField + 1) + cntVtxX;
				cntIdx++;
				idx[cntIdx] = cntVtxZ * (NumBlockXField + 1) + cntVtxX;
				cntIdx++;
			}

			if(cntVtxZ < (NumBlockZField - 1))
			{// 縮退ポリゴンのためのダブりの設定
				idx[cntIdx] = cntVtxZ * (NumBlockXField + 1) + NumBlockXField;
				cntIdx++;
			}
		}

		// インデックスデータをアンロックする
		D3DIdxBuffField->Unlock();
	}

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshField(void)
{
	if(D3DVtxBuffField)
	{// 頂点バッファの開放
		D3DVtxBuffField->Release();
		D3DVtxBuffField = NULL;
	}

	if(D3DIdxBuffField)
	{// インデックスバッファの開放
		D3DIdxBuffField->Release();
		D3DIdxBuffField = NULL;
	}

	if(D3DTextureField)
	{// テクスチャの開放
		D3DTextureField->Release();
		D3DTextureField = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshField(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshField(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&MtxWorldField);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, RotField.y, RotField.x, RotField.z);
	D3DXMatrixMultiply(&MtxWorldField, &MtxWorldField, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, PosField.x, PosField.y, PosField.z);
	D3DXMatrixMultiply(&MtxWorldField, &MtxWorldField, &mtxTranslate);

	// ワールドマトリックスの設定
	device->SetTransform(D3DTS_WORLD, &MtxWorldField);

	// 頂点バッファをレンダリングパイプラインに設定
	device->SetStreamSource(0, D3DVtxBuffField, 0, sizeof(VERTEX_3D));

	// インデックスバッファをレンダリングパイプラインに設定
	device->SetIndices(D3DIdxBuffField);

	// 頂点フォーマットの設定
	device->SetFVF(FVF_VERTEX_3D);

	// テクスチャの設定
	device->SetTexture(0, D3DTextureField);

	// ポリゴンの描画
	device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, NumVertexField, 0, NumPolygonField);
}

