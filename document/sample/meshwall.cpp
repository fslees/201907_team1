//=============================================================================
//
// メッシュ壁の処理 [meshwall.cpp]
// Author : 
//
//=============================================================================
#include "meshwall.h"
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MAX_MESH_WALL		(10)						// 壁の総数
#define	TEXTURE_FILENAME	"data/TEXTURE/wall000.jpg"	// 読み込むテクスチャファイル名
#define	VALUE_MOVE_WALL		(5.0f)						// 移動速度
#define	VALUE_ROTATE_WALL	(D3DX_PI * 0.001f)			// 回転速度

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9 D3DTexture = NULL;		// テクスチャ読み込み場所

typedef struct
{
	LPDIRECT3DVERTEXBUFFER9 D3DVtxBuff;		// 頂点バッファインターフェースへのポインタ
	LPDIRECT3DINDEXBUFFER9 D3DIdxBuff;		// インデックスバッファインターフェースへのポインタ

	D3DXMATRIX mtxWorld;					// ワールドマトリックス
	D3DXVECTOR3 pos;						// ポリゴン表示位置の中心座標
	D3DXVECTOR3 rot;						// ポリゴンの回転角
	int numBlockX, numBlockY;				// ブロック数
	int numVertex;							// 総頂点数	
	int numVertexIndex;						// 総インデックス数
	int numPolygon;							// 総ポリゴン数
	float blockSizeX, blockSizeY;			// ブロックサイズ
} MESH_WALL;

MESH_WALL MeshWall[MAX_MESH_WALL];			// メッシュ壁ワーク
int NumMeshField = 0;						// メッシュ壁の数

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitMeshWall(D3DXVECTOR3 pos, D3DXVECTOR3 rot, D3DXCOLOR col,
							int numBlockX, int numBlockY, float blockSizeX, float blockSizeZ)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	MESH_WALL *mesh;

	if(NumMeshField >= MAX_MESH_WALL)
	{
		return E_FAIL;
	}

	// テクスチャの読み込み
	if(!D3DTexture)
	{
		D3DXCreateTextureFromFile(device,				// デバイスへのポインタ
									TEXTURE_FILENAME,	// ファイルの名前
									&D3DTexture);		// 読み込むメモリー
	}

	mesh = &MeshWall[NumMeshField];
	NumMeshField++;

	// ポリゴン表示位置の中心座標を設定
	mesh->pos = pos;

	mesh->rot = rot;

	// ブロック数の設定
	mesh->numBlockX = numBlockX;
	mesh->numBlockY = numBlockY;

	// 頂点数の設定
	mesh->numVertex = (numBlockX + 1) * (numBlockY + 1);

	// インデックス数の設定
	mesh->numVertexIndex = (numBlockX + 1) * 2 * numBlockY + (numBlockY - 1) * 2;

	// ポリゴン数の設定
	mesh->numPolygon = numBlockX * numBlockY * 2 + (numBlockY - 1) * 4;

	// ブロックサイズの設定
	mesh->blockSizeX = blockSizeX;
	mesh->blockSizeY = blockSizeZ;

	// オブジェクトの頂点バッファを生成
    if(FAILED(device->CreateVertexBuffer(sizeof(VERTEX_3D) * mesh->numVertex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
												FVF_VERTEX_3D,					// 使用する頂点フォーマット
												D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
												&mesh->D3DVtxBuff,				// 頂点バッファインターフェースへのポインタ
												NULL)))							// NULLに設定
	{
        return E_FAIL;
	}

	// オブジェクトのインデックスバッファを生成
    if(FAILED(device->CreateIndexBuffer(sizeof(WORD) * mesh->numVertexIndex,	// 頂点データ用に確保するバッファサイズ(バイト単位)
												D3DUSAGE_WRITEONLY,				// 頂点バッファの使用法　
												D3DFMT_INDEX16,					// 使用するインデックスフォーマット
												D3DPOOL_MANAGED,				// リソースのバッファを保持するメモリクラスを指定
												&mesh->D3DIdxBuff,				// インデックスバッファインターフェースへのポインタ
												NULL)))							// NULLに設定
	{
        return E_FAIL;
	}

	{//頂点バッファの中身を埋める
		VERTEX_3D *vtx;
#if 0
		const float texSizeX = 1.0f / g_nNumBlockX;
		const float texSizeZ = 1.0f / g_nNumBlockY;
#else
		const float texSizeX = 1.0f;
		const float texSizeZ = 1.0f;
#endif

		// 頂点データの範囲をロックし、頂点バッファへのポインタを取得
		mesh->D3DVtxBuff->Lock( 0, 0, (void**)&vtx, 0 );

		for(int cntVtxY = 0; cntVtxY < (mesh->numBlockY + 1); cntVtxY++)
		{
			for(int cntVtxX = 0; cntVtxX < (mesh->numBlockX + 1); cntVtxX++)
			{
				// 頂点座標の設定
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].vtx.x = -(mesh->numBlockX / 2.0f) * mesh->blockSizeX + cntVtxX * mesh->blockSizeX;
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].vtx.y = mesh->numBlockY * mesh->blockSizeY - cntVtxY * mesh->blockSizeY;
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].vtx.z = 0.0f;

				// 法線の設定
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].nor = D3DXVECTOR3(0.0f, 0.0f, -1.0f);

				// 反射光の設定
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].diffuse = col;

				// テクスチャ座標の設定
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].tex.x = texSizeX * cntVtxX;
				vtx[cntVtxY * (mesh->numBlockX + 1) + cntVtxX].tex.y = texSizeZ * cntVtxY;
			}
		}

		// 頂点データをアンロックする
		mesh->D3DVtxBuff->Unlock();
	}

	{//インデックスバッファの中身を埋める
		WORD *idx;

		// インデックスデータの範囲をロックし、頂点バッファへのポインタを取得
		mesh->D3DIdxBuff->Lock( 0, 0, (void**)&idx, 0 );

		int cntIdx = 0;
		for(int cntVtxY = 0; cntVtxY < mesh->numBlockY; cntVtxY++)
		{
			if(cntVtxY > 0)
			{// 縮退ポリゴンのためのダブりの設定
				idx[cntIdx] = (cntVtxY + 1) * (mesh->numBlockX + 1);
				cntIdx++;
			}

			for(int cntVtxX = 0; cntVtxX < (mesh->numBlockX + 1); cntVtxX++)
			{
				idx[cntIdx] = (cntVtxY + 1) * (mesh->numBlockX + 1) + cntVtxX;
				cntIdx++;
				idx[cntIdx] = cntVtxY * (mesh->numBlockX + 1) + cntVtxX;
				cntIdx++;
			}

			if(cntVtxY < (mesh->numBlockY - 1))
			{// 縮退ポリゴンのためのダブりの設定
				idx[cntIdx] = cntVtxY * (mesh->numBlockX + 1) + mesh->numBlockX;
				cntIdx++;
			}
		}

		// インデックスデータをアンロックする
		mesh->D3DIdxBuff->Unlock();
	}



	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitMeshWall(void)
{
	MESH_WALL *mesh;
	int nCntMeshField;

	for(nCntMeshField = 0; nCntMeshField < NumMeshField; nCntMeshField++)
	{
		mesh = &MeshWall[nCntMeshField];

		if(mesh->D3DVtxBuff)
		{// 頂点バッファの開放
			mesh->D3DVtxBuff->Release();
			mesh->D3DVtxBuff = NULL;
		}

		if(mesh->D3DIdxBuff)
		{// インデックスバッファの開放
			mesh->D3DIdxBuff->Release();
			mesh->D3DIdxBuff = NULL;
		}
	}

	if(D3DTexture)
	{// テクスチャの開放
		D3DTexture->Release();
		D3DTexture = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateMeshWall(void)
{
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawMeshWall(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DXMATRIX mtxRot, mtxTranslate;

	MESH_WALL *mesh;
	int nCntMeshField;

	for(nCntMeshField = 0; nCntMeshField < NumMeshField; nCntMeshField++)
	{
		mesh = &MeshWall[nCntMeshField];

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mesh->mtxWorld);

		// 回転を反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, mesh->rot.y, mesh->rot.x, mesh->rot.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxRot);

		// 移動を反映
		D3DXMatrixTranslation(&mtxTranslate, mesh->pos.x, mesh->pos.y, mesh->pos.z);
		D3DXMatrixMultiply(&mesh->mtxWorld, &mesh->mtxWorld, &mtxTranslate);

		// ワールドマトリックスの設定
		device->SetTransform(D3DTS_WORLD, &mesh->mtxWorld);

		// 頂点バッファをレンダリングパイプラインに設定
		device->SetStreamSource(0, mesh->D3DVtxBuff, 0, sizeof(VERTEX_3D));

		// インデックスバッファをレンダリングパイプラインに設定
		device->SetIndices(mesh->D3DIdxBuff);

		// 頂点フォーマットの設定
		device->SetFVF(FVF_VERTEX_3D);

		// テクスチャの設定
		device->SetTexture(0, D3DTexture);

		// ポリゴンの描画
		device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, mesh->numVertex, 0, mesh->numPolygon);
	}
}

