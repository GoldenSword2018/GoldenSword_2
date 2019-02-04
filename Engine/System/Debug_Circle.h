//
//	Debug_Circle.h
//		USER:HIROMASA IKEDA		DATE:2018/07/09
//===============================================
#pragma once
#ifndef DEBUG_CIRCLE_H
#define DEBUG_CIRCLE_H

#include<d3dx9.h>

void DebugPrimitive_Initialize(LPDIRECT3DDEVICE9 Device);
void DebugPrimitive_Finalize();
void DebugPrimitive_BatchBegin();
void DebugPrimitive_BatchDrawCircle(float x, float y, float radius);
void DebugPrimitive_BatchRun(LPDIRECT3DDEVICE9 Device);

#endif // !DEBUG_CIRCLE_H

