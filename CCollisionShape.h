//
//	CCollisionableObject.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CCOLLISIONABLEOBJECT_H
#define CCOLLISIONABLEOBJECT_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"

//Class
#include "CGameObject.h"

//================================================
//	�}�N����`	define
//================================================


#define OBB_VECTOR_FORWARD		( 0 )
#define OBB_VECTOR_RIGHT		( 1 )
#define OBB_VECTOR_UP			( 2 )
//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
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
	Shape() {} // �ǂ��ɂ����Čp���悪�f�t�H���g�R���X�g���N�^�Ő�������Ȃ��悤�ɂ������B
public:
	Shape( CTransform* pParentTransform, D3DXVECTOR3* pGapPos, SHAPE_TYPE ShapeType, D3DCOLOR Color );
	Shape( CTransform* pParentTransform, D3DXVECTOR3* pGapPos, SHAPE_TYPE ShapeType );
	Shape( CTransform* pParentTransform, SHAPE_TYPE ShapeType );
	virtual ~Shape();
public:
	CTransform* pParentTransform;
	D3DXVECTOR3	GapPos; // ������Ƃ̈ʒu�̕␳�i�I�u�W�F�N�g�������炸�炷�j
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
	D3DXVECTOR3 NormalDirect[ 3 ]; // 0:�O, 1:�E, 2: �� �P�ʃx�N�g��
	float Length[3];// 0:���s, 1:��, 2:���� ���ꂼ��̔���
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

void Collision_PushBack(ShapeOBB *pShapeMovable, ShapeOBB *pShapeStable);

#endif