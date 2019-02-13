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
#define _USE_MATH_DEFINES
#include<math.h>

#include"GunSetting.h"
//class
#include"Input.h"

//Assets
#include"MeshField.h"
#include"CGun.h"
#include"CGameObject.h"

#include"Fade.h"

#include"GameScene.h"

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

//Assets
static ViewCamera* MainCamera;

void GunSetting::Initialize()
{
	CSight::InitLoad();
	CGun::InitLoad();

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
		CGun::HANDGUN
	);
	
	MainCamera->at = GunObject->transform->Get_Position();
	MainCamera->Set_Main();

	GunObject->Set(CSight::NORMAL);
	GunObject->Set(CGun::HANDGUN);

	Fade_Triger(false,10,D3DCOLOR_RGBA(255,255,255,0));
}

void GunSetting::UpdateBegin()
{
	MainCamera->Update();

	if(Keyboard_IsTrigger(DIK_1))
	{
		GunObject->Set(CSight::NORMAL);
	}

	if(Keyboard_IsTrigger(DIK_2))
	{
		GunObject->Set(CSight::OPTICAL);
	}

	if(Keyboard_IsPress(DIK_SPACE))
	{
		NSCENE::LoadScene(Get_GameScene());
	}


	if (Mouse_IsLeftDown())
	{
		GunObject->transform->Rotation()->y += Mouse_IsAccelerationX() * 0.001f;
	}
}

void GunSetting::Render()
{
	NMeshField::Render_Shpere({ 0.0f,0.0f,0.0f }, NTexture::MeshField_Sky);
	GunObject->render();
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

CGun* Get_Gun()
{
	return GunObject;
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
