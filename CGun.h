//
//	CGun.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CGUN_H
#define CGUN_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include"CGameObject.h"

//================================================
//	マクロ定義	define
//================================================
#define GUN_SHAKE (20)			//ブレ
#define GUN_SHAKE_VAR (1)		//ブレ変化値
#define GUN_SHAKE_MAG (0.1f)	//ブレ倍率

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

class CGun:public NRender3D::CGameObject
{
private:
	D3DXVECTOR3 Muzzle;		//弾口位置

private:
	int rate;		//レート(frame)
	int wait;		//待機(frame)
	int BulletNum;	//弾数
	int Shake;		//ブレ (x0.1)

public:
	CGun();
	// ・位置情報 ・銃口位置 ・弾数 ・射撃速度
	CGun(CTransform* transform,D3DXVECTOR3 Muzzle,int BulletNum,int rate);
	~CGun();

public:
	void Update();

public:
	D3DXVECTOR3 Get_Muzzle();
	void Set_Muzzle(D3DXVECTOR3 position);
	void render();
	void Burst(D3DXVECTOR3 target, float x);
};


#endif