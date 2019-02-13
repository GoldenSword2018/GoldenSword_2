// ===============================================================================================
// プロジェクト名: 
// ファイル名: Collider.cpp
// 概要: 
// 作成日 XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// 追記:                                                                                        
// MM/DD/YYYY Author: ○○                                                                      
// ・××の変更～～～～                                                                         
// ===============================================================================================

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// インクルードファイル
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#include "Collider.h"
//
// Windows系
// 

// 
// 自作系
//


// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// Shapeファミリー 
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#define COLLISION_SHAPE_DEFAULT_POS	( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) )
#define COLLISION_SHAPE_DEFAULT_COLOR ( D3DCOLOR_RGBA( 255, 255, 255, 255 ))

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// Shapeファミリー 
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

// --------------------------------------------------------------------------------------
//
// クラス: Shape
//
// --------------------------------------------------------------------------------------

Shape::Shape( CTransform* init_pParentTransform, SHAPE_TYPE init_ShapeType, D3DCOLOR init_Color )
	:
	pParentTransform( init_pParentTransform ),
	ShapeType( init_ShapeType ),
	Color( init_Color )
{
	pParentTransform = init_pParentTransform;
}
Shape::Shape( CTransform* init_pParentTransform, SHAPE_TYPE init_ShapeType )
	:
	Shape( init_pParentTransform, init_ShapeType, COLLISION_SHAPE_DEFAULT_COLOR )
{

}
Shape::~Shape()
{
	// null
}


//-------------------------------------
// 実効座標を戻す関数
//-------------------------------------

D3DXVECTOR3 Shape::GetEffectivePos( void )const
{
	return pParentTransform->Get_Position(); // ここやばいかも
}

// --------------------------------------------------------------------------------------
//
// クラス: ShapeSphere
//
// --------------------------------------------------------------------------------------

//
//  コンストラクタ デストラクタ
//

ShapeSphere::ShapeSphere( CTransform* init_pParentTransform, float init_Radius )
	: Shape( init_pParentTransform, SHAPE_TYPE::SPHERE ),
	Radius( init_Radius )
{

}
ShapeSphere::~ShapeSphere()
{
	// null
}

//
// デバッグ描画
// 
void ShapeSphere::DebugDraw()
{
	// DebugCollisionModule::GetInstance()->BatchDraw( this );
}
//===============================================
//	ShapeOBB クラス
//===============================================

// --------------------------------------------------------------------------------------
//
// クラス: ShapeOBB
//
// --------------------------------------------------------------------------------------
//
//  コンストラクタ デストラクタ
//

// arg0: 持ち主の座標ポインタ, arg1: 各座標軸回りの角度(ラジアン) 回す順番 Roll->Pitch->Yaw
// arg2: x幅, y高さ, z奥行, arg3: 当たり判定の座標との差分
ShapeOBB::ShapeOBB( CTransform* init_pParentTransform, D3DXVECTOR3* init_pRadian, D3DXVECTOR3* init_pLength )
	: Shape( init_pParentTransform, SHAPE_TYPE::OBB )
{
	D3DXMATRIX mtxRot;
	D3DXMatrixRotationYawPitchRoll( &mtxRot, D3DXToRadian( init_pRadian->y ), D3DXToRadian( init_pRadian->x ), D3DXToRadian( init_pRadian->z ) );

	// 前向きの単位ベクトルを作成
	NormalDirect[ OBB_VECTOR_FORWARD ] = D3DXVECTOR3( 0.0f, 0.0f, 1.0f );
	D3DXVec3TransformNormal( &NormalDirect[ OBB_VECTOR_FORWARD ], &NormalDirect[ OBB_VECTOR_FORWARD ], &mtxRot );
	D3DXVec3Normalize( &NormalDirect[ OBB_VECTOR_FORWARD ], &NormalDirect[ OBB_VECTOR_FORWARD ] );


	// 右向きの単位ベクトルを作成
	NormalDirect[ OBB_VECTOR_RIGHT ] = D3DXVECTOR3( 1.0f, 0.0f, 0.0f );
	D3DXVec3TransformNormal( &NormalDirect[ OBB_VECTOR_RIGHT ], &NormalDirect[ OBB_VECTOR_RIGHT ], &mtxRot );
	D3DXVec3Normalize( &NormalDirect[ OBB_VECTOR_RIGHT ], &NormalDirect[ OBB_VECTOR_RIGHT ] );

	// 上向きの単位ベクトルを作成
	NormalDirect[ OBB_VECTOR_UP ] = D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	D3DXVec3TransformNormal( &NormalDirect[ OBB_VECTOR_UP ], &NormalDirect[ OBB_VECTOR_UP ], &mtxRot );
	D3DXVec3Normalize( &NormalDirect[ OBB_VECTOR_UP ], &NormalDirect[ OBB_VECTOR_UP ] );


	// 各向きの長さを指定
	Length[ OBB_VECTOR_FORWARD ] = init_pLength->z / 2.0f;
	Length[ OBB_VECTOR_RIGHT ] = init_pLength->x / 2.0f;
	Length[ OBB_VECTOR_UP ] = init_pLength->y / 2.0f;
}

ShapeOBB::~ShapeOBB()
{
	// null
}

//-------------------------------------
//  デバッグ描画
//-------------------------------------
void ShapeOBB::DebugDraw()
{
	// DebugCollisionModule::GetInstance()->BatchDraw( this );
}
//===============================================
//	Collision クラス
//===============================================


namespace CollisionCheckHelper
{

bool SphereVsSphere( ShapeSphere& Sphere0, ShapeSphere& Sphere1 )
{
	D3DXVECTOR3 vecLength = Sphere1.GetEffectivePos() - Sphere0.GetEffectivePos();
	float fLength = D3DXVec3LengthSq( &vecLength ); // 二つの中心座標の距離

	if( ( Sphere0.Radius + Sphere1.Radius ) * ( Sphere0.Radius + Sphere1.Radius ) > fLength )
	{ // hit 
		return true;
	}
	else
	{ // no hit
		return false;
	}
}

bool OBBVsOBB( ShapeOBB& OBB0, ShapeOBB& OBB1 )
{
	// 各方向ベクトルの確保
	// （N***:標準化方向ベクトル）
	D3DXVECTOR3 NAe1 = OBB0.NormalDirect[ 0 ], Ae1 = NAe1 * OBB0.Length[ 0 ];
	D3DXVECTOR3 NAe2 = OBB0.NormalDirect[ 1 ], Ae2 = NAe2 * OBB0.Length[ 1 ];
	D3DXVECTOR3 NAe3 = OBB0.NormalDirect[ 2 ], Ae3 = NAe3 * OBB0.Length[ 2 ];
	D3DXVECTOR3 NBe1 = OBB1.NormalDirect[ 0 ], Be1 = NBe1 * OBB1.Length[ 0 ];
	D3DXVECTOR3 NBe2 = OBB1.NormalDirect[ 1 ], Be2 = NBe2 * OBB1.Length[ 1 ];
	D3DXVECTOR3 NBe3 = OBB1.NormalDirect[ 2 ], Be3 = NBe3 * OBB1.Length[ 2 ];
	D3DXVECTOR3 Interval = OBB0.GetEffectivePos() - OBB1.GetEffectivePos();

	// 分離軸 : Ae1
	float rA = D3DXVec3Length( &Ae1 );
	float rB = LenSegOnSeparateAxis( &NAe1, &Be1, &Be2, &Be3 );
	float L = fabs( D3DXVec3Dot( &Interval, &NAe1 ) );
	if( L > rA + rB )
		return false; // 衝突していない

					  // 分離軸 : Ae2
	rA = D3DXVec3Length( &Ae2 );
	rB = LenSegOnSeparateAxis( &NAe2, &Be1, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &NAe2 ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : Ae3
	rA = D3DXVec3Length( &Ae3 );
	rB = LenSegOnSeparateAxis( &NAe3, &Be1, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &NAe3 ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : Be1
	rA = LenSegOnSeparateAxis( &NBe1, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be1 );
	L = fabs( D3DXVec3Dot( &Interval, &NBe1 ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : Be2
	rA = LenSegOnSeparateAxis( &NBe2, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be2 );
	L = fabs( D3DXVec3Dot( &Interval, &NBe2 ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : Be3
	rA = LenSegOnSeparateAxis( &NBe3, &Ae1, &Ae2, &Ae3 );
	rB = D3DXVec3Length( &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &NBe3 ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C11
	D3DXVECTOR3 Cross;
	D3DXVec3Cross( &Cross, &NAe1, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C12
	D3DXVec3Cross( &Cross, &NAe1, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C13
	D3DXVec3Cross( &Cross, &NAe1, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae2, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C21
	D3DXVec3Cross( &Cross, &NAe2, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C22
	D3DXVec3Cross( &Cross, &NAe2, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C23
	D3DXVec3Cross( &Cross, &NAe2, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae3 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C31
	D3DXVec3Cross( &Cross, &NAe3, &NBe1 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be2, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C32
	D3DXVec3Cross( &Cross, &NAe3, &NBe2 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be3 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離軸 : C33
	D3DXVec3Cross( &Cross, &NAe3, &NBe3 );
	rA = LenSegOnSeparateAxis( &Cross, &Ae1, &Ae2 );
	rB = LenSegOnSeparateAxis( &Cross, &Be1, &Be2 );
	L = fabs( D3DXVec3Dot( &Interval, &Cross ) );
	if( L > rA + rB )
		return false;

	// 分離平面が存在しないので「衝突している」
	return true;
}

// 分離軸に投影された軸成分から投影線分長を算出
float LenSegOnSeparateAxis( D3DXVECTOR3 *Sep, D3DXVECTOR3 *e1, D3DXVECTOR3 *e2, D3DXVECTOR3 *e3 )
{
	// 3つの内積の絶対値の和で投影線分長を計算
	// 分離軸Sepは標準化されていること
	float r1 = fabs( D3DXVec3Dot( Sep, e1 ) );
	float r2 = fabs( D3DXVec3Dot( Sep, e2 ) );
	float r3 = e3 ? ( fabs( D3DXVec3Dot( Sep, e3 ) ) ) : 0;
	return r1 + r2 + r3;
}

}
/* +++++++++++++++ 注記<大> +++++++++++++++ */
/* ----- 注記<中> -----*/
// 注記<小>

/* ----- 関数名 XXXXXXXXXXXXXXXXXXXX ------------------------------------------------- */
/* 概要 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  */
/* 戻り値: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX　　　　　　　　　　　*/
/* arg0: Type VariableName 概要                                                        */
/* ----------------------------------------------------------------------------------- */

//ReturnType FunctionName( Type arg0... )
// {
//     /* ----- 処理開始 ----- */
//     int XXXXX = NULL// 概要
//     Func01() // 動作概要
//     a = Func02();
//         // 関数名
//         // 概要: XXXX
//         // 戻値: XXXXXX
//     Func03( arg0, // 型　引数名 概要
//             arg1, // 型　引数名 概要
//             arg2 );

// }