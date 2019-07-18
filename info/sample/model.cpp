//=============================================================================
//
// モデル処理 [model.cpp]
// Author : 
//
//=============================================================================
#include "model.h"
#include "camera.h"
#include "input.h"
#include "shadow.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	MODEL_AIRPLANE		"data/MODEL/airplane000.x"	// 読み込むモデル名
#define	VALUE_MOVE_MODEL	(0.50f)						// 移動速度
#define	RATE_MOVE_MODEL		(0.20f)						// 移動慣性係数
#define	VALUE_ROTATE_MODEL	(D3DX_PI * 0.05f)			// 回転速度
#define	RATE_ROTATE_MODEL	(0.20f)						// 回転慣性係数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECT3DTEXTURE9	D3DTextureModel;		// テクスチャ読み込み場所
LPD3DXMESH			D3DXMeshModel;			// ID3DXMeshインターフェイスへのポインタ
LPD3DXBUFFER		D3DXBuffMatModel;		// メッシュのマテリアル情報を格納
DWORD				NumMatModel;			// 属性情報の総数

D3DXMATRIX			MtxWorldModel;			// ワールドマトリックス
D3DXVECTOR3			PosModel;				// 現在の位置
D3DXVECTOR3			MoveModel;				// 移動量
D3DXVECTOR3			RotModel;				// 現在の向き
D3DXVECTOR3			RotDestModel;			// 目的の向き

int					IdxShadow;				// 影ID
float				SizeShadow;				// 影のサイズ
D3DXCOLOR			ColShadow;				// 影の色

//=============================================================================
// 初期化処理
//=============================================================================
HRESULT InitModel(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	D3DTextureModel = NULL;
	D3DXMeshModel = NULL;
	D3DXBuffMatModel = NULL;

	PosModel = D3DXVECTOR3(0.0f, 20.0f, 0.0f);
	MoveModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RotModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	RotDestModel = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// Xファイルの読み込み
	if(FAILED(D3DXLoadMeshFromX(MODEL_AIRPLANE,
								D3DXMESH_SYSTEMMEM,
								device,
								NULL,
								&D3DXBuffMatModel,
								NULL,
								&NumMatModel,
								&D3DXMeshModel)))
	{
		return E_FAIL;
	}

#if 0
	// テクスチャの読み込み
	D3DXCreateTextureFromFile(device,					// デバイスへのポインタ
								TEXTURE_FILENAME,		// ファイルの名前
								&D3DTextureModel);		// 読み込むメモリー
#endif

	// 影の生成
	IdxShadow = CreateShadow(PosModel, 25.0f, 25.0f);

	SizeShadow = 25.0f;
	ColShadow = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);

	return S_OK;
}

//=============================================================================
// 終了処理
//=============================================================================
void UninitModel(void)
{
	if(D3DTextureModel != NULL)
	{// テクスチャの開放
		D3DTextureModel->Release();
		D3DTextureModel = NULL;
	}

	if(D3DXMeshModel != NULL)
	{// メッシュの開放
		D3DXMeshModel->Release();
		D3DXMeshModel = NULL;
	}

	if(D3DXBuffMatModel != NULL)
	{// マテリアルの開放
		D3DXBuffMatModel->Release();
		D3DXBuffMatModel = NULL;
	}
}

//=============================================================================
// 更新処理
//=============================================================================
void UpdateModel(void)
{
	D3DXVECTOR3 rotCamera;
	float diffRotY;

	// カメラの向き取得
	rotCamera = GetRotCamera();

	if(GetKeyboardPress(DIK_LEFT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// 左前移動
			MoveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y + D3DX_PI * 0.75f;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// 左後移動
			MoveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y + D3DX_PI * 0.25f;
		}
		else
		{// 左移動
			MoveModel.x -= sinf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y + D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y + D3DX_PI * 0.50f;
		}
	}
	else if(GetKeyboardPress(DIK_RIGHT))
	{
		if(GetKeyboardPress(DIK_UP))
		{// 右前移動
			MoveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.75f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y - D3DX_PI * 0.75f;
		}
		else if(GetKeyboardPress(DIK_DOWN))
		{// 右後移動
			MoveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y - D3DX_PI * 0.25f;
		}
		else
		{// 右移動
			MoveModel.x -= sinf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;
			MoveModel.z -= cosf(rotCamera.y - D3DX_PI * 0.50f) * VALUE_MOVE_MODEL;

			RotDestModel.y = rotCamera.y - D3DX_PI * 0.50f;
		}
	}
	else if(GetKeyboardPress(DIK_UP))
	{// 前移動
		MoveModel.x -= sinf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;
		MoveModel.z -= cosf(D3DX_PI + rotCamera.y) * VALUE_MOVE_MODEL;

		RotDestModel.y = D3DX_PI + rotCamera.y;
	}
	else if(GetKeyboardPress(DIK_DOWN))
	{// 後移動
		MoveModel.x -= sinf(rotCamera.y) * VALUE_MOVE_MODEL;
		MoveModel.z -= cosf(rotCamera.y) * VALUE_MOVE_MODEL;

		RotDestModel.y = rotCamera.y;
	}

	if(GetKeyboardPress(DIK_LSHIFT))
	{// 左回転
		RotDestModel.y -= VALUE_ROTATE_MODEL;
		if(RotDestModel.y < -D3DX_PI)
		{
			RotDestModel.y += D3DX_PI * 2.0f;
		}
	}
	if(GetKeyboardPress(DIK_RSHIFT))
	{// 右回転
		RotDestModel.y += VALUE_ROTATE_MODEL;
		if(RotDestModel.y > D3DX_PI)
		{
			RotDestModel.y -= D3DX_PI * 2.0f;
		}
	}

	if(GetKeyboardPress(DIK_I))
	{// 上昇
		MoveModel.y += VALUE_MOVE_MODEL * 0.5f;

		if(PosModel.y < 75.0f)
		{
			SizeShadow += 0.2f;
			ColShadow.a -= 0.004f;
		}
	}
	if(GetKeyboardPress(DIK_K))
	{// 下降
		MoveModel.y -= VALUE_MOVE_MODEL * 0.5f;

		if(PosModel.y > 5.0f)
		{
			SizeShadow -= 0.2f;
			ColShadow.a += 0.004f;
		}
	}

	// 目的の角度までの差分
	diffRotY = RotDestModel.y - RotModel.y;
	if(diffRotY > D3DX_PI)
	{
		diffRotY -= D3DX_PI * 2.0f;
	}
	if(diffRotY < -D3DX_PI)
	{
		diffRotY += D3DX_PI * 2.0f;
	}

	// 目的の角度まで慣性をかける
	RotModel.y += diffRotY * RATE_ROTATE_MODEL;
	if(RotModel.y > D3DX_PI)
	{
		RotModel.y -= D3DX_PI * 2.0f;
	}
	if(RotModel.y < -D3DX_PI)
	{
		RotModel.y += D3DX_PI * 2.0f;
	}

	/// 位置移動
	PosModel.x += MoveModel.x;
	PosModel.y += MoveModel.y;
	if(PosModel.y < 5.0f)
	{
		PosModel.y = 5.0f;
	}
	if(PosModel.y > 75.0f)
	{
		PosModel.y = 75.0f;
	}
	PosModel.z += MoveModel.z;

	// 移動量に慣性をかける
	MoveModel.x += (0.0f - MoveModel.x) * RATE_MOVE_MODEL;
	MoveModel.y += (0.0f - MoveModel.y) * RATE_MOVE_MODEL;
	MoveModel.z += (0.0f - MoveModel.z) * RATE_MOVE_MODEL;

	if(PosModel.x < -310.0f)
	{
		PosModel.x = -310.0f;
	}
	if(PosModel.x > 310.0f)
	{
		PosModel.x = 310.0f;
	}
	if(PosModel.z < -310.0f)
	{
		PosModel.z = -310.0f;
	}
	if(PosModel.z > 310.0f)
	{
		PosModel.z = 310.0f;
	}

	// 影の位置設定
	SetPositionShadow(IdxShadow, D3DXVECTOR3(PosModel.x, 0.1f, PosModel.z));

	SetVertexShadow(IdxShadow, SizeShadow, SizeShadow);
	SetColorShadow(IdxShadow, ColShadow);

	PrintDebugProc("[飛行機の位置  ：(%f : %f : %f)]\n", PosModel.x, PosModel.y, PosModel.z);
	PrintDebugProc("[飛行機の向き  ：(%f) < 目的の向き:(%f) >]\n", RotModel.y, RotDestModel.y);
	PrintDebugProc("\n");

	PrintDebugProc("*** 飛行機操作 ***\n");
	PrintDebugProc("前移動 : ↑\n");
	PrintDebugProc("後移動 : ↓\n");
	PrintDebugProc("左移動 : ←\n");
	PrintDebugProc("右移動 : →\n");
	PrintDebugProc("上昇   : Ｉ\n");
	PrintDebugProc("下降   : Ｋ\n");
	PrintDebugProc("左旋回 : LSHIFT\n");
	PrintDebugProc("右旋回 : RSHIFT\n");
}

//=============================================================================
// 描画処理
//=============================================================================
void DrawModel(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();
	D3DXMATRIX mtxRot, mtxTranslate;
	D3DXMATERIAL *D3DXMat;
	D3DMATERIAL9 matDef;

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&MtxWorldModel);

	// 回転を反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, RotModel.y, RotModel.x, RotModel.z);
	D3DXMatrixMultiply(&MtxWorldModel, &MtxWorldModel, &mtxRot);

	// 移動を反映
	D3DXMatrixTranslation(&mtxTranslate, PosModel.x, PosModel.y, PosModel.z);
	D3DXMatrixMultiply(&MtxWorldModel, &MtxWorldModel, &mtxTranslate);

	// ワールドマトリックスの設定
	device->SetTransform(D3DTS_WORLD, &MtxWorldModel);

	// 現在のマテリアルを取得
	device->GetMaterial(&matDef);

	// マテリアル情報に対するポインタを取得
	D3DXMat = (D3DXMATERIAL*)D3DXBuffMatModel->GetBufferPointer();

	for(int nCntMat = 0; nCntMat < (int)NumMatModel; nCntMat++)
	{
		// マテリアルの設定
		device->SetMaterial(&D3DXMat[nCntMat].MatD3D);

		// テクスチャの設定
		device->SetTexture(0, D3DTextureModel);

		// 描画
		D3DXMeshModel->DrawSubset(nCntMat);
	}

	// マテリアルをデフォルトに戻す
	device->SetMaterial(&matDef);
}

//=============================================================================
// 位置取得
//=============================================================================
D3DXVECTOR3 GetPositionModel(void)
{
	return PosModel;
}

//=============================================================================
// 向き取得
//=============================================================================
D3DXVECTOR3 GetRotationModel(void)
{
	return RotModel;
}

//=============================================================================
// 目的の向き取得
//=============================================================================
D3DXVECTOR3 GetRotationDestModel(void)
{
	return RotDestModel;
}
