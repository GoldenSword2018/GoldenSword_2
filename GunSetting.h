//
//	GunSetting.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef GUNSETTING_H
#define GUNSETTING_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include"Scene.h"
#include"CCamera.h"

#include"CGun.h"

//================================================
//	マクロ定義	define
//================================================


//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//================================================
//	クラス		class
//================================================

//-------------------------------------
//	Scene
//-------------------------------------
class GunSetting:public NSCENE::AScene
{
public:
	GunSetting() :AScene("GunSetting") {};
public:
	void Initialize() override;
	void UpdateBegin() override;
	void Render() override;
	void UpdateEnd() override;
	void Finalize() override;
};

NSCENE::AScene* Get_GunSetting();
CGun* Get_Gun();

//-------------------------------------
//	Camera
//-------------------------------------
class ViewCamera:public ACamera
{
public:
	ViewCamera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov);
	~ViewCamera();
public:
	void Update() override;
};

#endif