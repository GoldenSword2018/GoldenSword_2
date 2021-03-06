//	Score.h
//		Author:ハンコウ	DATE:2019/02/05
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef SCORE_H
#define SCORE_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

//================================================
//	マクロ定義	define
//================================================
#define FIG (4) //桁数
#define SCORE_X (100.0f) //スコアのX座標
#define SCORE_Y (100.0f) //スコアのY座標

//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================
static int g_score;

//=========================================================
//	関数
//=========================================================
void Score_Initialize(void);
void Score_Render(void);
void Score_Plus(int Item);
void Number_Render(D3DXVECTOR2 Position, int Number);
int Return_Score(void);

#endif