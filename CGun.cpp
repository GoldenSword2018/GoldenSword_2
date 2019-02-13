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
GunData* CGun::Index[CGun::END];

//===============================================
//	GunData_tag
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
GunData_tag::GunData_tag(
	NRender3D::CGameObject* Model,
	D3DXVECTOR3 SightPos,
	D3DXVECTOR3 MuzzlePos,
	D3DXVECTOR3 UnderBarrel,
	D3DXVECTOR3 Magazine,
	float Rate,
	float Recoil,
	int BulletNum,
	D3DXVECTOR3 Muzzle,
	D3DXVECTOR3 Grip
):
	Model(Model),
	SightPos(SightPos),
	MuzzlePos(MuzzlePos),
	UnderBarrel(UnderBarrel),
	Magazine(Magazine),
	Rate(Rate),
	Recoil(Recoil),
	Max_BulletNum(BulletNum),
	Muzzle(Muzzle),
	Grip(Grip)
{

}

//===============================================
//	CGun
//===============================================

//-------------------------------------
//	メンバ関数名
//-------------------------------------

void CGun::InitLoad()
{
	Index[CGun::HANDGUN] = new GunData(
		new NRender3D::CGameObject(
			new CTransform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }),
			new CXModelName(NModel::GUN)
		),
		D3DXVECTOR3(0.0f, 2.5f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		10.0f,
		0.0f,
		10,
		D3DXVECTOR3(0.0f, 0.0f, 9.5f),
		D3DXVECTOR3(0.0f, 0.0f, 0.0f)
	);
}

void CGun::FinalUnLoad()
{
	for(int i = 0; i<CGun::END; i++)
	{
		delete Index[i];
	}
}

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CGun::CGun(CTransform* transform,TYPE type)
:
	m_Sight( NULL ),
	m_type(type),
	m_Rate(Index[type]->Rate),
	m_Recoil(Index[type]->Recoil),
	m_Max_BulletNum(Index[type]->Max_BulletNum),
	m_Muzzle(Index[type]->Muzzle)
{
	this->transform = transform;
	this->mesh = NULL;
	m_wait = 0;
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CGun::~CGun()
{

}

//-------------------------------------
//	射撃
//-------------------------------------
void CGun::Burst(D3DXVECTOR3 target,float x)
{
	if (this->m_wait >= this->m_Rate)
	{
		CBullet::Create(this->Get_Muzzle(), target, x);
		this->m_wait = 0;
	}
}

//-------------------------------------
//	更新
//-------------------------------------
void CGun::Update()
{
	this->m_wait++;
}

//-------------------------------------
//	描画
//-------------------------------------
void CGun::render()
{
	NRender3D::Render(Index[this->m_type]->Model->mesh,&this->transform->Get_MtxWorld());

	if(this->m_Sight != NULL)	this->m_Sight->render();
}


//-------------------------------------
//	銃口取得
//-------------------------------------
D3DXVECTOR3 CGun::Get_Muzzle()
{
	D3DXVECTOR3 out;
	D3DXVec3TransformCoord(&out, &this->m_Muzzle, &this->transform->Get_MtxWorld());
	return out;
}

//-------------------------------------
//	サイトを設定
//-------------------------------------
void CGun::Set(CSight::TYPE type)
{
	if(this->m_Sight != nullptr || this->m_Sight != NULL)
	{
		delete this->m_Sight;
		this->m_Sight = NULL;
	}

	this->m_Sight = new CSight();
	this->m_Sight->Set(this->transform,Index[this->m_type]->SightPos,type);

	return;
}

//-------------------------------------
//	タイプを設定
//-------------------------------------
void CGun::Set(TYPE Type)
{
	this->m_type = Type;
	this->m_Muzzle = Index[Type]->Muzzle;
	this->transform->Set_Position(Index[Type]->Grip);
}

