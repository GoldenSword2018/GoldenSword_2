//
//	Debug_font.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/20
//===============================================
//
//	動くかしらない。多分ミスってる
//
//-----------------------------------------------
#include<d3dx9.h>
#include<stdio.h>
#include"System.h"
#include"debug_font.h"

//===============================================
//	マクロ定義
//===============================================
#define DEBUG_PRINTF_BUFFER_MAX (256) // 文字列用バッファ量（少ないときは増やすこと）

//===============================================
//	フォント
//===============================================
#if defined(_DEBUG) || defined(DEBUG)
static LPD3DXFONT g_pD3DXFont = NULL;
#endif

//===============================================
//	初期化処理
//===============================================
void DebugFont_Initialize(void) 
{
#if defined(_DEBUG) || defined(DEBUG)
	LPDIRECT3DDEVICE9 pD3DDevice = System_GetDevice();
	D3DXCreateFont(
		pD3DDevice,
		16,
		0,
		0,
		0,
		FALSE,
		SHIFTJIS_CHARSET,	//日本語使うならこれ
		OUT_DEFAULT_PRECIS,	
		DEFAULT_QUALITY,
		DEFAULT_PITCH,	//文字間
		"Terminal",	//フォント
		&g_pD3DXFont
	);
#endif
}

//===============================================
//	終了処理
//===============================================
void DebugFont_Finalize(void) 
{
#if defined(_DEBUG) || defined(DEBUG)
	if (g_pD3DXFont) 
	{
		g_pD3DXFont->Release();
		g_pD3DXFont = NULL;
	}
#endif
}

//===============================================
//	描画
//===============================================
void DebugFont_Draw(int x,int y,const char* pFormat, ...) 
{
#if defined(_DEBUG) || defined(DEBUG)
	//この矩形にフォントポリゴン貼っている感じ
	RECT rect = {x,y,WINDOWSCREEN_WIDTH,WINDOWSCREEN_HEIGHT};
	
	va_list argp;
	va_start(argp, pFormat);
	// 文字列用バッファ
	char buf[DEBUG_PRINTF_BUFFER_MAX];
	vsprintf_s(buf, DEBUG_PRINTF_BUFFER_MAX, pFormat, argp);
	va_end(argp);
	
	g_pD3DXFont->DrawText(
		NULL,
		buf,
		-1,	//指定した文字数を表示(-1だと全部)
		&rect,
		DT_LEFT,
		D3DCOLOR_RGBA(0,255,0,255)	//文字色
		);
#else
	UNREFERENCED_PARAMETER(pFormat);
	UNREFERENCED_PARAMETER(x);
	UNREFERENCED_PARAMETER(y);
#endif
}