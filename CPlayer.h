//
//	CPlayer.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CPLAYER_H
#define CPLAYER_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include"CGameObject.h"

//================================================
//	マクロ定義	define
//================================================
#define SPEED_WALK (0.05f)
#define SPEED_RUN  (0.08f)

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

#include"CCamera.h"
#include"CGun.h"

#include<d3dx9.h>

class CPlayer :public NRender3D::CGameObject
{
public:
	Camera Camera;
	CGun* Gun;

public:
	float Aty;
	float Speed;
	bool bLean;		//[ true = 右 / false = 左 ]

public:
	CPlayer(CTransform* transform, AMesh* mesh,CGun* Gun);
	~CPlayer();

public:
	void Update();
	void Render();
};

void CameraBehavior(CPlayer* const player, D3DXVECTOR3 Distance);
void Set_GunRotate(CPlayer* const player);

#endif