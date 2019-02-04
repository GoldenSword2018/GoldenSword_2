//
//	MeshField.h
//		Author:HIROMASA IEKDA	DATE:2018/11/27
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef MESHFIELD_H
#define MESHFIELD_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"Texture.h"

//================================================
//	マクロ定義	define
//================================================

//-------------------------------------
//	Ground
//-------------------------------------
#define MF_GROUND_GRID_WIDTH (50)		//横グリッド数
#define MF_GROUND_GRID_DEPTH (50)		//奥行グリッド数

#define MF_GROUND_SCALE_WIDTH (100)		//横サイズ
#define MF_GROUND_SCALE_DEPTH (100)		//奥行サイズ

//-------------------------------------
//	Cylinder
//-------------------------------------
#define MF_CYLINDER_HEIGHT (50)			//高さ
#define MF_CYLINDER_RADIUS (40.0f)		//半径

#define MF_CYLINDER_GRID_WIDTH (100)	//横グリッド数
#define MF_CYLINDER_GRID_HEIGHT (10)	//縦グリッド数

#define MF_CYLINDER_ANGLE ((2*M_PI)/MF_CYLINDER_GRID_WIDTH)					//1グリッド角度
#define MF_CYLINDER_A_HEIGHT (MF_CYLINDER_HEIGHT / MF_CYLINDER_GRID_HEIGHT)	//1グリッド高さ

//-------------------------------------
//	SkyDome
//-------------------------------------
#define MF_SKYDORM_RADIUS (70)			//半径
#define MF_SKYDORM_GRID_HEIGHT (50)		//縦グリッド数
#define MF_SKYDORM_GRID_WIDTH (50)		//横グリッド数

#define MF_SKYDORM_ANGLE_WIDTH	( (2*M_PI) / MF_SKYDORM_GRID_WIDTH ) //1グリッド角度
#define MF_SKYDORM_ANGLE_HEIGHT	( (M_PI_2) / MF_SKYDORM_GRID_HEIGHT) //1グリッド

//-------------------------------------
//	Wall
//-------------------------------------
#define MF_WALL_HEIGHT	(2)			//高さ
#define MF_WALL_WIDTH	(100)			//横幅

#define MF_WALL_GRID_HEIGHT (2)		//縦グリッド
#define MF_WALL_GRID_WIDTH	(100)		//横グリッド

//================================================
//	名前空間
//================================================
namespace NMeshField
{
	//================================================
	//	関数		function
	//================================================
	void Initialize();

	void Render_Ground(const D3DXVECTOR3 Center, const NTexture::Name TextureName);
	void Render_Cylinder(const D3DXVECTOR3 Center, const NTexture::Name TextureName);
	void Render_SkyDome(const D3DXVECTOR3 Center, const NTexture::Name TextureName);
	void Render_Wall(const D3DXVECTOR3 Center, const D3DXVECTOR3 Scale, const D3DXVECTOR3 Rotate, const NTexture::Name TextureName);
	void Render_Wall_Enclosure(const D3DXVECTOR3 Center, const D3DXVECTOR3 Scale, const NTexture::Name TextureName);
	void Finalize();
}

#endif