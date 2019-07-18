//=============================================================================
//
// ���͏��� [input.cpp]
// Author : �����~��
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// �}�N����`
//*****************************************************************************
#define	NUM_KEY_MAX		(256)			// �L�[�ő吔

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

//*****************************************************************************
// �O���[�o���ϐ�
//*****************************************************************************
LPDIRECTINPUT8			DInput = NULL;					// IDirectInput8�C���^�[�t�F�[�X�ւ̃|�C���^
LPDIRECTINPUTDEVICE8	DIDevKeyboard = NULL;			// IDirectInputDevice8�C���^�[�t�F�[�X�ւ̃|�C���^(�L�[�{�[�h)
BYTE					KeyState[NUM_KEY_MAX];			// �L�[�{�[�h�̉�����Ԃ�ێ����郏�[�N
BYTE					KeyStateTrigger[NUM_KEY_MAX];	// �L�[�{�[�h�̃g���K�[��Ԃ�ێ����郏�[�N
BYTE					KeyStateRelease[NUM_KEY_MAX];	// �L�[�{�[�h�̃����[�X��Ԃ�ێ����郏�[�N
BYTE					KeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g��Ԃ�ێ����郏�[�N
int						KeyStateRepeatCnt[NUM_KEY_MAX];	// �L�[�{�[�h�̃��s�[�g�J�E���^

//=============================================================================
// ���͏����̏�����
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!DInput)
	{
		// DirectInput�I�u�W�F�N�g�̍쐬
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&DInput, NULL);
	}

	// �L�[�{�[�h�̏�����
	InitKeyboard(hInst, hWnd);

	return S_OK;
}

//=============================================================================
// ���͏����̏I������
//=============================================================================
void UninitInput(void)
{
	// �L�[�{�[�h�̏I������
	UninitKeyboard();

	if(DInput)
	{// DirectInput�I�u�W�F�N�g�̊J��
		DInput->Release();
		DInput = NULL;
	}
}

//=============================================================================
// ���͏����̍X�V����
//=============================================================================
void UpdateInput(void)
{
	// �L�[�{�[�h�̍X�V
	UpdateKeyboard();
}

//=============================================================================
// �L�[�{�[�h�̏���������
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// �f�o�C�X�I�u�W�F�N�g���쐬
	hr = DInput->CreateDevice(GUID_SysKeyboard, &DIDevKeyboard, NULL);
	if(FAILED(hr) || DIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "�L�[�{�[�h���˂��I", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	hr = DIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̃f�[�^�t�H�[�}�b�g��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �������[�h��ݒ�i�t�H�A�O���E���h����r�����[�h�j
	hr = DIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "�L�[�{�[�h�̋������[�h��ݒ�ł��܂���ł����B", "�x���I", MB_ICONWARNING);
		return hr;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��(���͐���J�n)
	DIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̏I������
//=============================================================================
void UninitKeyboard(void)
{
	if(DIDevKeyboard)
	{// �f�o�C�X�I�u�W�F�N�g�̊J��
		DIDevKeyboard->Release();
		DIDevKeyboard = NULL;
	}
}

//=============================================================================
// �L�[�{�[�h�̍X�V����
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyState[NUM_KEY_MAX];

	// �f�o�C�X����f�[�^���擾
	hr = DIDevKeyboard->GetDeviceState(sizeof(keyState), keyState);
	if(SUCCEEDED(hr))
	{
		for(int cntKey = 0; cntKey < NUM_KEY_MAX; cntKey++)
		{
			KeyStateTrigger[cntKey] = (KeyState[cntKey] ^ keyState[cntKey]) & keyState[cntKey];
			KeyStateRelease[cntKey] = (KeyState[cntKey] ^ keyState[cntKey]) & ~keyState[cntKey];
			KeyStateRepeat[cntKey] = KeyStateTrigger[cntKey];

			if(keyState[cntKey])
			{
				KeyStateRepeatCnt[cntKey]++;
				if(KeyStateRepeatCnt[cntKey] >= 20)
				{
					KeyStateRepeat[cntKey] = keyState[cntKey];
				}
			}
			else
			{
				KeyStateRepeatCnt[cntKey] = 0;
				KeyStateRepeat[cntKey] = 0;
			}

			KeyState[cntKey] = keyState[cntKey];
		}
	}
	else
	{
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		DIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// �L�[�{�[�h�̃v���X��Ԃ��擾
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (KeyState[key] & 0x80) ? true: false;
}

//=============================================================================
// �L�[�{�[�h�̃g���K�[��Ԃ��擾
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (KeyStateTrigger[key] & 0x80) ? true: false;
}

//=============================================================================
// �L�[�{�[�h�̃��s�[�g��Ԃ��擾
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (KeyStateRepeat[key] & 0x80) ? true: false;
}

//=============================================================================
// �L�[�{�[�h�̃����|�X��Ԃ��擾
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (KeyStateRelease[key] & 0x80) ? true: false;
}

