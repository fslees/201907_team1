//==================================================
//　ノーツ処理[note.h]
//  Author : 染矢　晃介
//==================================================
#ifndef _NOTE_H_
#define _NOTE_H_

#include "noteview.h"
#include "notecontroller.h"
#include "main.h"

//==================================================
//マクロ定義
//==================================================

//==================================================
//クラス定義
//==================================================
class Note
{
	//メンバー変数
public:
	NoteView * view;		//viewのポインタ変数
	NoteController *ctrl;	//controllerのポインタ変数
	D3DXVECTOR3 pos;

private:

	//メンバー関数
public:
	 Note();				//コンストラクタ
	 ~Note();				//デストラクタ
	 void Update();			//更新処理を呼ぶ
	 void Draw();			//描画処理を呼ぶ


private:
};


#endif

