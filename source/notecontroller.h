//==================================================
//　ノーツ更新処理[notecontroller.h]
//  Author : 染矢　晃介
//==================================================
#ifndef _NOTECONTROLLER_H_
#define _NOTECONTROLLER_H_

class Note; 
#include "main.h"


//==================================================
//マクロ定義
//==================================================

//==================================================
//クラス定義
//==================================================
class NoteController
{
	//メンバー変数
public:
	Note * note;				//ノーツのポインタ変数

private:

	//メンバー関数
public:
	NoteController();			//
	~NoteController();			//
	void Update();				//
	bool SetNoteLane(int laneNum, int notesNo);
	void SetNote(int laneNum);


private:
};


#endif

