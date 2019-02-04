//
//	common.h
//		Author:HIROMASA IKEDA	DATE:2018/09/15
//===============================================
#pragma once

#ifndef COMMON_H
#define COMMON_H

//===============================================
//	マクロ定義
//===============================================
//画面サイズ
#define WINDOWSCREEN_WIDTH (1024)
#define WINDOWSCREEN_HEIGHT (576)

// 2/1
#define WINDOWSCREEN_WIDTH_2 (WINDOWSCREEN_WIDTH*0.5f)
#define WINDOWSCREEN_HEIGHT_2 (WINDOWSCREEN_HEIGHT*0.5f)

//スコア保存先
#define SCORE_DATAFILE "./ScoreData.din"

//#define DISABLE_GAMEPAD
#define DISABLE_SOUND
#define DISABLE_DS4
//#define DISABLE_JOYCON

#endif // !COMMON_H
