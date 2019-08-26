//======================================
// ノーツの描画処理[noteview.cpp]
// Author : 染矢　晃介
//======================================
#include "noteview.h"
#include "note.h"

//=====================================
//グローバル変数
//=====================================
LPD3DXBUFFER		D3DXBuffMatNote;	    // マテリアル情報へのポインタ
DWORD				NumMatNote;				// マテリアル情報の数
LPD3DXMESH			D3DXMeshNote;		    // メッシュ情報へのポインタ
LPDIRECT3DTEXTURE9	D3DTextureNote;			// テクスチャへのポインタ


//=====================================
//コンストラクタ
//=====================================
NoteView::NoteView()
{
	//初期化
	LPD3DXBUFFER		D3DXBuffMatNote = NULL;	    // マテリアル情報へのポインタ
	DWORD				NumMatNote = 0;				// マテリアル情報の数
	LPD3DXMESH			D3DXMeshNote = NULL;		// メッシュ情報へのポインタ
	LPDIRECT3DTEXTURE9	D3DTextureNote = NULL;		// テクスチャへのポインタ
	LPDIRECT3DDEVICE9 pDevice = GetDevice();


	// Xファイルの読み込み
	if (FAILED(D3DXLoadMeshFromX(NOTE_MODEL,			// 読み込むモデルファイル名(Xファイル)
								D3DXMESH_SYSTEMMEM,		// メッシュの作成オプションを指定
								pDevice,				// IDirect3DDevice9インターフェイスへのポインタ
								NULL,					// 隣接性データを含むバッファへのポインタ
								&D3DXBuffMatNote,		// マテリアルデータを含むバッファへのポインタ
								NULL,					// エフェクトインスタンスの配列を含むバッファへのポインタ
								&NumMatNote,			// D3DXMATERIAL構造体の数
								&D3DXMeshNote)))		// ID3DXMeshインターフェイスへのポインタのアドレス
	{
		E_FAIL;
	}

}

//=====================================
//デストラクタ
//=====================================
NoteView :: ~NoteView()
{
	if (D3DTextureNote != NULL)
	{// テクスチャの開放
		D3DTextureNote->Release();
		D3DTextureNote = NULL;
	}

	if (D3DXMeshNote != NULL)
	{// メッシュの開放
		D3DXMeshNote->Release();
		D3DXMeshNote = NULL;
	}

	if (D3DXBuffMatNote != NULL)
	{// マテリアルの開放
		D3DXBuffMatNote->Release();
		D3DXBuffMatNote = NULL;
	}
}

//=====================================
//描画処理
//=====================================
void NoteView::Draw()
{
	//Noteから情報をGet
	D3DXVECTOR3 pos = note->GetPos();
	D3DXVECTOR3 scl = note->GetScl();
	D3DXMATRIX  mtxWorld = note->GetMtxWorld();

	//
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	D3DXMATRIX mtxScl, mtxRot, mtxTranslate;
	D3DXMATERIAL *pD3DXMat;
	D3DMATERIAL9 matDef;
	

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxWorld);

	// スケールを反映
	D3DXMatrixScaling(&mtxScl, scl.x, scl.y, scl.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	// 回転を反映(現状は回転なし)
	/*D3DXMatrixRotationYawPitchRoll(&mtxRot, note->rot.y, note->rot.x, note->rot.z);
	D3DXMatrixMultiply(&note->mtxWorld, &note->mtxWorld, &mtxRot);*/

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, pos.x,pos.y, pos.z);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxTranslate);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	pD3DXMat = (D3DXMATERIAL*)D3DXBuffMatNote->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)NumMatNote; nCntMat++)
	{
		// マテリアルの設定
		pDevice->SetMaterial(&pD3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		pDevice->SetTexture(0, D3DTextureNote);

		// 描画
		D3DXMeshNote->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	pDevice->SetMaterial(&matDef);
}

