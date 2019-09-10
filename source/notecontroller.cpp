//======================================
// ノーツの処理[note.cpp]
// Author : 染矢　晃介
//======================================
#include "notecontroller.h"
#include "notemanager.h"
#include "note.h"
#include "inputmanager.h"
#include "rating.h"

//======================================
//マクロ定義
//======================================
#define NOTE_DELETE_POS		(100)

//======================================
//コンストラクタ
//======================================
NoteController::NoteController()
{

}

//=====================================
//デストラクタ
//=====================================
NoteController::~NoteController()
{

}

//=====================================
//更新処理
//=====================================
void NoteController::Update()
{
	// ノーツの操作
	InputNote();

	// 座標を移動
	note->pos.z -= note->move;

	// 座標が限度を超えるとデリート
	if (note->pos.z < -NOTE_DELETE_POS)
	{
		note->use = false;
	}
}

//================================================
//通常ノーツの当たり判定
//第１引数：Note *note(対象ノーツのアドレス)
//第２引数：D3DXVECTOR3 linePos(レーンの中心座標)
//戻り値　：なし
//================================================
void NoteController::InputNote()
{
	// 左レーンの操作
	if (GetInput(HIT_LEFT_LANE))
	{
		CheckHit(note, D3DXVECTOR3(-NOTE_SET_POS_X, NOTE_SET_POS_Y, NOTE_SET_POS_Z));
	}
	// 中央レーンの操作
	if (GetInput(HIT_CENTER_LANE))
	{
		CheckHit(note, D3DXVECTOR3(0, NOTE_SET_POS_Y, NOTE_SET_POS_Z));
	}
	// 右レーンの操作
	if (GetInput(HIT_RIGHT_LANE))
	{
		CheckHit(note, D3DXVECTOR3(NOTE_SET_POS_X, NOTE_SET_POS_Y, NOTE_SET_POS_Z));
	}
}

//================================================
//通常ノーツの当たり判定
//第１引数：Note *note(対象ノーツのアドレス)
//第２引数：D3DXVECTOR3 linePos(レーンの中心座標)
//戻り値　：なし
//================================================
void NoteController::CheckHit(Note *note, D3DXVECTOR3 linePos)
{
	D3DXVECTOR3 pos = note->GetPos();

	// X軸でレーンを判定,Z座標で成功パターンの判定
	if (pos.x == linePos.x && pos.z <= 10 && pos.z >= 0)
	{	//パーフェクト
		note->use = false;
		SetRatingTex(PERFECT);
	}
	else if (pos.x == linePos.x && pos.z <= 30 && pos.z >= -10)
	{	//グレート
		note->use = false;
		SetRatingTex(GREAT);
	}
	else if (pos.x == linePos.x && pos.z <= 50 && pos.z >= -15)
	{	//グッド
		note->use = false;
		SetRatingTex(GOOD);
	}
}