//=============================================================================
//
// �^�C�g����ʂ̒�` [title.h]
// Author : �����~��
//
//=============================================================================
#ifndef _TITLELOGO_H_
#define _TITLELOGO_H_

#include "main.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define TEXTURE_TITLELOGO "data/TEXTURE/number.png"
#define LOGO_POS_X			(500)	//���S��x���W
#define LOGO_POS_Y			(450)	//���S��Y���W
#define LOGO_WIDTH			(280)	//��
#define LOGO_HEIGHT			(100)	//����
#define	COUNT_APPERA_LOGO	(60)	// �X�^�[�g�{�^���o���܂ł̎���
#define	INTERVAL_DISP_LOGO	(60)	// �X�^�[�g�{�^���_�ł̎���

//===========================
//�v���g�^�C�v�錾
//===========================
//������
HRESULT InitTitleLogo();
//�I������
void UninitTitleLogo();
//�X�V����
void UpdateTitleLogo();
//�`�揈��
void DrawTitleLogo();
//���_�쐬����
void MakeVertexTitleLogo();
//���ˌ��̐ݒ�
void SetColorLogo();

#endif
