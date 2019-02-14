//
//	CStageBlockManager.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CSTAGE_BLOCK_LIST_H
#define CSTAGE_BLOCK_LIST_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"
#include<d3dx9.h>
#include"CStageBlock.h"
#include"CCoreObject.h"
#include<vector>

//Class

//================================================
//	�}�N����`	define
//================================================


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


//-------------------------------------
//	�N���X��
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
	void CreateBlock(CTransform* pTransform, DISCHARGING_TYPE type, D3DXVECTOR3 CorePosition, CoreObject::CORE_DISCHARGE_JUDGE_TYPE Type);
	void UpdateAll();
	void RenderAll();
};

#endif