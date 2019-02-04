//
//	CBullert.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CBULLET_H
#define CBULLET_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include"CGameObject.h"
#include"CCollision.h"

//================================================
//	マクロ定義	define
//================================================
#define BULLET_SPEED (1.0f)
#define BULLET_NUM (256)

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

class CBullet:public NRender3D::CGameObject
{
private:
	NTexture::CAnimation animation;
public:
	bool bEnable;
	int frame;
	Collision::Sphere ColSphere;
public:
	//コンストラクタ
	CBullet();
	~CBullet();

public:
	static void Initialize();
	static void Render();
	static void Update();
	static void Finalize();

public:
	static void Create(D3DXVECTOR3 position,D3DXVECTOR3 at,float x);

public:
	void update();
	void render();
	void destroy();
	void hit();
};

CBullet* Get_Bullet(int num);
bool Get_BulletIsEnable(int num);

#endif