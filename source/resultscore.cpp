//=============================================================================
//
// リザルト用スコアの実装 [resultscore.cpp]
// Author : 染矢　晃介
//
//=============================================================================
#include "resultscore.h"
#include "score.h"

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
Resultscore::Resultscore()
{
	LPDIRECT3DDEVICE9 Device = GetDevice();


	// テクスチャの読み込み
	D3DXCreateTextureFromFile(Device,				// デバイスへのポインタ
								TEXTURE_SCORE,		// ファイルの名前
									&resultScoreTex);// 読み込むメモリー

						//表示位置の初期化
	pos = D3DXVECTOR3((float)SCORE_POS_X, (float)SCORE_POS_Y, 0.0f);

	//頂点の作成
	MakeVertex(pos);

	//スコアの実数値の初期化
	resultScoreNum = GetScore();

	//スコアの初期化
	SetResultScore(resultScoreNum);

}

//=============================================================================
//デストラクタ
//=============================================================================
Resultscore::~Resultscore()
{
	if (resultScoreTex != NULL)
	{// テクスチャの開放
		resultScoreTex->Release();
		resultScoreTex = NULL;
	}
}

//*****************************************************************************
// ゲームの終了
//*****************************************************************************
void Resultscore::UninitResultScore()
{
	
}

//*****************************************************************************
// ゲームの更新
//*****************************************************************************
void  Resultscore::UpdateResultScore()
{

}

//*****************************************************************************
// ゲーム画面の描画
//*****************************************************************************
void  Resultscore::DrawResultScore()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// テクスチャの設定
	pDevice->SetTexture(0, resultScoreTex);


	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点フォーマットの設定
		pDevice->SetFVF(FVF_VERTEX_2D);

		// ポリゴンの描画
		pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, NUM_POLYGON, vertexResultScore[i], sizeof(VERTEX_2D));
	}
}


//=======================================================
// 頂点の作成
// 引数:頂点情報ワーク
// 引数:標示位置
//=======================================================
void Resultscore::MakeVertex(D3DXVECTOR3 pos)
{
	// 桁数分処理する
	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// 頂点座標の設定
		vertexResultScore[i][0].vtx.x = -SCORE_WIDE * i + pos.x;
		vertexResultScore[i][0].vtx.y = pos.y;
		vertexResultScore[i][0].vtx.z = 0.0f;
		vertexResultScore[i][1].vtx.x = -SCORE_WIDE * i + pos.x + TEXTURE_SCORE_SIZE_X;
		vertexResultScore[i][1].vtx.y = pos.y;
		vertexResultScore[i][1].vtx.z = 0.0f;
		vertexResultScore[i][2].vtx.x = -SCORE_WIDE * i + pos.x;
		vertexResultScore[i][2].vtx.y = pos.y + TEXTURE_SCORE_SIZE_Y;
		vertexResultScore[i][2].vtx.z = 0.0f;
		vertexResultScore[i][3].vtx.x = -SCORE_WIDE * i + pos.x + TEXTURE_SCORE_SIZE_X;
		vertexResultScore[i][3].vtx.y = pos.y + TEXTURE_SCORE_SIZE_Y;
		vertexResultScore[i][3].vtx.z = 0.0f;

		// rhwの設定
		vertexResultScore[i][0].rhw =
		vertexResultScore[i][1].rhw =
		vertexResultScore[i][2].rhw =
		vertexResultScore[i][3].rhw = 1.0f;

		// 反射光の設定
		vertexResultScore[i][0].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexResultScore[i][1].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexResultScore[i][2].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);
		vertexResultScore[i][3].diffuse = D3DCOLOR_RGBA(255, 255, 255, 255);

		// テクスチャ座標の設定
		vertexResultScore[i][0].tex = D3DXVECTOR2(0.0f, 0.0f);
		vertexResultScore[i][1].tex = D3DXVECTOR2(1.0f, 0.0f);
		vertexResultScore[i][2].tex = D3DXVECTOR2(0.0f, 1.0f);
		vertexResultScore[i][3].tex = D3DXVECTOR2(1.0f, 1.0f);
	}


}


//===================================
// スコアのセット
// 引数:表示するスコア
//==================================
void Resultscore::SetResultScore(int num)
{

	resultScoreNum = num;

	for (int i = 0; i < SCORE_DIGIT; i++)
	{
		// テクスチャ座標の設定
		float x = (float)(resultScoreNum % 10);
		vertexResultScore[i][0].tex = D3DXVECTOR2(0.1f * x, 0.0f);
		vertexResultScore[i][1].tex = D3DXVECTOR2(0.1f * (x + 1), 0.0f);
		vertexResultScore[i][2].tex = D3DXVECTOR2(0.1f * x, 1.0f);
		vertexResultScore[i][3].tex = D3DXVECTOR2(0.1f * (x + 1), 1.0f);
		resultScoreNum /= 10;
	}
}


