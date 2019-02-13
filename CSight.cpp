//
//	Sight.cpp
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

#include"CSight.h"
using namespace NRender3D;
//class

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	ロード定義
//===============================================


//===============================================
//	グローバル変数	global
//===============================================

//Index
//@ transform : CSightからの移動量 モデルの中心ズレを治す目的
//@ mesh		 : Modelデータ
CGameObject* CSight::Index[CSight::END];

//===============================================
//	クラス名		class
//===============================================
void CSight::InitLoad()
{
	Index[NORMAL] = new CGameObject(
		new CTransform({ 0.0f,0.0f,0.0f }, { 0.7f,0.7f,0.7f }, { 0.0f,0.0f,0.0f }),
		new CXModelMesh("sight.x", "Sight")
	);

	Index[OPTICAL] = new CGameObject(
		new CTransform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }),
		new CXModelMesh("sight2.x", "Sight")
	);
}

void CSight::FinalLoad()
{
	for (int i = 0; i < CSight::END; i++)
	{
		delete Index[i];
	}
}


CGameObject CSight::Get_SightObj(TYPE type)
{
	return *Index[type];
}


//-------------------------------------
//	メンバ関数名
//-------------------------------------
CSight::CSight()
:
	CGameObject(
		new CTransform(),
		NULL
	)
{

}



CSight::~CSight()
{

}

//親,距離,サイト種類
void CSight::Set(CTransform* parent,D3DXVECTOR3 distance,TYPE type)
{
	this->m_type = type;
	*this->transform = *Index[type]->transform;
	this->transform->Set_Parent(parent);

	D3DXVECTOR3 vec1 = distance;
	D3DXVECTOR3 vec2 = *Index[type]->transform->Position();

	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;

	this->transform->Set_Position(vec1);
}

void CSight::Set(TYPE type)
{
	this->m_type = type;
}

void CSight::render()
{
	D3DXMATRIX MtxWorld;
	MtxWorld = Index[m_type]->transform->Get_MtxWorld() * this->transform->Get_MtxWorld();

	NRender3D::Render(Index[m_type]->mesh,&MtxWorld);
}