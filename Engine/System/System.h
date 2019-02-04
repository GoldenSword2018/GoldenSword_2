//
//	System.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
#pragma once
#ifndef SYSTEM_H
#define SYSTEM_H

#include<d3dx9.h>
#include"common.h"

//===============================================
//	マクロ定義
//===============================================
#define CLASS_NAME		("GameWindow")

#ifndef WINDOW_STYLE				//ウィンドウスタイル
#define WINDOW_STYLE	(WS_OVERLAPPEDWINDOW ^ (WS_MAXIMIZEBOX  | WS_THICKFRAME))
#endif // !WINDOW_STYLE

#ifndef WINDOW_CAPTION				//ウィンドウ名
#define WINDOW_CAPTION	("NONE")
#endif // !WINDOW_CAPTION

#ifndef BG_COLOR					//背景色
#define BG_COLOR (D3DCOLOR_RGBA(75, 75, 75, 255))
#endif // !BG_COLOR

#ifndef WINDOWSCREEN_WIDTH			//スクリーン幅
#define WINDOWSCREEN_WIDTH (1024)
#endif // !WINDOWSCREEN_WIDTH

#ifndef WINDOWSCREEN_HEIGHT			//スクリーン縦
#define WINDOWSCREEN_HEIGHT (576)
#endif // !WINDOWSCREEN_HEIGHT

#define DEBUG_KEY_ENABLE	//デバッグキーの有効

//===============================================
//	メイン関数
//===============================================
void Main_Initialize(void);		//初期化
void Main_UpdateBegin(void);	//前更新
void Main_Render(void);			//描画
void Main_UpdateEnd(void);		//後更新
void Main_Finalize(void);		//終了

//===============================================
//	関数	
//===============================================
HWND *System_GethWnd();
HINSTANCE *System_GethInstance();

#ifndef INPUT_H
LPDIRECT3DDEVICE9 System_GetDevice(void);
#endif // !INPUT_H

#endif // !SYSTEM_CPP

