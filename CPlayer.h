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

class APlayer:public NRender3D::CGameObject
{
public:
	APlayer();
	~APlayer();
public:
	void Update();
	void Render();
};

class GunPlayer:public APlayer
{

};

//-------------------------------------
//	クラス名
//-------------------------------------

#endif