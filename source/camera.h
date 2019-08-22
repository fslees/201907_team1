//=============================================================================
//
// カメラ処理 [camera.h]
// Author : 李尚ミン
//
//=============================================================================
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

//=============================================================================
// カメラデータクラスの定義
// posEye			: カメラの位置
// posAT			: カメラの注視点
//=============================================================================
struct CameraData
{
	D3DXVECTOR3		posEye;
	D3DXVECTOR3		posAT;
};


//=============================================================================
// カメラクラスの定義
//=============================================================================
class Camera
{
private:
	D3DXVECTOR3		posEye;				// カメラの視点
	D3DXVECTOR3		posAT;				// カメラの注視点
	D3DXVECTOR3		vecUp;				// カメラの上方向
	D3DXVECTOR3		rot;				// カメラの回転
	float			lengthInterval;		// カメラの視点と注視点の距離
	D3DXMATRIX		mtxView;			// ビューマトリックス
	D3DXMATRIX		mtxProjection;		// プロジェクションマトリックス

public:
	Camera(CameraData initData);

	void Update(void);
	void Set(void);

	D3DXVECTOR3	GetPosEye();
	D3DXMATRIX	GetMtxView();
	D3DXMATRIX	GetMtxProjection();
};


#endif
