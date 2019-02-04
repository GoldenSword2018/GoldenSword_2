//
//	Input.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/16
//===============================================
#include<Windows.h>
#include<dinput.h>
#include"input.h"

#include"joycon_input.h"
#include"Dualshock4.h"
#include"Dualshock4.hpp"

//===============================================
//	グローバル変数
//===============================================
static LPDIRECTINPUT8		g_pInput		= NULL;				// DirectInputオブジェクトへのポインタ

static LPDIRECTINPUTDEVICE8	g_pDevKeyboard = NULL;				// 入力デバイス(キーボード)へのポインタ
static BYTE					g_aKeyState[NUM_KEY_MAX];			// キーボードの入力情報ワーク
static BYTE					g_aKeyStateTrigger[NUM_KEY_MAX];	// キーボードのトリガー情報ワーク
static BYTE					g_aKeyStateRelease[NUM_KEY_MAX];	// キーボードのリリース情報ワーク

static LPDIRECTINPUTDEVICE8	g_pDevMouse		= NULL;				// 入力デバイス(マウス)
static DIMOUSESTATE2		g_MouseState2	= { NULL };			//マウスの情報
static POINT				g_MousePos		= { NULL };			//マウスの場所

//===============================================
//	関数
//===============================================

//===============================================
//	初期化
//===============================================
void Input_Initalize(HWND hWnd,HINSTANCE hInstance )
{

	if (g_pInput == NULL) {

		// DirectInputオブジェクトの作成
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) {
			MessageBox(hWnd, "Inputデバイスの取得に失敗しました。", "エラー", MB_OK);
			DestroyWindow(hWnd);
			return;
		}
	}

	// 入力処理の初期化
	if (g_pInput == NULL) {
		MessageBox(hWnd, "DirectInputオブジェクトが無いです", "エラー", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	//------------------------------------
	//	キーボード
	//------------------------------------
	// デバイスの作成
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		MessageBox(hWnd, "キーボードが無い", "エラー", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	// データフォーマットを設定
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(hWnd, "キーボードのデータフォーマットを設定できませんでした。", "エラー", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "キーボードの協調モードを設定できませんでした。", "エラー", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	// キーボードへのアクセス権を獲得(入力制御開始)
	g_pDevKeyboard->Acquire();

	//------------------------------------
	//	マウス
	//------------------------------------
	//マウスデバイス取得
	if (FAILED(g_pInput->CreateDevice(GUID_SysMouse, &g_pDevMouse, NULL)))
	{
		MessageBox(hWnd, "マウスが無いです", "エラー", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	//マウスのデータフォーマット
	if (FAILED(g_pDevMouse->SetDataFormat(&c_dfDIMouse2)))
	{
		MessageBox(hWnd, "マウスのデータフォーマットを設定できませんでした。", "エラー", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	//マウスの協調モード
	if (FAILED(g_pDevMouse->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "マウスの協調モードを設定できませんでした。", "エラー", MB_ICONWARNING);
		DestroyWindow(hWnd);
		return;
	}

	g_pDevMouse->Acquire();
}

//===============================================
//	入力更新
//===============================================
void Input_Update(HWND hWnd)
{
	//---------------------------------
	//	キーボード情報
	//---------------------------------
	BYTE aKeyState[NUM_KEY_MAX];	//キーステータス

	// デバイスからデータを取得
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), aKeyState)))
	{
		// aKeyState[DIK_SPACE] & 0x80

		for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
		{
			// キートリガー・リリース情報を生成
			g_aKeyStateTrigger[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & aKeyState[nCnKey];
			g_aKeyStateRelease[nCnKey] = (g_aKeyState[nCnKey] ^ aKeyState[nCnKey]) & g_aKeyState[nCnKey];

			// キープレス情報を保存
			g_aKeyState[nCnKey] = aKeyState[nCnKey];
		}
	}
	else
	{
		// キーボードへのアクセス権を取得
		g_pDevKeyboard->Acquire();
	}

	//------------------------------------
	//	マウス情報
	//------------------------------------
	GetCursorPos(&g_MousePos);					//マウスのXY座標
	ScreenToClient(hWnd, &g_MousePos);		//ウィンドウ内座標に変換


	//マウスのステータス
	if (SUCCEEDED(g_pDevMouse->GetDeviceState(sizeof(DIMOUSESTATE2), &g_MouseState2)))
	{
		//直接データの取得に成功
		int i = 0;
	}
	else
	{
		g_pDevMouse->Acquire();
	}

}

//===============================================
//	終了処理
//===============================================
void Input_Finalize()
{
	//マウスデバイスの開放
	if (g_pDevMouse != NULL)
	{
		g_pDevMouse->Unacquire();
		g_pDevMouse->Release();
		g_pDevMouse = NULL;
	}

	if (g_pDevKeyboard != NULL)
	{
		// 入力デバイス(キーボード)の開放
		// キーボードへのアクセス権を開放(入力制御終了)
		g_pDevKeyboard->Unacquire();
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// 入力処理の終了処理
	if (g_pInput != NULL) {

		// DirectInputオブジェクトの開放
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//===============================================
//	キーボード情報
//===============================================

//-------------------------------------
//	キーボードを押してる
//-------------------------------------
bool Keyboard_IsPress(int nDIK)
{
	return (g_aKeyState[nDIK] & 0x80) ? true : false;
}

//-------------------------------------
//	キーボードを押した
//-------------------------------------
bool Keyboard_IsTrigger(int nDIK)
{
	return (g_aKeyStateTrigger[nDIK] & 0x80) ? true : false;
}

//-------------------------------------
//	キーボードを放した
//-------------------------------------
bool Keyboard_IsRelease(int nDIK)
{
	return (g_aKeyStateRelease[nDIK] & 0x80) ? true : false;
}

//===============================================
//	マウス情報
//===============================================

//-------------------------------------
//	左クリック
//-------------------------------------
bool Mouse_IsLeftDown()
{
	return (g_MouseState2.rgbButtons[0] & 0x80) ? true : false;
}

//-------------------------------------
//	右クリック
//-------------------------------------
bool Mouse_IsRightDown()
{
	return (g_MouseState2.rgbButtons[1] & 0x80) ? true : false;
}

//-------------------------------------
//	ホイールクリック
//-------------------------------------
bool Mouse_IsCenterDown()
{
	return (g_MouseState2.rgbButtons[2] & 0x80) ? true : false;
}

//-------------------------------------
//	マウス加速度　X
//-------------------------------------
float Mouse_IsAccelerationX()
{
	return (float)g_MouseState2.lX;
}

//-------------------------------------
//	マウス加速度　Y
//-------------------------------------
float Mouse_IsAccelerationY()
{
	return (float)g_MouseState2.lY;
}

//-------------------------------------
//	マウス加速度　Z　(スクロール)
//-------------------------------------
float Mouse_IsAccelerationZ()
{
	return (float)g_MouseState2.lZ;
}

//-------------------------------------
//	マウスX座標
//-------------------------------------
float Mouse_IsMouseX()
{
	return (float)g_MousePos.x;
}

//-------------------------------------
//	マウスY座標
//-------------------------------------
float Mouse_IsMouseY()
{
	return (float)g_MousePos.y;
}


