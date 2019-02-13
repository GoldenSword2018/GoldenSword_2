// ===============================================================================================
// �v���W�F�N�g��: 
// �t�@�C����: Collider.h
// �쐬�� XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// �ǋL:                                                                                        
// MM/DD/YYYY Author: ����                                                                      
// �E�~�~�̕ύX�`�`�`�`                                                                         
// ===============================================================================================

#ifndef _COLLIDER_H_
#define _COLLIDER_H_
#pragma once

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// �C���N���[�h�t�@�C��
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//
// Windows�n
// 
#include <d3dx9.h>

// 
// ����n
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
	Shape() {} // �ǂ��ɂ����Čp���悪�f�t�H���g�R���X�g���N�^�Ő�������Ȃ��悤�ɂ������B
public:
	Shape( CTransform* pParentTransform, SHAPE_TYPE ShapeType, D3DCOLOR Color );
	Shape( CTransform* pParentTransform, SHAPE_TYPE ShapeType );
	virtual ~Shape();
public:
	CTransform* pParentTransform;
	D3DCOLOR	Color;
public: // ���蔲���h�~�p ���A�V���W
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
	D3DXVECTOR3 NormalDirect[ 3 ]; // 0:�O, 1:�E, 2: �� �P�ʃx�N�g��
	float Length[ 3 ];// 0:���s, 1:��, 2:���� ���ꂼ��̔���
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
/* +++++++++++++++ ���L<��> +++++++++++++++ */
/* ----- ���L<��> -----*/
// ���L<��>

#endif // _COLLIDER_H_