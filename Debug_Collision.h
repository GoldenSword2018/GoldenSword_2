
//
//	Debug_Circle.h
//		USER:YU NISHIMAKI		DATE:2018/10/18
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//		Name: Yuto Hashimoto	DATE:2018/10/18
// シングルトンっぽい感じに記述を変更.　直方体に関しては未実装.
//
//-----------------------------------------------
#pragma once
#ifndef DEBUG_PRIMITIVE_H
#define DEBUG_PRIMITIVE_H

#include<d3dx9.h>
#include"CCollisionShape.h"

typedef struct DebugVertex_tag
{
	D3DXVECTOR3 position;
	D3DCOLOR color;
}DebugVertex;

class DebugCollisionModule
{

private:
	DebugCollisionModule();
	DebugCollisionModule( const DebugCollisionModule& DCM );
	~DebugCollisionModule();
private: // instance 
	static DebugCollisionModule* pInstance;
public: // 関数
	static DebugCollisionModule* GetInstance( void );
	void BatchBegin( void ); // 描画対象の登録処理開始
	void BatchRun( void ); // 登録の終了,及び描画
	void Finalize( void );
	/*
	static void BatchRun( void ); // ここの実装わかりません
	*/
// Sphere用
private:
	LPDIRECT3DVERTEXBUFFER9 pSphereVertexBuffer;		// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9 pSphereIndexBuffer;		// インデックスバッファ
public: // バッチ処理 将来的にprivateメンバにする
	void Sphere_BatchBegin( void );
	void Sphere_BatchRun( void );
private:
	int SphereCount;
	DebugVertex* pSphereVertex;
	WORD* pSphereVertexIndex;
public: // 座標登録
	void BatchDraw( const ShapeSphere* Sphere );

// Cuboid用 _
private:
	LPDIRECT3DVERTEXBUFFER9 pCuboidVertexBuffer;		// 頂点バッファ
	LPDIRECT3DINDEXBUFFER9 pCuboidIndexBuffer;		// インデックスバッファ
public: // バッチ処理
	void Cuboid_BatchBegin( void );
	void Cuboid_BatchRun( void );
private:
	int CuboidCount;
	DebugVertex* pCuboidVertex;
	WORD*  pCuboidVertexIndex;
public: // 座標登録
	void BatchDraw( const ShapeOBB* pCuboid );

};

#endif // !DEBUG_PRIMITIVE_H