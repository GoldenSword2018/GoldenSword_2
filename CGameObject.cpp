//
//	CGameObject.cpp
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
#include"CGameObject.h"
//class

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
namespace NRender3D
{
	CGameObject::CGameObject()
	{
	
	}

	CGameObject::CGameObject(CTransform* transform, AMesh* mesh)
	{
		this->transform = transform;
		this->mesh = mesh;
	}

	CGameObject::~CGameObject()
	{
		delete this->transform;
		delete this->mesh;
	}

	void CGameObject::render()
	{
		NRender3D::Render(this->mesh,this->transform);
	}
}