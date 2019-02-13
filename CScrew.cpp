//
//	CScrew.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include"CScrew.h"
#include<vector>

//class
#include"CMesh.h"
#include"CRender.h"
#include"CCollision.h"
#include"Billboard.h"
#include"CBurst.h"

#include"Screwdrop.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================
static CScrew Index[SCREW_NUM];
static CXModelName* ScrewModel;

//===============================================
//	クラス名		class
//===============================================

CScrew::CScrew()
	:
	transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }),
	ColSphere(this->transform.Position(), 1.0f)
{
	bEnable = false;
}

CScrew::~CScrew()
{

}

void CScrew::g_Initialize()
{
	ScrewModel = new CXModelName(NModel::TARGET);

	for (int i = 0; i < SCREW_NUM; i++)
	{
		Index[i].Initialize();
	}
}

void CScrew::g_Update()
{
	for (int i = 0; i < SCREW_NUM; i++)
	{
		if (Index[i].bEnable)
		{
			Index[i].Update();
		}
	}
}

void CScrew::g_Render()
{
	for (int i = 0; i < SCREW_NUM; i++)
	{
		if (Index[i].bEnable)
		{
			Index[i].Render();
		}
	}
}

void CScrew::g_Finalize()
{
	for (int i = 0; i < SCREW_NUM; i++)
	{
		Index[i].Finalize();
	}
}



void CScrew::Initialize()
{
	CScrew::CScrew();
}

void CScrew::Update()
{

}

void CScrew::Render()
{
	D3DXMATRIX mtxRotationFace;
	D3DXVECTOR3 face = this->face;
	D3DXVECTOR3 X, Y, Z; //X:右 Z:前 Y:上
	D3DXVECTOR3 Faceup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Z = -face;
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &Faceup), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));

	//回転行列を作る
	mtxRotationFace._11 = X.x; mtxRotationFace._12 = X.y; mtxRotationFace._13 = X.z; mtxRotationFace._14 = 0;
	mtxRotationFace._21 = Y.x; mtxRotationFace._22 = Y.y; mtxRotationFace._23 = Y.z; mtxRotationFace._24 = 0;
	mtxRotationFace._31 = Z.x; mtxRotationFace._32 = Z.y; mtxRotationFace._33 = Z.z; mtxRotationFace._34 = 0;
	mtxRotationFace._41 = 0.0f; mtxRotationFace._42 = 0.0f; mtxRotationFace._43 = 0.0f; mtxRotationFace._44 = 1.0f;

	D3DXMATRIX mtx = mtxRotationFace * this->transform.Get_MtxWorld();
	NRender3D::Render(ScrewModel, &mtx);
}

void CScrew::Finalize()
{
	CScrew::CScrew();
}

void CScrew::Create(D3DXVECTOR3 position, D3DXVECTOR3 face)
{
	for (int i = 0; i < SCREW_NUM; i++)
	{
		if (!Index[i].bEnable)
		{
			CScrew* Screw = &Index[i];
			Screw->bEnable = true;
			Screw->transform.Set_Position(position);
			Screw->face = face;
			return;
		}
	}
}

void CScrew::Destroy()
{
	this->bEnable = false;
}

void CScrew::Hit()
{
	Screwdrop_Create(this->transform.Get_Position(), this->face);
	this->Destroy();
}

CScrew* Get_Screw(int num)
{
	return &Index[num];
}

bool Get_ScrewIsEnable(int num)
{
	return Index[num].bEnable;
}

int Get_ScrewNum()
{
	int out = 0;
	for (int i = 0; i < SCREW_NUM; i++)
	{
		if (Index[i].bEnable)
		{
			out++;
		}
	}
	return out;
}