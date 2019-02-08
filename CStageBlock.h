//
//	CStageBlock.h
//		Author:YU NISHIMAKI		DATE:2018/11/13
//===============================================
//	変更者 Changed By
//		Name:YU NISHIMAKI		DATE:2019/02/05
//
//-----------------------------------------------

#pragma once
#ifndef CSTAGE_BLOCK_H
#define CSTAGE_BLOCK_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include<vector>
#include"Texture.h"

//Class
#include"CGameObject.h"
#include"CCollisionShape.h"
#include"CCoreObject.h"

// 当たり判定
class ShapeOBB;

//================================================
//	マクロ定義	define
//================================================
#define NUM_STAGE_VERTEX		(24)
#define FVF_STAGE_BLOCK_VERTEX	( D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE | D3DFVF_TEX1 )		// 構造体StageBlockVertexのFVFフラグ
#define STAGE_BLOCK_SPEED		(1.0f)
#define MARGIN					(60)
#define WEIGHT					(1)


//================================================
//	列挙型		enum
//================================================
enum DISCHARGING_TYPE
{
	FALL,		// 垂直落下
	RADIALLY,	// 放射状に

	NONE
};

//================================================
//	構造体		struct/typedef
//================================================
typedef struct StageBlockVertex_tag
{
	D3DXVECTOR3 Position;			// 頂点座標
	D3DXVECTOR3 Normal;				// 法線ベクトル
	D3DCOLOR Color;					// 頂点色
	D3DXVECTOR2 TexCoord;			// テクスチャ座標
}StageBlockVertex;


//================================================
//	グローバル変数　global
//================================================


//================================================
//	クラス		class
//================================================


//-------------------------------------
//	StageBlockクラス
//-------------------------------------
class StageBlock:public NRender3D::CGameObject
{
	//-------------------------------------
	//	描画関係
	//-------------------------------------
private:
	LPDIRECT3DTEXTURE9 pTexture;	// ブロックに貼るテクスチャポインタ

// バッファ用変数
private:
	static LPDIRECT3DVERTEXBUFFER9 pVertexBuffer;			// 頂点バッファ
	static LPDIRECT3DINDEXBUFFER9 pIndexBuffer;				// インデックスバッファ

	static StageBlockVertex *pVertex;
	static WORD *pVertexIndex;

public:
	static void Initialize();		// 初期化(頂点バッファ、インデックスバッファの確保)
	static void Finalize();			// 終了処理(頂点バッファ、インデックスバッファの解放)

	//-------------------------------------
	//	バラバラ関係
	//-------------------------------------
private: // 一般
	D3DXVECTOR3 Speed;	// 吹き飛び速度

public: // バラバラ イベント用
	DISCHARGING_TYPE Discharging_Type;	// 吹き飛び方のタイプ
	int DelayFrameForDrop;				// バラバラになって飛んでいくまでの時間

public: // バラバラ
	void SetSpeed(D3DXVECTOR3 CorePosition, int CoreType);

public: // 一般関数
	void Set_DischargingType(DISCHARGING_TYPE Type);

//===========================================================//

public:
	StageBlock* pPrev;
	StageBlock* pNext;
public:
	// コンストラクタ
	StageBlock(CTransform *pTransform, NTexture::Name TextureIndex);
	StageBlock(CTransform* pTransform, NTexture::Name TextureIndex, DISCHARGING_TYPE type);

	void Update();					// 更新
public:
	void Render();					// 描画

};


#endif