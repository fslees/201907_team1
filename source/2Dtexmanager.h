//================================================
// 2D�̃e�N�X�`���쐬����[2Dtexmanager.h]
// Author : ����@�W��
//================================================
#ifndef _2DTEXMANAGER_H_
#define _2DTEXMANAGER_H_


#include "main.h"

//================================
// �N���X��`
//================================
class Texmanager
{
public: //�����o�[�ϐ�

private:

public: //�����o�[�֐�


	void Draw(LPDIRECT3DTEXTURE9 p, VERTEX_2D vertex[NUM_VERTEX]); //�`�揈��

	void MakeVertex(VERTEX_2D vertex[NUM_VERTEX]);  //���_�̍쐬

	//void DrawNumber(LPDIRECT3DTEXTURE9 p, VERTEX_2D vertex[NUM_VERTEX][SCORE_DIGIT]);

	//void MakeVertexNumber(VERTEX_2D vertex[NUM_VERTEX][SCORE_DIGIT], D3DXVECTOR3 pos); //�X�R�A�ƃR���{�p�̒��_�̍쐬

private:


};

#endif

