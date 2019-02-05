//
//	DebuCircle.cpp
//		Author:YU NISHIMAKI		DATE:2018/10/18
//===============================================
//	変更者 Changed By
//		Name: Yuto Hashimoto	DATE:2018/11/13
//  用意するバッファ領域の数を訂正.
//  CuboidはColorメンバを用いて色付けするように変更.
//
//-----------------------------------------------
#include<d3dx9.h>
#include"System.h"
#include"Debug_Collision.h"


//===============================================
//	マクロ定義
//===============================================
// Sphere
#define CIRCLE_VERTEX_COUNT		(16)
#define CIRCLE_DRAW_MAX			(2048)

// Cuboid
#define CUBOID_VERTEX_COUNT     ( 8 )
#define CUBOID_EDGE_COUNT       ( 12 )
#define CUBOID_POINT_COUNT_PER_EDGE    ( 2 )
#define CUBOID_DRAW_MAX			( 10000 )
//===============================================
//	構造体
//===============================================
#define FVF_DEBUG_VERTEX	(D3DFVF_XYZ | D3DFVF_DIFFUSE)



//===============================================
//	グローバル変数
//===============================================

DebugCollisionModule* DebugCollisionModule::pInstance = NULL;

DebugCollisionModule::DebugCollisionModule()
{
#if defined(_DEBUG) || defined(DEBUG)
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	// 球用のバッファ確保
	// 円を3軸分書くので用意するバッファ領域は3倍
	pDevice->CreateVertexBuffer( sizeof( DebugVertex ) * CIRCLE_VERTEX_COUNT * CIRCLE_DRAW_MAX * 3, D3DUSAGE_WRITEONLY, FVF_DEBUG_VERTEX, D3DPOOL_MANAGED, &pSphereVertexBuffer, NULL );
	pDevice->CreateIndexBuffer( sizeof( WORD ) * ( CIRCLE_VERTEX_COUNT * 2 ) *  CIRCLE_DRAW_MAX * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pSphereIndexBuffer, NULL );
	SphereCount = 0;

	// Cuboid用のバッファ確保
	pDevice->CreateVertexBuffer( sizeof( DebugVertex ) * CUBOID_VERTEX_COUNT * CUBOID_DRAW_MAX, D3DUSAGE_WRITEONLY, FVF_DEBUG_VERTEX, D3DPOOL_MANAGED, &pCuboidVertexBuffer, NULL );
	pDevice->CreateIndexBuffer( sizeof( WORD ) * CUBOID_EDGE_COUNT * CUBOID_POINT_COUNT_PER_EDGE * CUBOID_DRAW_MAX, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pCuboidIndexBuffer, NULL );
	CuboidCount = 0;
#endif // _DEBUG || DEBUG
}
/*
* デストラクタ
*/
DebugCollisionModule::~DebugCollisionModule()
{
#if defined(_DEBUG) || defined(DEBUG)

	if( pSphereIndexBuffer )
	{
		pSphereIndexBuffer->Release();
		pSphereIndexBuffer = NULL;
	}


	if( pSphereVertexBuffer )
	{
		pSphereVertexBuffer->Release();
		pSphereVertexBuffer = NULL;
	}
	if( pCuboidVertexBuffer )
	{
		pCuboidVertexBuffer->Release();
		pCuboidVertexBuffer = NULL;
	}
	if( pCuboidIndexBuffer )
	{
		pCuboidIndexBuffer->Release();
		pCuboidIndexBuffer = NULL;
	}
#endif // _DEBUG || DEBUG
}

/*
 * 関数
 */

DebugCollisionModule* DebugCollisionModule::GetInstance( void )
{
#if defined(_DEBUG) || defined(DEBUG)
	if( !DebugCollisionModule::pInstance )
	{
		pInstance = new DebugCollisionModule;
	}

	return pInstance;
#endif // _DEBUG || DEBUG
	return NULL;
}
void DebugCollisionModule::Finalize( void )
{
#if defined(_DEBUG) || defined(DEBUG)
	delete pInstance;
#endif // _DEBUG || DEBUG
}

/*
 * 描画対象の登録
 */
void DebugCollisionModule::BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)
	Sphere_BatchBegin();
	Cuboid_BatchBegin();
#endif // _DEBUG || DEBUG
}

void DebugCollisionModule::BatchRun( void )
{
#if defined(_DEBUG) || defined(DEBUG)
	Sphere_BatchRun();
	Cuboid_BatchRun();
#endif // _DEBUG || DEBUG
}

//-------------------------------------
//	Sphere
//-------------------------------------


/*
 * 描画開始 : 終了
 */
void DebugCollisionModule::Sphere_BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	SphereCount = 0;

	pSphereVertexBuffer->Lock( 0, 0, (void**) &pSphereVertex, 0 );
	pSphereIndexBuffer->Lock( 0, 0, (void**) &pSphereVertexIndex, 0 );

#endif // _DEBUG || DEBUG
}

void DebugCollisionModule::Sphere_BatchRun( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxTransform;
	D3DXMatrixIdentity( &mtxTransform );
	pDevice->SetTransform( D3DTS_WORLD, &mtxTransform );

	pSphereVertexBuffer->Unlock();
	pSphereIndexBuffer->Unlock();

	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( FVF_DEBUG_VERTEX );
	pDevice->SetStreamSource( 0, pSphereVertexBuffer, 0, sizeof( DebugVertex ) );
	pDevice->SetIndices( pSphereIndexBuffer );
	pDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, CIRCLE_VERTEX_COUNT * SphereCount, 0, SphereCount * CIRCLE_VERTEX_COUNT * 3 );
#endif // _DEBUG || DEBUG
}


/*
* Bufferへの座標登録関数
*/
void DebugCollisionModule::BatchDraw( const ShapeSphere *Sphere )
{
#if defined(_DEBUG) || defined(DEBUG)
	/*
	// 既に描画最大数を超えてバッチ登録していたらreturn とりあえず
	if( CIRCLE_DRAW_MAX < SphereCount  )
	{
		return;
	}
	int n = SphereCount * CIRCLE_VERTEX_COUNT;
	D3DXVECTOR3 Pos = Sphere->GetEffectivePos();

	const float s = D3DX_PI * 2 / CIRCLE_VERTEX_COUNT;

	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pSphereVertex[ n + i ].position.x = (float) cos( i * s ) * Sphere->Radius + Pos.x;
		pSphereVertex[ n + i ].position.y = (float) sin( i * s ) * Sphere->Radius + Pos.y;
		pSphereVertex[ n + i ].position.z = Pos.z;
		pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}

	n += CIRCLE_VERTEX_COUNT;
	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pSphereVertex[ n + i ].position.x = Pos.x;
		pSphereVertex[ n + i ].position.y = (float) cos( i * s ) * Sphere->Radius + Pos.y;
		pSphereVertex[ n + i ].position.z = (float) sin( i * s ) * Sphere->Radius + Pos.z;
		pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}
	n += CIRCLE_VERTEX_COUNT;
	for( int i = 0; i < CIRCLE_VERTEX_COUNT; i++ )
	{
		pSphereVertex[ n + i ].position.x = (float) sin( i * s ) * Sphere->Radius + Pos.x;
		pSphereVertex[ n + i ].position.y = Pos.y;
		pSphereVertex[ n + i ].position.z = (float) cos( i * s ) * Sphere->Radius + Pos.z;
		pSphereVertex[ n + i ].color = D3DCOLOR_RGBA( 0, 255, 0, 255 );

		pSphereVertexIndex[ n * 2 + i * 2 ] = (WORD) ( n + i );
		pSphereVertexIndex[ n * 2 + i * 2 + 1 ] = (WORD) ( n + ( i + 1 ) % CIRCLE_VERTEX_COUNT );
	}

	SphereCount++;
	*/
#endif // _DEBUG || DEBUG
}

//-------------------------------------
//	Cuboid
//-------------------------------------

void DebugCollisionModule::Cuboid_BatchBegin( void )
{
#if defined(_DEBUG) || defined(DEBUG)

	CuboidCount = 0;

	pCuboidVertexBuffer->Lock( 0, 0, (void**) &pCuboidVertex, 0 );
	pCuboidIndexBuffer->Lock( 0, 0, (void**) &pCuboidVertexIndex, 0 );

#endif // _DEBUG || DEBUG
}
void DebugCollisionModule::Cuboid_BatchRun( void )

{
#if defined(_DEBUG) || defined(DEBUG)

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxTransform;
	D3DXMatrixIdentity( &mtxTransform );
	pDevice->SetTransform( D3DTS_WORLD, &mtxTransform );

	pCuboidVertexBuffer->Unlock();
	pCuboidIndexBuffer->Unlock();

	pDevice->SetTexture( 0, NULL );
	pDevice->SetFVF( FVF_DEBUG_VERTEX );
	pDevice->SetStreamSource( 0, pCuboidVertexBuffer, 0, sizeof( DebugVertex ) );
	pDevice->SetIndices( pCuboidIndexBuffer );
	pDevice->DrawIndexedPrimitive( D3DPT_LINELIST, 0, 0, CUBOID_VERTEX_COUNT * CuboidCount, 0, CuboidCount * CUBOID_EDGE_COUNT );


#endif // _DEBUG || DEBUG
}
/*
* Bufferへの座標登録関数
*/
void DebugCollisionModule::BatchDraw( const ShapeOBB* pCuboid )
{
#if defined(_DEBUG) || defined(DEBUG)
	/*
	// 既に描画最大数を超えてバッチ登録していたらreturn とりあえず
	if( CUBOID_DRAW_MAX < CuboidCount )
	{
		return;
	}
	D3DXVECTOR3 AbsLocalX = pCuboid->NormalDirect[ 1 ] * pCuboid->Length[ 1 ];
	D3DXVECTOR3 AbsLocalY = pCuboid->NormalDirect[ 2 ] * pCuboid->Length[ 2 ];
	D3DXVECTOR3 AbsLocalZ = pCuboid->NormalDirect[ 0 ] * pCuboid->Length[ 0 ];

	DebugVertex CuboidVertex[] =
	{
		{ -AbsLocalX + AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ AbsLocalX + AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ -AbsLocalX - AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ AbsLocalX - AbsLocalY - AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },

		{ AbsLocalX + AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ -AbsLocalX + AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ AbsLocalX - AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color },
		{ -AbsLocalX - AbsLocalY + AbsLocalZ + pCuboid->GetEffectivePos(), pCuboid->Color }
	};

	int Margin = CUBOID_VERTEX_COUNT * CuboidCount;

	pCuboidVertex[ Margin + 0 ] = CuboidVertex[ 0 ];
	pCuboidVertex[ Margin + 1 ] = CuboidVertex[ 1 ];
	pCuboidVertex[ Margin + 2 ] = CuboidVertex[ 2 ];
	pCuboidVertex[ Margin + 3 ] = CuboidVertex[ 3 ];
	pCuboidVertex[ Margin + 4 ] = CuboidVertex[ 4 ];
	pCuboidVertex[ Margin + 5 ] = CuboidVertex[ 5 ];
	pCuboidVertex[ Margin + 6 ] = CuboidVertex[ 6 ];
	pCuboidVertex[ Margin + 7 ] = CuboidVertex[ 7 ];

	int IndexMargin = CUBOID_EDGE_COUNT * 2 * CuboidCount;
	// x軸 平行の辺
	pCuboidVertexIndex[ IndexMargin + 0 ] = (WORD) ( Margin + 1 );
	pCuboidVertexIndex[ IndexMargin + 1 ] = (WORD) ( Margin + 0 );

	pCuboidVertexIndex[ IndexMargin + 2 ] = (WORD) ( Margin + 4 );
	pCuboidVertexIndex[ IndexMargin + 3 ] = (WORD) ( Margin + 5 );

	pCuboidVertexIndex[ IndexMargin + 4 ] = (WORD) ( Margin + 6 );
	pCuboidVertexIndex[ IndexMargin + 5 ] = (WORD) ( Margin + 7 );

	pCuboidVertexIndex[ IndexMargin + 6 ] = (WORD) ( Margin + 3 );
	pCuboidVertexIndex[ IndexMargin + 7 ] = (WORD) ( Margin + 2 );

	// y軸 平行
	pCuboidVertexIndex[ IndexMargin + 8 ] = (WORD) ( Margin + 0 );
	pCuboidVertexIndex[ IndexMargin + 9 ] = (WORD) ( Margin + 2 );

	pCuboidVertexIndex[ IndexMargin + 10 ] = (WORD) ( Margin + 1 );
	pCuboidVertexIndex[ IndexMargin + 11 ] = (WORD) ( Margin + 3 );

	pCuboidVertexIndex[ IndexMargin + 12 ] = (WORD) ( Margin + 4 );
	pCuboidVertexIndex[ IndexMargin + 13 ] = (WORD) ( Margin + 6 );

	pCuboidVertexIndex[ IndexMargin + 14 ] = (WORD) ( Margin + 5 );
	pCuboidVertexIndex[ IndexMargin + 15 ] = (WORD) ( Margin + 7 );

	// z軸平行
	pCuboidVertexIndex[ IndexMargin + 16 ] = (WORD) ( Margin + 5 );
	pCuboidVertexIndex[ IndexMargin + 17 ] = (WORD) ( Margin + 0 );

	pCuboidVertexIndex[ IndexMargin + 18 ] = (WORD) ( Margin + 4 );
	pCuboidVertexIndex[ IndexMargin + 19 ] = (WORD) ( Margin + 1 );

	pCuboidVertexIndex[ IndexMargin + 20 ] = (WORD) ( Margin + 6 );
	pCuboidVertexIndex[ IndexMargin + 21 ] = (WORD) ( Margin + 3 );

	pCuboidVertexIndex[ IndexMargin + 22 ] = (WORD) ( Margin + 7 );
	pCuboidVertexIndex[ IndexMargin + 23 ] = (WORD) ( Margin + 2 );
	CuboidCount++;
	*/
#endif // _DEBUG || DEBUG 
}