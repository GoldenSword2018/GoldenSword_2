//
//	CTarget.cpp
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
#include"CTarget.h"
#include<vector>

//class
#include"CMesh.h"
#include"CRender.h"
#include"CCollision.h"
#include"Billboard.h"
#include"CBurst.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================
static CTarget Index[TARGET_NUM];
static CXModelName TargetModel(NModel::TARGET);

//===============================================
//	クラス名		class
//===============================================

CTarget::CTarget()
:
	transform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, {0.0f,0.0f,0.0f}),
	ColSphere(this->transform.Position(),1.0f)
{
	bEnable = false;
}

CTarget::~CTarget()
{

}

void CTarget::g_Initialize()
{
	for(int i = 0; i < TARGET_NUM; i++)
	{
		Index[i].Initialize();
	}
}

void CTarget::g_Update()
{
	for (int i = 0; i < TARGET_NUM; i++)
	{
		if(Index[i].bEnable)
		{
			Index[i].Update();
		}
	}
}

void CTarget::g_Render()
{
	for (int i = 0; i < TARGET_NUM; i++)
	{
		if (Index[i].bEnable)
		{
			Index[i].Render();
		}
	}
}

void CTarget::g_Finalize()
{
	for (int i = 0; i < TARGET_NUM; i++)
	{
		Index[i].Finalize();
	}
}



void CTarget::Initialize()
{
	CTarget::CTarget();
}

void CTarget::Update()
{

}

void CTarget::Render()
{
	D3DXMATRIX mtx = InvMatrix() * this->transform.Get_MtxWorld();
	NRender3D::Render(&TargetModel,&mtx);
}

void CTarget::Finalize()
{
	CTarget::CTarget();
}

void CTarget::Create(D3DXVECTOR3 position)
{
	for(int i = 0; i < TARGET_NUM; i++)
	{
		if(!Index[i].bEnable)
		{
			CTarget* target = &Index[i];
			target->bEnable = true;
			target->transform.Set_Position(position);
			return;
		}
	}
}

void CTarget::Destroy()
{
	this->bEnable = false;
}

void CTarget::Hit()
{
	CBurst* burst = new CBurst(this->transform.Get_Position(), { 1.0f,1.0f,1.0f },false);
	this->Destroy();
}

CTarget* Get_Target(int num)
{
	return &Index[num];
}

bool Get_TargetIsEnable(int num)
{
	return Index[num].bEnable;
}

int Get_TargetNum()
{
	int out = 0;
	for(int i = 0; i < TARGET_NUM; i++)
	{
		if (Index[i].bEnable)
		{
			out++;
		}
	}
	return out;
}