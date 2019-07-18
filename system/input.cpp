//=============================================================================
//
// 入力処理 [input.cpp]
// Author : 李尚ミン
//
//=============================================================================
#include "input.h"

//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX		(256)			// キー最大数

//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd);
void UninitKeyboard(void);
HRESULT UpdateKeyboard(void);

//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTINPUT8			DInput = NULL;					// IDirectInput8インターフェースへのポインタ
LPDIRECTINPUTDEVICE8	DIDevKeyboard = NULL;			// IDirectInputDevice8インターフェースへのポインタ(キーボード)
BYTE					KeyState[NUM_KEY_MAX];			// キーボードの押下状態を保持するワーク
BYTE					KeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー状態を保持するワーク
BYTE					KeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース状態を保持するワーク
BYTE					KeyStateRepeat[NUM_KEY_MAX];		// キーボードのリピート状態を保持するワーク
int						KeyStateRepeatCnt[NUM_KEY_MAX];	// キーボードのリピートカウンタ

//=============================================================================
// 入力処理の初期化
//=============================================================================
HRESULT InitInput(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	if(!DInput)
	{
		// DirectInputオブジェクトの作成
		hr = DirectInput8Create(hInst, DIRECTINPUT_VERSION,
									IID_IDirectInput8, (void**)&DInput, NULL);
	}

	// キーボードの初期化
	InitKeyboard(hInst, hWnd);

	return S_OK;
}

//=============================================================================
// 入力処理の終了処理
//=============================================================================
void UninitInput(void)
{
	// キーボードの終了処理
	UninitKeyboard();

	if(DInput)
	{// DirectInputオブジェクトの開放
		DInput->Release();
		DInput = NULL;
	}
}

//=============================================================================
// 入力処理の更新処理
//=============================================================================
void UpdateInput(void)
{
	// キーボードの更新
	UpdateKeyboard();
}

//=============================================================================
// キーボードの初期化処理
//=============================================================================
HRESULT InitKeyboard(HINSTANCE hInst, HWND hWnd)
{
	HRESULT hr;

	// デバイスオブジェクトを作成
	hr = DInput->CreateDevice(GUID_SysKeyboard, &DIDevKeyboard, NULL);
	if(FAILED(hr) || DIDevKeyboard == NULL)
	{
		MessageBox(hWnd, "キーボードがねぇ！", "警告！", MB_ICONWARNING);
		return hr;
	}

	// データフォーマットを設定
	hr = DIDevKeyboard->SetDataFormat(&c_dfDIKeyboard);
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	hr = DIDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE));
	if(FAILED(hr))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return hr;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	DIDevKeyboard->Acquire();

	return S_OK;
}

//=============================================================================
// キーボードの終了処理
//=============================================================================
void UninitKeyboard(void)
{
	if(DIDevKeyboard)
	{// デバイスオブジェクトの開放
		DIDevKeyboard->Release();
		DIDevKeyboard = NULL;
	}
}

//=============================================================================
// キーボードの更新処理
//=============================================================================
HRESULT UpdateKeyboard(void)
{
	HRESULT hr;
	BYTE keyState[NUM_KEY_MAX];

	// デバイスからデータを取得
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
		// キーボードへのアクセス権を取得
		DIDevKeyboard->Acquire();
	}

	return S_OK;
}

//=============================================================================
// キーボードのプレス状態を取得
//=============================================================================
bool GetKeyboardPress(int key)
{
	return (KeyState[key] & 0x80) ? true: false;
}

//=============================================================================
// キーボードのトリガー状態を取得
//=============================================================================
bool GetKeyboardTrigger(int key)
{
	return (KeyStateTrigger[key] & 0x80) ? true: false;
}

//=============================================================================
// キーボードのリピート状態を取得
//=============================================================================
bool GetKeyboardRepeat(int key)
{
	return (KeyStateRepeat[key] & 0x80) ? true: false;
}

//=============================================================================
// キーボードのリリ－ス状態を取得
//=============================================================================
bool GetKeyboardRelease(int key)
{
	return (KeyStateRelease[key] & 0x80) ? true: false;
}

