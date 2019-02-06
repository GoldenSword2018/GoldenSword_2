//
//	GunSetting.cpp
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

#include"GunSetting.h"
//class

//Assets
#include"MeshField.h"

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

//Assets
static ViewCamera* MainCamera;
static OperationCamera OpCamea;

void GunSetting::Initialize()
{
	MainCamera = new ViewCamera(
		{0.0f,5.0f,-5.0f},
		{0.0f,0.0f,0.0f},
		10.0f,
		CAMERA_FOV
	);

	MainCamera->Set_Main();
	OpCamea.Set_Main();
}

void GunSetting::UpdateBegin()
{
	MainCamera->Update();
	OpCamea.Update();
}

void GunSetting::Render()
{
	NMeshField::Render_Shpere({0.0f,0.0f,0.0f},NTexture::MeshField_Sky);
	//NMeshField::Render_SkyDome({0.0f,0.0f,0.0f},NTexture::MeshField_Sky);

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
	this->position = this->at - (this->Get_Forward()* this->atDistance);
}
