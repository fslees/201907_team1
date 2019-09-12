//=============================================================================
//
// ���ʃf�[�^�̊Ǘ����� [bmsmanager.cpp]
// Author : GP12A332_26_�c�����z
//
//=============================================================================
#include "bmsmanager.h"
#include "sound.h"
#include "scene.h"
//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define BMS_CHANNEL_MAX		(6)		// BMS�t�@�C���̃`�����l����

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
const int BmsManager::index[BMS_CHANNEL_MAX] = { 0,2,4,1,3,5 };

//====================================================================
// �R���X�g���N�^
//====================================================================
BmsManager::BmsManager()
{
	// �e�ϐ��̏�����
	scrMulti = 5.0f;
	startTime = 0;
	globalFreq = 0;
	elapsedTime = 0;
	scrZ = 0;
	ZeroMemory(&startNum, sizeof(startNum));

	// BMS���[�h
	bms.Load("data/BMS/test2.bms");

	// �T�E���h�̃��[�h
	BGM = LoadSound(BGM_NULL);
	PlaySound(BGM, E_DS8_FLAG_LOOP);

	// �}�V���̎��g�����擾
	LARGE_INTEGER freq;
	QueryPerformanceFrequency(&freq);
	globalFreq = freq.QuadPart;

	// ���݂̎��Ԃ��J�n���ԂƂ���
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	startTime = li.QuadPart;
}

//====================================================================
// �f�X�g���N�^
//====================================================================
BmsManager::~BmsManager()
{
	bms.Clear();
}

//====================================================================
// ���ʃf�[�^�̍X�V����
//====================================================================
void BmsManager::Update(NoteManager *note)
{
	// �J�n������o�߂������Ԃ��Z�o
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	elapsedTime = (double)(li.QuadPart - startTime) / globalFreq;

	// �o�߂������Ԃ���i��BMS�J�E���g�l���Z�o
	nowCount = bms.GetCountFromTime(elapsedTime);

	// BMS�J�E���^���Ȃ̍ő�J�E���g+1���߂𒴂�����I��
	if (bms.GetMaxCount() + BMS_RESOLUTION <= nowCount)
	{
		StopSound(BGM);
		SetScene(SCENE_RESULT);
		return;
	}

	// BGM���^�C�~���O�ɂ��킹�čĐ�����
	for (int i = startNum[BMS_BACKMUSIC]; i < bms.GetObjeNum(BMS_BACKMUSIC); i++) {
		LPBMSDATA b = bms.GetObje(BMS_BACKMUSIC, i);
		if (nowCount < b->lTime)
			break;
		if (b->bFlag) {
			if (nowCount >= (b->lTime * (scrMulti / 2)))
			{
				StopSound(BGM);
				BGM = LoadSound(BGM_GAME);
				PlaySound(BGM, E_DS8_FLAG_NONE);
				b->bFlag = FALSE;				// �ʉ߂���BGM�t���O��false
				startNum[BMS_BACKMUSIC] = i + 1;
			}
		}
	}

	// �X�N���[�����W��ł̃X�N���[���ʂ��Z�o
	scrZ = (int)((double)nowCount / (BMS_RESOLUTION / (scrMulti * 192)));

	CheckSetCount(note);
}

//====================================================================
// ���ʃf�[�^�̃m�[�c�������Ԃ̊m�F����
//====================================================================
bool BmsManager::CheckSetCount(NoteManager *note)
{
	for (int j = 0; j < 6; j++)
	{
		for (int i = startNum[0x11 + index[j]]; i < bms.GetObjeNum(0x11 + index[j]); i++)
		{
			LPBMSDATA b = bms.GetObje(0x11 + index[j], i);
			if (nowCount > b->lTime)
			{
				note->SetNote(j, scrMulti);
			}

			int objZ = (int)((double)b->lTime / (BMS_RESOLUTION / (scrMulti * 192)));
			// �X�N���[�����l���������݂�Z���W���Z�o
			offZ = objZ - scrZ;
			// ���胉�C����艺�Ȃ�����\���͂����A���񂩂炻�̎��̃I�u�W�F����Q�Ƃ���
			if (offZ < 0) 
			{
				startNum[index[j] + 0x11] = i + 1;
				continue;
			}
		}
	}

	return false;
}
