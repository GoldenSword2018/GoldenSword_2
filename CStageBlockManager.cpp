//
//	CStageBlockManager.cpp
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include"CStageBlockManager.h"

//Class

//===============================================
//	�}�N����`		define
//===============================================
#define STAGE_BLOCK_TEXTURE			(NTexture::CubeTexture)

//===============================================
//	�O���[�o���ϐ�	global
//===============================================


//===============================================
//	�֐�			function
//===============================================

//-------------------------------------
//	�ÓI�����o������
//-------------------------------------
StageBlockManager* StageBlockManager::pInstance = NULL;

//-------------------------------------
//	�C���X�^���X�̎擾�i�Ȃ���ΐ����j
//-------------------------------------
StageBlockManager* StageBlockManager::GetInstance()
{
	if (!pInstance)
	{
		pInstance = new StageBlockManager( STAGE_BLOCK_TEXTURE );
	}

	return pInstance;
}

//-------------------------------------
//	�C���X�^���X�̔j��
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
//	�R���X�g���N�^
//-------------------------------------
StageBlockManager::StageBlockManager(NTexture::Name DefaultTexture)
{
	this->DefaultTexture = DefaultTexture;
}

//-------------------------------------
//	�f�X�g���N�^
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
//	�u���b�N�ǉ�
//-------------------------------------
void StageBlockManager::CreateBlock(CTransform* pTransform, DISCHARGING_TYPE type, D3DXVECTOR3 CorePosition, CoreObject::CORE_DISCHARGE_JUDGE_TYPE Type)
{
	StageBlock* pStageBlock = new StageBlock( pTransform, this->DefaultTexture);
	pStageBlock->SetSpeed(CorePosition, Type);
	StageBlockAllay.push_back(pStageBlock);
}

//-------------------------------------
//	�o�^���ꂽ�u���b�N�����ׂčX�V
//-------------------------------------
void StageBlockManager::UpdateAll()
{
	if( 2 < StageBlockAllay.size() )
	{
		int a = 0;
	}
	for (int i = 0; i < StageBlockAllay.size(); i++)
	{
		StageBlockAllay.at(i)->Update();
	}
}

//-------------------------------------
//	�o�^���ꂽ�u���b�N�����ׂĕ`��
//-------------------------------------
void StageBlockManager::RenderAll()
{
	for (int i = 0; i < StageBlockAllay.size(); i++)
	{
		StageBlockAllay.at(i)->Render();
	}
}