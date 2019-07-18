//=============================================================================
//
// カメラ処理 [camera.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "camera.h"
#include "input.h"
#include "debugproc.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	VIEW_ANGLE			(D3DXToRadian(45.0f))	// 視野角
#define	VIEW_ASPECT			((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT)	// ビュー平面のアスペクト比
#define	VIEW_NEAR_Z			(10.0f)					// ビュー平面のNearZ値
#define	VIEW_FAR_Z			(1000.0f)				// ビュー平面のFarZ値
#define	VALUE_MOVE_CAMERA	(2.0f)					// カメラの移動量
#define	VALUE_ROTATE_CAMERA	(D3DX_PI * 0.01f)		// カメラの回転量

#define	INTERVAL_CAMERA_R	(12.5f)					// モデルの視線の先までの距離
#define	RATE_CHASE_CAMERA_P	(0.35f)					// カメラの視点への補正係数
#define	RATE_CHASE_CAMERA_R	(0.20f)					// カメラの注視点への補正係数

#define	CHASE_HEIGHT_P		(100.0f)				// 追跡時の視点の高さ
#define	CHASE_HEIGHT_R		(10.0f)					// 追跡時の注視点の高さ

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
D3DXVECTOR3		posCameraEye;				// カメラの視点
D3DXVECTOR3		posCameraAT;				// カメラの注視点
D3DXVECTOR3		posCameraUp;				// カメラの上方向
D3DXVECTOR3		posCameraEyeDest;			// カメラの視点の目的位置
D3DXVECTOR3		posCameraATDest;			// カメラの注視点の目的位置
D3DXVECTOR3		rotCamera;					// カメラの回転
float			lengthIntervalCamera;		// カメラの視点と注視点の距離
D3DXMATRIX		mtxView;					// ビューマトリックス
D3DXMATRIX		mtxProjection;				// プロジェクションマトリックス

//=============================================================================
// カメラの初期化
//=============================================================================
HRESULT InitCamera(void)
{
	posCameraEye = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	posCameraAT = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	posCameraUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	posCameraEyeDest = D3DXVECTOR3(0.0f, 100.0f, -200.0f);
	posCameraATDest = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	rotCamera = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	float vx,vz;
	vx = posCameraEye.x - posCameraAT.x;
	vz = posCameraEye.z - posCameraAT.z;
	lengthIntervalCamera = sqrtf(vx * vx + vz * vz);

	return S_OK;
}

//=============================================================================
// カメラの終了処理
//=============================================================================
void UninitCamera(void)
{
}

//=============================================================================
// カメラの更新処理
//=============================================================================
void UpdateCamera(void)
{
	if(GetKeyboardPress(DIK_A))
	{
		if(GetKeyboardPress(DIK_W))
		{// 左前移動
			posCameraEye.x -= cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			posCameraEye.z += sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else if(GetKeyboardPress(DIK_S))
		{// 左後移動
			posCameraEye.x -= cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			posCameraEye.z += sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else
		{// 左移動
			posCameraEye.x -= cosf(rotCamera.y) * VALUE_MOVE_CAMERA;
			posCameraEye.z += sinf(rotCamera.y) * VALUE_MOVE_CAMERA;
		}

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_D))
	{
		if(GetKeyboardPress(DIK_W))
		{// 右前移動
			posCameraEye.x += cosf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			posCameraEye.z -= sinf(rotCamera.y - D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else if(GetKeyboardPress(DIK_S))
		{// 右後移動
			posCameraEye.x += cosf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
			posCameraEye.z -= sinf(rotCamera.y + D3DX_PI * 0.25f) * VALUE_MOVE_CAMERA;
		}
		else
		{// 右移動
			posCameraEye.x += cosf(rotCamera.y) * VALUE_MOVE_CAMERA;
			posCameraEye.z -= sinf(rotCamera.y) * VALUE_MOVE_CAMERA;
		}

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_W))
	{// 前移動
		posCameraEye.x += sinf(rotCamera.y) * VALUE_MOVE_CAMERA;
		posCameraEye.z += cosf(rotCamera.y) * VALUE_MOVE_CAMERA;

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	else if(GetKeyboardPress(DIK_S))
	{// 後移動
		posCameraEye.x -= sinf(rotCamera.y) * VALUE_MOVE_CAMERA;
		posCameraEye.z -= cosf(rotCamera.y) * VALUE_MOVE_CAMERA;

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}

	if(GetKeyboardPress(DIK_Z))
	{// 視点旋回「左」
		rotCamera.y += VALUE_ROTATE_CAMERA;
		if(rotCamera.y > D3DX_PI)
		{
			rotCamera.y -= D3DX_PI * 2.0f;
		}

		posCameraEye.x = posCameraAT.x - sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraEye.z = posCameraAT.z - cosf(rotCamera.y) * lengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_C))
	{// 視点旋回「右」
		rotCamera.y -= VALUE_ROTATE_CAMERA;
		if(rotCamera.y < -D3DX_PI)
		{
			rotCamera.y += D3DX_PI * 2.0f;
		}

		posCameraEye.x = posCameraAT.x - sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraEye.z = posCameraAT.z - cosf(rotCamera.y) * lengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_Y))
	{// 視点移動「上」
		posCameraEye.y += VALUE_MOVE_CAMERA;
	}
	if(GetKeyboardPress(DIK_N))
	{// 視点移動「下」
		posCameraEye.y -= VALUE_MOVE_CAMERA;
	}

	if(GetKeyboardPress(DIK_Q))
	{// 注視点旋回「左」
		rotCamera.y -= VALUE_ROTATE_CAMERA;
		if(rotCamera.y < -D3DX_PI)
		{
			rotCamera.y += D3DX_PI*2.0f;
		}

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_E))
	{// 注視点旋回「右」
		rotCamera.y += VALUE_ROTATE_CAMERA;
		if(rotCamera.y > D3DX_PI)
		{
			rotCamera.y -= D3DX_PI*2.0f;
		}

		posCameraAT.x = posCameraEye.x + sinf(rotCamera.y) * lengthIntervalCamera;
		posCameraAT.z = posCameraEye.z + cosf(rotCamera.y) * lengthIntervalCamera;
	}
	if(GetKeyboardPress(DIK_T))
	{// 注視点移動「上」
		posCameraAT.y += VALUE_MOVE_CAMERA;
	}
	if(GetKeyboardPress(DIK_B))
	{// 注視点移動「下」
		posCameraAT.y -= VALUE_MOVE_CAMERA;
	}

}

//=============================================================================
// カメラの設定処理
//=============================================================================
void SetCamera(void)
{
	LPDIRECT3DDEVICE9 device = GetDevice();

	// ビューマトリックスの初期化
	D3DXMatrixIdentity(&mtxView);

	// ビューマトリックスの作成
	D3DXMatrixLookAtLH(&mtxView, 
						&posCameraEye,		// カメラの視点
						&posCameraAT,		// カメラの注視点
						&posCameraUp);		// カメラの上方向

	// ビューマトリックスの設定
	device->SetTransform(D3DTS_VIEW, &mtxView);


	// プロジェクションマトリックスの初期化
	D3DXMatrixIdentity(&mtxProjection);

	// プロジェクションマトリックスの作成
	D3DXMatrixPerspectiveFovLH(&mtxProjection,
								VIEW_ANGLE,			// 視野角
								VIEW_ASPECT,		// アスペクト比
								VIEW_NEAR_Z,		// ビュー平面のNearZ値
								VIEW_FAR_Z);		// ビュー平面のFarZ値

	// プロジェクションマトリックスの設定
	device->SetTransform(D3DTS_PROJECTION, &mtxProjection);
}

//=============================================================================
// カメラの向きの取得
//=============================================================================
D3DXVECTOR3 GetRotCamera(void)
{
	return rotCamera;
}

//=============================================================================
// ビューマトリックスの取得
//=============================================================================
D3DXMATRIX GetMtxView(void)
{
	return mtxView;
}

