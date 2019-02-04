//=============================================================================
//
// ジョイコン入力処理 [joycon_input.cpp]
//
//=============================================================================
#include <Windows.h>
#define DIRECTINPUT_VERSION (0x0800)
#include <dinput.h>
#include "input.h"
#include "debug_font.h"
#include "joycon_input.h"


//*****************************************************************************
// マクロ定義
//*****************************************************************************
#define	NUM_KEY_MAX			(256)	// キーの最大数
#define	LIMIT_COUNT_REPEAT	( 5 )	// リピートカウントリミッター


//*****************************************************************************
// プロトタイプ宣言
//*****************************************************************************


//*****************************************************************************
// グローバル変数
//*****************************************************************************
LPDIRECTINPUTDEVICE8	g_pDevGamepad = NULL;				// 入力デバイス(ゲームパッド)へのポインタ
BYTE					g_JoyTrigger[NUM_KEY_MAX];			// ゲームパッドのトリガー情報ワーク
BYTE					g_JoyRelease[NUM_KEY_MAX];			// ゲームパッドのリリース情報ワーク
BYTE					g_JoyRepeat[NUM_KEY_MAX];			// ゲームパッドのリピート情報ワーク
int						g_JoyRepeatCnt[NUM_KEY_MAX];		// ゲームパッドのリピートカウンタ

DIJOYSTATE2				g_Joy;								// ゲームパッドの初期化
bool					gamepadUseEnable = false;			// ゲームパッドが使用可能ならtrue



//=============================================================================
//	ゲームパッドの初期化
//=============================================================================
HRESULT JoyconInput_Initialize(HWND hWnd, LPDIRECTINPUT8 pInput)
{
	// デバイスの作成
	if (FAILED(pInput->CreateDevice(GUID_Joystick, &g_pDevGamepad, NULL)))
	{
		MessageBox(hWnd, "ゲームパッドがねぇ！", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// データフォーマットを設定
	if (FAILED(g_pDevGamepad->SetDataFormat(&c_dfDIJoystick2)))
	{
		MessageBox(hWnd, "ゲームパッドのデータフォーマットを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// 協調モードを設定（フォアグラウンド＆非排他モード）
	if (FAILED(g_pDevGamepad->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		MessageBox(hWnd, "ゲームパッドの協調モードを設定できませんでした。", "警告！", MB_ICONWARNING);
		return E_FAIL;
	}

	// ゲームパッドへのアクセス権を獲得(入力制御開始)
	if (FAILED(g_pDevGamepad->Poll()))
	{
		g_pDevGamepad->Acquire();

	}

	// ゲームパッドを使用可能に設定
	gamepadUseEnable = true;

	return S_OK;
}

//=============================================================================
//	ゲームパッドの終了処理
//=============================================================================
void JoyconInput_Finalize(void)
{
	if (g_pDevGamepad != NULL)
	{
		// 入力デバイス(ゲームパッド)の開放
		// ゲームパッドへのアクセス権を開放(入力制御終了)
		g_pDevGamepad->Unacquire();

		g_pDevGamepad->Release();
		g_pDevGamepad = NULL;
	}
}

//=============================================================================
//	ゲームパッドの更新処理
//=============================================================================
void JoyconInput_Update(void)
{

	DIJOYSTATE2 Joy;


	// ゲームパッドが使用可能かどうか判断
	if (gamepadUseEnable) {

		// デバイスからデータを取得
		if (SUCCEEDED(g_pDevGamepad->GetDeviceState(sizeof(DIJOYSTATE2), &Joy)))
		{

			for (int nCnKey = 0; nCnKey < NUM_KEY_MAX; nCnKey++)
			{

				//キートリガーリリース情報の作成
				g_JoyTrigger[nCnKey] = (g_Joy.rgbButtons[nCnKey] ^ Joy.rgbButtons[nCnKey]) & Joy.rgbButtons[nCnKey];

				g_JoyRelease[nCnKey] = (g_Joy.rgbButtons[nCnKey] ^ Joy.rgbButtons[nCnKey]) & g_Joy.rgbButtons[nCnKey];

				//キーリピート情報の生成
				if (Joy.rgbButtons[nCnKey] & 0x80) {			//不具合起きた場合, if( Joy.rgbButtons[nCnKey] & 0x80 )
					if (g_JoyRepeatCnt[nCnKey] < LIMIT_COUNT_REPEAT) {
						g_JoyRepeatCnt[nCnKey]++;
						if (g_JoyRepeatCnt[nCnKey] == 1) {
							//if( g_JoyRepeatCnt[nCnKey]==1 || g_JoyRepeatCnt[nCnKey]>=LIMIT_COUNT_REPEAT ){

							g_JoyRepeat[nCnKey] = Joy.rgbButtons[nCnKey];

						}
						else {

							g_JoyRepeat[nCnKey] = 0;

						}
					}
				}
				else {

					g_JoyRepeat[nCnKey] = 0;
					g_JoyRepeatCnt[nCnKey] = 0;

				}

				// キープレス情報を保存
				//g_Joy.rgbButtons[nCnKey] = Joy.rgbButtons[nCnKey];

			}

			// キープレス情報を保存
			g_Joy = Joy;

		}
		else {
			// ゲームパッドへのアクセス権を取得
			g_pDevGamepad->Acquire();
		}
	}
}

//=============================================================================
//	ゲームパッドのボタンのプレス状態を取得
//=============================================================================
bool JoyconInput_IsPress(int nKey)
{
	//return (g_Joy[nKey] & 0x80) ? true: false;
	return (g_Joy.rgbButtons[nKey] & 0x80) ? true : false;
}

//=============================================================================
//	ゲームパッドのボタンのトリガー状態を取得
//=============================================================================
bool JoyconInput_IsTrigger(int nKey)
{
	return (g_JoyTrigger[nKey] & 0x80) ? true : false;
}

//=============================================================================
//	ゲームパッドのボタンのリリース状態を取得
//=============================================================================
bool JoyconInput_IsRelease(int nKey)
{
	return (g_JoyRelease[nKey] & 0x80) ? true : false;
}


//=============================================================================
//	左スティックのX座標を取得
//=============================================================================
int JoyconInput_GetLeftStickX(void)
{
	return g_Joy.lX - BASE_POSITION;
}

//=============================================================================
//	左スティックのY座標を取得
//=============================================================================
int JoyconInput_GetLeftStickY(void)
{
	return -g_Joy.lY + BASE_POSITION;
}


//=============================================================================
//	角速度を取得（ヨー）
//=============================================================================
int JoyconInput_GetAVYaw(void)
{
	return -g_Joy.lRz + BASE_POSITION;
}


//=============================================================================
//	角速度を取得（ロール）
//=============================================================================
int JoyconInput_GetAVRoll(void)
{
	return -g_Joy.rglSlider[0] + BASE_POSITION;
}


//=============================================================================
//	角速度を取得（ピッチ）
//=============================================================================
int JoyconInput_GetAVPitch(void)
{
	return g_Joy.rglSlider[1] - BASE_POSITION;
}



void JoyconInput_Draw(void)
{
#ifdef _DEBUG
	DebugFont_Draw(0, 0, "スティックX:%d", JoyconInput_GetLeftStickX());
	DebugFont_Draw(0, 20, "スティックY:%d", JoyconInput_GetLeftStickY());
	DebugFont_Draw(0, 40, "ヨー:%d", JoyconInput_GetAVYaw());
	DebugFont_Draw(0, 60, "ピッチ:%d", JoyconInput_GetAVPitch());
	DebugFont_Draw(0, 80, "ロール:%d", JoyconInput_GetAVRoll());
	for (int i = 0; i < 30; i++)
	{
		DebugFont_Draw(200, 20 * i, "ボタン%d:%d", i, g_Joy.rgbButtons[i]);
	}
#endif // _DEBUG
}