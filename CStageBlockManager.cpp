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
		StageBlock::Initialize();
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
void StageBlockManager::CreateBlock( CTransform* pTransform, DISCHARGING_TYPE type, D3DXVECTOR3 CorePosition, CoreObject::CORE_DISCHARGE_JUDGE_TYPE JudgeType, CoreObject::CORE_TYPE CoreType )
{
	NTexture::Name texture;
	switch( CoreType )
	{
		case CoreObject::CORE_TYPE_NORMAL:
			texture = this->DefaultTexture;
			break;
		case CoreObject::CORE_TYPE_TIME_GAIN:
			texture = NTexture::BlockTex2;
			break;
		case CoreObject::CORE_TYPE_DOUBLE_POINT:
			texture = NTexture::BlockTex3;
			break;
		default:
			texture = this->DefaultTexture;
			break;
	}
	StageBlock* pStageBlock = new StageBlock( pTransform, texture );
	pStageBlock->SetSpeed( CorePosition, JudgeType );
	StageBlockAllay.push_back( pStageBlock );
}

//-------------------------------------
//	�o�^���ꂽ�u���b�N�����ׂčX�V
//-------------------------------------
void StageBlockManager::UpdateAll()
{
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