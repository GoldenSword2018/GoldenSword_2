//
//	CTarget.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CTARGET_H
#define CTARGET_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"CTransform.h"
#include"CCollision.h"

//================================================
//	マクロ定義	define
//================================================
#define TARGET_NUM (256)

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
//	クラス		class
//================================================

//-------------------------------------
//	CTarget
//-------------------------------------
class CTarget
{
public:
	CTransform transform;
	Collision::Sphere ColSphere;
	bool bEnable;
public:
	CTarget();
	~CTarget();
public:
	static void Create(D3DXVECTOR3 position);
public:
	static void g_Initialize();
	static void g_Update();
	static void g_Render();
	static void g_Finalize();
public:
	void Initialize();
	void Update();
	void Render();
	void Finalize();
	void Destroy();
	void Hit();
};

CTarget* Get_Target(int num);
bool Get_TargetIsEnable(int num);
int Get_TargetNum();

#endif