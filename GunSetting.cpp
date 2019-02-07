//
//	GunSetting.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//
//図形から予想外なアイデア
//動詞。述語。形容動詞。
//代用が効く図形は無し。
//今までに大賞で使われたものは危ない
//

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#define _USE_MATH_DEFINES
#include<math.h>

#include"GunSetting.h"
//class
#include"Input.h"

//Assets
#include"MeshField.h"
#include"CGun.h"
#include"CGameObject.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	クラス名		class
//===============================================
static GunSetting Scene;
static CGun* GunObject;
static NRender3D::CGameObject*  Sight;

//Assets
static ViewCamera* MainCamera;

void GunSetting::Initialize()
{
	MainCamera = new ViewCamera(
		{0.0f,5.0f,-5.0f},
		{0.0f,0.0f,0.0f},
		10.0f,
		CAMERA_FOV
	);

	GunObject = new CGun(
		new CTransform(
			{0.0f,0.0f,0.0f},
			{0.5f,0.5f,0.5f},
			{0.0f,(float)M_PI_2,0.0f}
		),
		{0.0f,0.0f,0.0f},
		10,
		10
	);
	GunObject->Sight = {0.0f,2.5f,0.0f};

	Sight = new NRender3D::CGameObject(
		new CTransform(
			{0.0f,0.0f,0.0f},
			{0.5f,0.5f,0.5f},
			{0.0f,0.0f,0.0f}
		),
		new CXModelName(NModel::SIGHT)
	);

	Sight->transform->Set_Parent(GunObject->transform);
	Sight->transform->Set_Position(GunObject->Sight);

	MainCamera->at = GunObject->transform->Get_Position();
	MainCamera->Set_Main();
}

void GunSetting::UpdateBegin()
{
	MainCamera->Update();
}

void GunSetting::Render()
{
	NMeshField::Render_Shpere({ 0.0f,0.0f,0.0f }, NTexture::MeshField_Sky);
	GunObject->render();
	NRender3D::Render(Sight->mesh,Sight->transform);
}

void GunSetting::UpdateEnd()
{

}

void GunSetting::Finalize()
{

}

NSCENE::AScene* Get_GunSetting()
{
	return &Scene;
}

//-------------------------------------
//	Camera
//-------------------------------------
ViewCamera::ViewCamera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov)
:
	ACamera(Position,At,AtDistance,fov)
{

}

ViewCamera::~ViewCamera()
{

}

void ViewCamera::Update()
{
	this->m_Rotation.y += Mouse_IsAccelerationX() * 0.001f;
	this->atDistance += Mouse_IsAccelerationZ() * 0.001f;

	this->position = this->at - (this->Get_Forward()* this->atDistance);
}
