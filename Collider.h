// ===============================================================================================
// プロジェクト名: 
// ファイル名: Collider.h
// 作成日 XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// 追記:                                                                                        
// MM/DD/YYYY Author: ○○                                                                      
// ・××の変更～～～～                                                                         
// ===============================================================================================

#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#pragma once

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// インクルードファイル
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//
// Windows系
// 
#include <d3dx9.h>

// 
// 自作系
//
#include "CTransform.h"

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// 
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

#define OBB_VECTOR_FORWARD		( 0 )
#define OBB_VECTOR_RIGHT		( 1 )
#define OBB_VECTOR_UP			( 2 )
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// 
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
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
	Shape( CTransform* pParentTransform, SHAPE_TYPE ShapeType, D3DCOLOR Color );
	Shape( CTransform* pParentTransform, SHAPE_TYPE ShapeType );
	virtual ~Shape();
public:
	CTransform* pParentTransform;
	D3DCOLOR	Color;
public: // すり抜け防止用 旧、新座標
	D3DXVECTOR3 OriginalPos;
	D3DXVECTOR3 NewPos;

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
	ShapeSphere( CTransform* pParentTransform, float Radius );
	~ShapeSphere();
public:
	void DebugDraw();
};

//-------------------------------------
class ShapeOBB : public Shape
{
public:
	D3DXVECTOR3 NormalDirect[ 3 ]; // 0:前, 1:右, 2: 上 単位ベクトル
	float Length[ 3 ];// 0:奥行, 1:幅, 2:高さ それぞれの半分
private:
	ShapeOBB() {}

public:
	ShapeOBB( CTransform* pParentTransform, D3DXVECTOR3* pRadian, D3DXVECTOR3* Length );
	~ShapeOBB();
public:
	void DebugDraw();
};

/*
* Collsion Class
*/
namespace CollisionCheckHelper
{
float LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 = 0 );

bool SphereVsSphere( ShapeSphere& Sphere0, ShapeSphere& Sphere1 );
bool OBBVsSphere( ShapeOBB& OBB, ShapeSphere& Sphere );
bool OBBVsOBB( ShapeOBB& OBB0, ShapeOBB& OBB1 );
}
/* +++++++++++++++ 注記<大> +++++++++++++++ */
/* ----- 注記<中> -----*/
// 注記<小>

#endif // _COLLIDER_H_