//======================================
// ノーツの処理[note.cpp]
// Author : 染矢　晃介
//======================================
#include "note.h"


//=====================================
//コンストラクタ
//=====================================
Note::Note()
{
	ctrl = new NoteController();
	view = new NoteView();

	ctrl->note = this;
	view->note = this;

	//値の仮設定
	pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	scl = D3DXVECTOR3(NOTE_SCALE_X, NOTE_SCALE_Y, NOTE_SCALE_Z);
	move = 0;
	use = false;
}

//=======================================
//デストラクタ
//=======================================
Note::~Note()
{
	delete ctrl;

	delete view;
}

//=======================================
//更新処理
//=======================================
void Note::Update()
{
	ctrl->Update();
}

//=======================================
//描画処理
//=======================================
void Note::Draw()
{
	view->Draw();
}

//=======================================
//Get関数[pos]:返り値でposを返す
//=======================================
D3DXVECTOR3 Note::GetPos()
{
	return pos;
}

//=======================================
//Get関数[scl]:返り値でsclを返す
//=======================================
D3DXVECTOR3 Note::GetScl()
{
	return scl;
}

//=======================================
//Get関数[mtxWorld]:返り値でmtxWorldを返す
//=======================================
D3DXMATRIX Note::GetMtxWorld()
{
	return mtxWorld;
}

//=======================================
//Set関数：ノーツの設置を行う
//=======================================
