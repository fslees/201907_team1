//=============================================================================
//
// スコアの実装 [score.cpp]
// Author : 染矢　晃介
//
//=============================================================================
#include "score.h"
#include "2Dtexmanager.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************


//*****************************************************************************
// コンストラクタ　スコアの読み込み
//*****************************************************************************
Score::Score()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
								&scoreTex);		// 読み込むメモリー

	//表示位置の初期化
	pos = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);

	//頂点の作成
	MakeVertex(pos);

	//スコアの実数値の初期化
	score = SCORE_INITIAL;

	//スコアの初期化
	SetScore(score);

}

//=============================================================================
//デストラクタ
//=============================================================================
Score::~Score()
{
	if (scoreTex != NULL)
	{// テクスチャの開放
		scoreTex->Release();
		scoreTex = NULL;
	}
}

//*****************************************************************************
// ゲームの終了
//*****************************************************************************
void Score::UninitScore()
{
	
}

//*****************************************************************************
// ゲームの更新
//*****************************************************************************
void  Score::UpdateScore()
{
	
}

//*****************************************************************************
// ゲーム画面の描画
//*****************************************************************************
void  Score::DrawScore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, scoreTex);

	
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexScore[i], sizeof(VERTEX_2D));
	}
}


//=======================================================
// 頂点の作成
// 引数:頂点情報ワーク
// 引数:標示位置
//=======================================================
void Score::MakeVertex(D3DXVECTOR3 pos)
{
	// 桁数分処理する
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点座標の設定
		vertexScore[i][0].vtx.x = -SCORE_WIDE * i + pos.x;
		vertexScore[i][0].vtx.y = pos.y;
		vertexScore[i][0].vtx.z = 0.0f;
		vertexScore[i][1].vtx.x = -SCORE_WIDE * i + pos.x + TEXTURE_SCORE_SIZE_X;
		vertexScore[i][1].vtx.y = pos.y;
		vertexScore[i][1].vtx.z = 0.0f;
		vertexScore[i][2].vtx.x = -SCORE_WIDE * i + pos.x;
		vertexScore[i][2].vtx.y = pos.y + TEXTURE_SCORE_SIZE_Y;
		vertexScore[i][2].vtx.z = 0.0f;
		vertexScore[i][3].vtx.x = -SCORE_WIDE * i + pos.x + TEXTURE_SCORE_SIZE_X;
		vertexScore[i][3].vtx.y = pos.y + TEXTURE_SCORE_SIZE_Y;
		vertexScore[i][3].vtx.z = 0.0f;

		// rhwの設定
		vertexScore[i][0].rhw =
		vertexScore[i][1].rhw =
		vertexScore[i][2].rhw =
		vertexScore[i][3].rhw = 1.0f;

		// 反射光の設定
		vertexScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		vertexScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vertexScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vertexScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vertexScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}


}


//===================================
// スコアのセット
// 引数:表示するスコア
//==================================
void Score::SetScore(int num)
{
	
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(num % 10);
		vertexScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		vertexScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		vertexScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		vertexScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		num /= 10;
	}
}


//==========================================
//スコア情報のGet関数
//戻り値：表示しているスコアの数字
//==========================================
int Score::GetScore()
{
	return score;
}