//
//	CStageBlockManager.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include"CStageBlockManager.h"

//Class

//===============================================
//	マクロ定義		define
//===============================================
#define STAGE_BLOCK_TEXTURE			(NTexture::CubeTexture)

//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	関数			function
//===============================================

//-------------------------------------
//	静的メンバ初期化
//-------------------------------------
StageBlockManager* StageBlockManager::pInstance = NULL;

//-------------------------------------
//	インスタンスの取得（なければ生成）
//-------------------------------------
StageBlockManager* StageBlockManager::GetInstance()
{
	if (!pInstance)
	{
		pInstance = new StageBlockManager(STAGE_BLOCK_TEXTURE);
	}

	return pInstance;
}

//-------------------------------------
//	インスタンスの破棄
//-------------------------------------
void StageBlockManager::Finalize()
{
	if (pInstance)
	{
		delete pInstance;
		pInstance = NULL;
	}
}


//-------------------------------------
//	コンストラクタ
//-------------------------------------
StageBlockManager::StageBlockManager(NTexture::Name DefaultTexture)
{
	this->DefaultTexture = DefaultTexture;
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
StageBlockManager::~StageBlockManager()
{
	for (int i = 0; i < StageBlockAllay.size(); i++)
	{
		delete StageBlockAllay.at(i);
	}
	StageBlockAllay.clear();
}


//-------------------------------------
//	ブロック追加
//-------------------------------------
void StageBlockManager::CreateBlock(CTransform* pTransform, DISCHARGING_TYPE type, D3DXVECTOR3 CorePosition, CoreObject::CORE_DISCHARGE_JUDGE_TYPE Type)
{
	StageBlock* pStageBlock = new StageBlock(pTransform, this->DefaultTexture);
	pStageBlock->SetSpeed(CorePosition, Type);
	StageBlockAllay.push_back(pStageBlock);
}

//-------------------------------------
//	登録されたブロックをすべて更新
//-------------------------------------
void StageBlockManager::UpdateAll()
{
	for (int i = 0; i < StageBlockAllay.size(); i++)
	{
		StageBlockAllay.at(i)->Update();
	}
}

//-------------------------------------
//	登録されたブロックをすべて描画
//-------------------------------------
void StageBlockManager::RenderAll()
{
	for (int i = 0; i < StageBlockAllay.size(); i++)
	{
		StageBlockAllay.at(i)->Render();
	}
}
