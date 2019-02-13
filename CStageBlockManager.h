//
//	CStageBlockManager.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CSTAGE_BLOCK_LIST_H
#define CSTAGE_BLOCK_LIST_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include"CStageBlock.h"
#include"CCoreObject.h"
#include<vector>

//Class

//================================================
//	マクロ定義	define
//================================================


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


//-------------------------------------
//	クラス名
//-------------------------------------
class StageBlockManager
{
private:
	static StageBlockManager* pInstance;
public:
	static StageBlockManager* GetInstance();
	void Finalize();
private:
	std::vector<StageBlock*> StageBlockAllay;
	NTexture::Name DefaultTexture;

public:
	StageBlockManager(NTexture::Name DefaultTexture);
	~StageBlockManager();
	void CreateBlock( CTransform* pTransform, DISCHARGING_TYPE type, D3DXVECTOR3 CorePosition, CoreObject::CORE_DISCHARGE_JUDGE_TYPE JudgeType, CoreObject::CORE_TYPE CoreType ); 
	void UpdateAll();
	void RenderAll();
};

#endif