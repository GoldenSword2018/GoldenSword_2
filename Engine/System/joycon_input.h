//=============================================================================
//
// ジョイコン入力処理 [joycon_input.h]
//
//=============================================================================
#ifndef JOYCON_INPUT_H
#define JOYCON_INPUT_H

#include <Windows.h>
#ifndef DIRECTINPUT_VERSION
#define DIRECTINPUT_VERSION		(0x0800)
#endif // !DIRECTINPUT_VERSION

#include <dinput.h>


#define JOYCON_LEFT_STICK_X		(g_Joy.lRx)					// 左スティックX情報
#define JOYCON_LEFT_STICK_Y		(g_Joy.lRy)					// 左スティックY情報
#define JOYCON_AV_YAW			(g_Joy.lRz)					// 角速度情報（ヨー）
#define JOYCON_AV_ROLL			(g_Joy.rglSlider[0])		// 角速度情報（ロール）
#define JOYCON_AV_PITCH			(g_Joy.rglSlider[1])		// 角速度情報（ピッチ）
#define BASE_POSITION			(32767)						// 基準位置


// ジョイコン仮想ボタン情報
typedef enum
{
	JOYCON_BUTTON_INDEX_L_DOWN = 0,				// 下ボタン
	JOYCON_BUTTON_INDEX_L_UP,					// 上ボタン
	JOYCON_BUTTON_INDEX_L_RIGHT,				// 右ボタン
	JOYCON_BUTTON_INDEX_L_LEFT,					// 左ボタン
	JOYCON_BUTTON_INDEX_L_SR,					// 左側SRボタン
	JOYCON_BUTTON_INDEX_L_SL,					// 左側SLボタン
	JOYCON_BUTTON_INDEX_L_L,					// Lボタン
	JOYCON_BUTTON_INDEX_L_ZL,					// ZLボタン
	JOYCON_BUTTON_INDEX_L_MINUS,				// マイナスボタン
	JOYCON_BUTTON_INDEX_L_STICK = 11,			// 左スティック押し込み
	JOYCON_BUTTON_INDEX_R_Y = 16,				// Yボタン
	JOYCON_BUTTON_INDEX_R_X,					// Xボタン
	JOYCON_BUTTON_INDEX_R_B,					// Bボタン
	JOYCON_BUTTON_INDEX_R_A,					// Aボタン
	JOYCON_BUTTON_INDEX_R_SR,					// 右側SRボタン
	JOYCON_BUTTON_INDEX_R_SL,					// 右側SLボタン
	JOYCON_BUTTON_INDEX_R_R,					// Rボタン
	JOYCON_BUTTON_INDEX_R_ZR,					// ZRボタン
	JOYCON_BUTTON_INDEX_R_PLUS = 25,			// プラスボタン
	JOYCON_BUTTON_INDEX_R_STICK,				// 右スティック
	JOYCON_BUTTON_INDEX_R_HOME = 28,			// ホームボタン

	JOYCON_BUTTON_INDEX_MAX
}JOYCON_BUTTON_INDEX;


// プロトタイプ宣言
HRESULT JoyconInput_Initialize(HWND hWnd, LPDIRECTINPUT8 pInput);
void JoyconInput_Finalize(void);
void JoyconInput_Update(void);
bool JoyconInput_IsPress(int nKey);
bool JoyconInput_IsTrigger(int nKey);
bool JoyconInput_IsRelease(int nKey);
int JoyconInput_GetLeftStickX(void);
int JoyconInput_GetLeftStickY(void);
int JoyconInput_GetAVYaw(void);
int JoyconInput_GetAVRoll(void);
int JoyconInput_GetAVPitch(void);

void JoyconInput_Draw(void);


#endif