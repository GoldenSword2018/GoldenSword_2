//
//	Cube.h
//		Author:HIROMASA IKEDA	DATE:2018/09/21
//===============================================
#pragma once
#ifndef CUBE_H
#define CUBE_H

#include<d3dx9.h>

//===============================================
//	マクロ	
//===============================================
#define FVF_CUBE_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1 )
#define CUBE_PRIMITIVE_TYPE (D3DPT_TRIANGLELIST)	//プリミティブタイプ
#define CUBE_PRIMITIVE_NUM	(12)					//ポリゴン数

//===============================================
//	構造体
//===============================================
typedef struct Cube_Vertex3D_tag
{
	D3DXVECTOR3 Position;	//位置
	D3DXVECTOR3 Normal;		//法線
	D3DXVECTOR2 TexCoord;	//テクスチャ座標
}CubeVertex3D;

//===============================================
//	Cube モデルデータ
//===============================================


//===============================================
//	関数
//===============================================
void* GetModel_Cube();

void Cube_Initialize();
void Cube_Render();
void Cube_Finalize();
#endif