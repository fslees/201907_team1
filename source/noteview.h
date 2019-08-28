//==================================================
//　ノーツ描画処理[noteview.h]
//  Author : 染矢　晃介
//==================================================
#ifndef _NOTEVIEW_H_
#define _NOTEVIEW_H_

class Note;					
#include "main.h"


//==================================================
//マクロ定義
//==================================================
#define NOTE_MODEL		"data/MODEL/airplane000.x"


//==================================================
//クラス定義
//==================================================
class NoteView
{
	//メンバー変数
public:
	Note * note;		//ノーツのポインタ変数

private:
	
	D3DXVECTOR3 pos;							//位置
	D3DXVECTOR3 scl;							//大きさ
	D3DXMATRIX  mtxWorld ;						//ワールドマトリクス

	//メンバー関数
public:
	NoteView();			//コンストラクタ・モデルの読み込みと初期化
	~NoteView();		//デストラクタ・終了処理
	void Draw();		//描画処理
	


private:
};


#endif

