//
//	TimeRender.cpp
//		Author:ハンコウ	DATE:2019/02/05
//===============================================

//===============================================
//	インクルード	include
//===============================================

#include"Score.h"
#include"Texture.h"
#include"Sprite.h"
#include"TimeRender.h"

#include"CTimer.h"//残り時間のヘッダーファイル

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================

//------------------------------------
//	描画
//------------------------------------
void Time_Render(D3DXVECTOR2 pos)
{
	int Timeremain;
	Timeremain = Timer::GetTime()/*タイムリターン*/;
	for (int i = 0; i < TIME_FIG; i++)
	{
		int number = Timeremain % 10;
		Timeremain /= 10;
		Number_Render({ pos.x + NTexture::Get_Width(NTexture::ScoreTex) * 0.15f * (TIME_FIG - (i + 1)), pos.y }, number);
	}
}