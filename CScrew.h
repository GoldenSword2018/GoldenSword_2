//
//	CScrew.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CSCREW_H
#define CSCREW_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"CTransform.h"
#include"CCollision.h"

//================================================
//	�}�N����`	define
//================================================
#define SCREW_NUM (256)

//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
//================================================

//-------------------------------------
//	CScrew
//-------------------------------------
class CScrew
{
public:
	CTransform transform;
	Collision::Sphere ColSphere;
	bool bEnable;
	D3DXVECTOR3 face;
public:
	CScrew();
	~CScrew();
public:
	static void Create(D3DXVECTOR3 position, D3DXVECTOR3 face);
public:
	static void g_Initialize();
	static void g_Update();
	static void g_Render();
	static void g_Finalize();
private:
	void Initialize();
	void Update();
	void Render();
	void Finalize();
	void Destroy();
	void Hit();
};

CScrew* Get_Screw(int num);
bool Get_ScrewIsEnable(int num);
int Get_ScrewNum();

#endif#pragma once
