//
//	Fade.h
//		Author:HIROMASA IEKDA		DATE:2018/07/11
//===============================================
//
//	使ってない
//
//-----------------------------------------------
#pragma once
#ifndef FADE_H
#define FADE_H

#include<d3dx9.h>
#include"common.h"

//===============================================
//	関数
//===============================================
void Fade_Initialize();
void Fade_Update();
void Fade_Render();
//bOut(true = FadeIn,false = FadeOut)
void Fade_Triger(bool bOut, int frame, D3DCOLOR Color);

bool Fade_IsFade();
bool Fade_Alpha();

#endif // !FADE_H


