//
//	Grid.h
//		Author:HIROMASA IKEDA	DATE:2018/09/27
//===============================================
#pragma once
#ifndef GRID_H
#define	GRID_H

#include<d3dx9.h>

//===============================================
//	É}ÉNÉçíËã`
//===============================================
//#define DISABLE_GRID		//GridÇñ≥å¯
#define GRID_WIDTH (1)
#define GRID_COLOR (D3DCOLOR_RGBA(255,255,255,255))

//===============================================
//	ä÷êî
//===============================================
void Grid_Initialize();
void Grid_Render();

#endif // !GRID_H

