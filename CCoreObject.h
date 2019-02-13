//
//	CCoreObject.h
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#pragma once
#ifndef COREOBJECT_H
#define COREOBJECT_H

#include<d3dx9.h>
#include<vector>
#include"common.h"

using namespace std;

// Hew
#include"CGameObject.h"
#include"CStageBlock.h"
#include"Collider.h"

//===============================================
//	列挙
//===============================================

//===============================================
//	CoreObject クラス
//===============================================
class CoreObject:public NRender3D::CGameObject
{
public: 
	//判定タイプ
	enum CORE_DISCHARGE_JUDGE_TYPE
	{
		CORE_JUDGE_TYPE_0 = 0,
		CORE_JUDGE_TYPE_1,
		// enum max
		CORE_JUDGE__MAX
	};

	//ネジの向き
	enum CORE_DIRECTION
	{
		CORE_DIRECTION_FORWARD,
		CORE_DIRECTION_BEHIND,
		CORE_DIRECTION_UP,
		CORE_DIRECTION_DOWN,
		CORE_DIRECTION_RIGHT,
		CORE_DIRECTION_LEFT,
		// enum max
		CORE_DIRECTION_MAX
	};

	// ネジのタイプ
	enum CORE_TYPE
	{
		CORE_TYPE_NORMAL,
		CORE_TYPE_TIME_GAIN,
		CORE_TYPE_DOUBLE_POINT,

		CORE_TYPE_MAX
	};
private:	
	CORE_DISCHARGE_JUDGE_TYPE JudgeType;		//飛び方判定タイプ
	
public:
	int BlockWidth;			// ブロック保持数（横）
	int BlockHeight;		// ブロック保持数（縦）
	int BlockDepth;			// ブロック保持数（奥行き）
	int NumBlocks;			// ブロック総保持数

public:
	bool bHit;							// 当たった
	D3DXVECTOR3 face;					// ネジ前方向
	D3DXVECTOR3 right;					// ネジ右方向
	D3DXVECTOR3 up;						// ネジ上方向
	ShapeSphere ColShape;				// ネジ自身
	CORE_DIRECTION direction;
	CORE_TYPE CoreType;					// ネジのタイプ
	void SetBlocks(int x, int y, int z);	// ネジにブロックを持たせる

public:
	CoreObject(CTransform* pTransform, AMesh* pMesh, CORE_DISCHARGE_JUDGE_TYPE Type, CORE_DIRECTION face);
	~CoreObject();
private:
	void SetFace(CORE_DIRECTION face);	// ネジの向き設定

public:
	void Hit();			// 当たった

	void Set_JudgeType(CORE_DISCHARGE_JUDGE_TYPE Type);	// 飛び方セット
	void Update();				// 更新
	void Render();				// 描画
	void RenderBox();			// 張りぼての描画
	D3DXVECTOR3 GetFace();		// ネジの向きの取得

};


//===============================================
//	CoreObjectManager クラス
//===============================================

class CoreObjectManager
{
private:
	CoreObjectManager();
	~CoreObjectManager();
	static CoreObjectManager* pInstance;
public:
	static CoreObjectManager* GetInstance();
private:
	vector<CoreObject*> ppCoreCollection;
	CXModelMesh* pCoreModel;
public:
	void CreateCore( D3DXVECTOR3 pos, unsigned int x, unsigned int y, unsigned int z );
	unsigned int  GetCurrentCoreExist( void ) const;
	void UpdateCoreAll( void );
	void RenderCoreAll( void );
	void Finalize( void );
};
#endif // !CCOREOBJECT_H
