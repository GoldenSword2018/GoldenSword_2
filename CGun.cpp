//
//	CGun.cpp
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
#include"CGun.h"

//class
#include"CBullet.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	クラス名		class
//===============================================


//-------------------------------------
//	メンバ関数名
//-------------------------------------
CGun::CGun()
{
	this->rate = 0;
	this->wait = 0;
	this->BulletNum = 0;
	this->Shake = 0.0f;
	this->transform = new CTransform();
	this->mesh = new CXModelName(NModel::GUN);
}

CGun::CGun(CTransform* transform, D3DXVECTOR3 Muzzle,int BulletNum, int rate)
{
	this->rate = rate;
	this->wait = 0;
	this->BulletNum = BulletNum;
	this->Muzzle = Muzzle;
	this->transform = transform;
	this->mesh = new CXModelName(NModel::GUN);
}

CGun::~CGun()
{

}

D3DXVECTOR3 CGun::Get_Muzzle()
{
	D3DXVECTOR3 out;
	D3DXVec3TransformCoord(&out,&this->Muzzle,&this->transform->Get_MtxWorld());
	return out;
}

void CGun::Set_Muzzle(D3DXVECTOR3 position)
{
	this->Muzzle = position;
}

void CGun::render()
{
	NRender3D::Render(this->mesh, this->transform);
}

void CGun::Burst(D3DXVECTOR3 target,float x)
{
	if (this->wait >= this->rate)
	{
		CBullet::Create(this->Get_Muzzle(), target, x);
		this->wait = 0;
		this->Shake += GUN_SHAKE_VAR * 1.5f;
	}
}

void CGun::Update()
{
	this->wait++;
}
