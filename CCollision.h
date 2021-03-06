//
//	CCollision.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CCOLLISION_H
#define CCOLLISION_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"CTransform.h"

//================================================
//	マクロ定義	define
//================================================


//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//================================================
//	Class
//================================================

namespace Collision
{
	//-------------------------------------
	//	ACollision
	//-------------------------------------
	class ACollision
	{
	public:
		ACollision();
		~ACollision();
	};

	//-------------------------------------
	//	Sphere
	//-------------------------------------
	class Sphere:public ACollision
	{
	public:
		D3DXVECTOR3* pCenter;		//中心
		float radius;				//半径
	public:
		Sphere(D3DXVECTOR3* pCenter,float radius);
		~Sphere();
	};

	bool Judge(Sphere* col_1,Sphere* col_2);
}
#endif