//
//	CCollisionableObject.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CCOLLISIONABLEOBJECT_H
#define CCOLLISIONABLEOBJECT_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include "CGameObject.h"

//================================================
//	マクロ定義	define
//================================================


#define OBB_VECTOR_FORWARD		( 0 )
#define OBB_VECTOR_RIGHT		( 1 )
#define OBB_VECTOR_UP			( 2 )
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

/*
 * Shape Crustor
 */
class Shape
{
public:
	enum SHAPE_TYPE
	{
		SPHERE = 0,
		OBB,
		NO_TYPE,
		/* MAX ENUM */
		COLLISION_SHAPE_TYPE_ENUM_MAX
	};
public:
	SHAPE_TYPE ShapeType;
public:
	Shape() {} // どうにかして継承先がデフォルトコンストラクタで生成されないようにしたい。
public:
	Shape( CTransform* pParentTransform, D3DXVECTOR3* pGapPos, SHAPE_TYPE ShapeType, D3DCOLOR Color );
	Shape( CTransform* pParentTransform, D3DXVECTOR3* pGapPos, SHAPE_TYPE ShapeType );
	Shape( CTransform* pParentTransform, SHAPE_TYPE ShapeType );
	virtual ~Shape();
public:
	CTransform* pParentTransform;
	D3DXVECTOR3	GapPos; // 持ち主との位置の補正（オブジェクト中央からずらす）
	D3DCOLOR	Color;
public:
	D3DXVECTOR3 GetEffectivePos( void )const;
public:
	virtual void DebugDraw() = 0;
};

//-------------------------------------
class ShapeSphere : public Shape
{
public:
	float Radius;
private:
	ShapeSphere() {}
public:
	ShapeSphere( CTransform* pParentTransform, float Radius, D3DXVECTOR3* pGapPos = &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ));
	~ShapeSphere();
public:
	void DebugDraw();
};

//-------------------------------------
class ShapeOBB : public Shape 
{
public:
	D3DXVECTOR3 NormalDirect[ 3 ]; // 0:前, 1:右, 2: 上 単位ベクトル
	float Length[3];// 0:奥行, 1:幅, 2:高さ それぞれの半分
private:
	ShapeOBB() {}
	
public:
	ShapeOBB( CTransform* pParentTransform, D3DXVECTOR3* pRadian, D3DXVECTOR3* Length,D3DXVECTOR3* pGapPos = &D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );
	~ShapeOBB();
public:
	void DebugDraw();
};

/*
 * Collsion Class
 */

class CollisionCheck
{
private:
	static float LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0 );
public:
	static bool SphereVsSphere( ShapeSphere& Sphere0, ShapeSphere& Sphere1 );
	static bool OBBVsSphere(ShapeOBB& OBB, ShapeSphere& Sphere) {};
	static bool OBBVsOBB( ShapeOBB& OBB0, ShapeOBB& OBB1 );
};
//-------------------------------------
//	クラス名
//-------------------------------------

#endif