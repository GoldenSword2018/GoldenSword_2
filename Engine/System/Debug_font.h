//
//	Debug_font.h
//		Author:HIROMASA IKEDA	DATE:2018/07/06
//===============================================

#pragma once

#ifndef DEBUG_FONT_H
#define DEBUG_FONT_H

//===============================================
//	ä÷êî
//===============================================
void DebugFont_Initialize(void);
void DebugFont_Finalize(void);
void DebugFont_Draw(int x, int y, const char* pFormat, ...);

#endif // !DEBUG_FONT_H
