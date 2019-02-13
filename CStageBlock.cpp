//
//	CStageBlock.cpp
//		Author:YU NISHIMAKI		DATE:2018/11/13
//===============================================
//	�ύX�� Changed By
//		Name:YU NISHIMAKI		DATE:2019/02/05
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include<d3dx9.h>
#include"System.h"

//class
#include"CStageBlock.h"
#include"CCoreObject.h"


//===============================================
//	�}�N����`		define
//===============================================
const D3DXVECTOR3 GRAVITY(0.0f, -0.02f, 0.0f);	//�d��


//===============================================
//	�\���̐錾	struct
//===============================================

//===============================================
//	�O���[�o���ϐ�	global
//===============================================

// ���_���X�g
const StageBlockVertex g_StageVertex[] = {
	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(0.0f / 6, 0.0f) }, // ���
	{ D3DXVECTOR3(0.5f , 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(1.0f / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(0.0f / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(1.0f / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 1.0f) / 6, 0.0f) }, // ��O��
	{ D3DXVECTOR3(0.5f , 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 1.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 1.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 1.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 2.0f) / 6, 0.0f) }, // �E��
	{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 2.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 2.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 2.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 3.0f) / 6, 0.0f) }, // ����
	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 3.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 3.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 3.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 4.0f) / 6, 0.0f) }, // ����
	{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 4.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 4.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 4.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 5.0f) / 6, 0.0f) }, // ����
	{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 5.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 5.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 5.0f) / 6, 1.0f) },
};


//===============================================
//	StageBlock�N���X		class
//===============================================

//-------------------------------------
//	�ÓI�����o�ϐ��̏�����	static
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 StageBlock::pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 StageBlock::pIndexBuffer = NULL;

StageBlockVertex *StageBlock::pVertex = NULL;
WORD *StageBlock::pVertexIndex = NULL;

//-------------------------------------
//	�������i���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̊m�ہj
//-------------------------------------
void StageBlock::Initialize()
{
	if (pVertexBuffer || pIndexBuffer)
		return;

	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();
	pDevice->CreateVertexBuffer(sizeof(StageBlockVertex) * NUM_STAGE_VERTEX, D3DUSAGE_WRITEONLY, FVF_STAGE_BLOCK_VERTEX, D3DPOOL_MANAGED, &pVertexBuffer, NULL);
	pDevice->CreateIndexBuffer(sizeof(WORD) * NUM_STAGE_VERTEX * 3 / 2, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &pIndexBuffer, NULL);
	pVertexBuffer->Lock(0, 0, (void **)&pVertex, 0);
	pIndexBuffer->Lock(0, 0, (void **)&pVertexIndex, 0);

	for (int i = 0; i < NUM_STAGE_VERTEX; i++)
	{
		pVertex[i] = g_StageVertex[i];
	}

	int Num_Face = NUM_STAGE_VERTEX / 4;
	for (int i = 0; i < Num_Face; i++)
	{
		pVertexIndex[i * 6 + 0] = (WORD)i * 4 + 0;
		pVertexIndex[i * 6 + 1] = (WORD)i * 4 + 1;
		pVertexIndex[i * 6 + 2] = (WORD)i * 4 + 2;
		pVertexIndex[i * 6 + 3] = (WORD)i * 4 + 1;
		pVertexIndex[i * 6 + 4] = (WORD)i * 4 + 3;
		pVertexIndex[i * 6 + 5] = (WORD)i * 4 + 2;
	}
	pVertexBuffer->Unlock();
	pIndexBuffer->Unlock();
}

//-------------------------------------
//	�I�������i���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�̉���j
//-------------------------------------
void StageBlock::Finalize()
{
	if (pVertexBuffer)
	{
		pVertexBuffer->Release();
		pVertexBuffer = NULL;
	}
	if (pIndexBuffer)
	{
		pIndexBuffer->Release();
		pIndexBuffer = NULL;
	}
}


//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
StageBlock::StageBlock(CTransform* pTransform, NTexture::Name TextureIndex)
	:
	CGameObject(pTransform, NULL)
{
	this->Discharging_Type = RADIALLY;
	this->Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->DelayFrameForDrop = -1;

	pTexture = NTexture::Get_Texture(TextureIndex);
}

StageBlock::StageBlock(CTransform* pTransform, NTexture::Name TextureIndex, DISCHARGING_TYPE type)
	: 
	CGameObject(pTransform, NULL)
{
	this->Discharging_Type = type;
	this->Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->DelayFrameForDrop = -1;

	pTexture = NTexture::Get_Texture(TextureIndex);
}

//-------------------------------------
//	�`��
//-------------------------------------
void StageBlock::Render()
{
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxScaling;

	D3DXMatrixTranslation(&mtxTranslation, transform->Get_Position().x, transform->Get_Position().y, transform->Get_Position().z);
	D3DXMatrixScaling(&mtxScaling, transform->Get_Scale().x, transform->Get_Scale().y, transform->Get_Scale().z);

	mtxWorld = mtxScaling * mtxTranslation;
	
	// pDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->SetTexture(0, pTexture);
	pDevice->SetFVF(FVF_STAGE_BLOCK_VERTEX);
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(StageBlockVertex));
	pDevice->SetIndices(pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_STAGE_VERTEX, 0, NUM_STAGE_VERTEX * 2 / 4);
}


//-------------------------------------
//	�X�V����
//-------------------------------------
void StageBlock::Update()
{
	//--------------------------
	//	�o���o��
	//--------------------------
	if (DelayFrameForDrop <= 0)
	{
		this->transform->Set_Position(this->transform->Get_Position() + this->Speed);
		this->Speed += GRAVITY;
	}

	// 
	if (0 < DelayFrameForDrop)
	{
		DelayFrameForDrop--;
	}
	
}


//-------------------------------------
//	���x�x�N�g���Z�b�g
//-------------------------------------
void StageBlock::SetSpeed(D3DXVECTOR3 CorePosition, int CoreType)
{
	// ���W�Ƃ肽��
	float SquaredDist = D3DXVec3LengthSq(&(transform->Get_Position() - CorePosition));

	switch (CoreType)
	{
	case CoreObject::CORE_JUDGE_TYPE_0:	//����
		this->DelayFrameForDrop = (int)SquaredDist * WEIGHT + MARGIN;
		break;
	case CoreObject::CORE_JUDGE_TYPE_1:	// �qArmor�S�Ĉ�x��
		this->DelayFrameForDrop = WEIGHT + MARGIN;
		break;
	default:
		this->DelayFrameForDrop = WEIGHT + MARGIN; // ���u����Type1���f�t�H���g��
		break;
	}

	// ���x���w��
	D3DXVECTOR3* pInitSpeed;

	switch (this->Discharging_Type)
	{

	case FALL:	//����ė�����
		this->Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	case RADIALLY: //���ˏ�ɍL����
		this->Speed = D3DXVECTOR3(this->transform->Get_Position() - CorePosition);
		D3DXVec3Normalize(&this->Speed, &this->Speed);
		this->Speed *=  STAGE_BLOCK_SPEED;
	}
}

//-------------------------------------
//	�^�C�v���Z�b�g
//-------------------------------------
void StageBlock::Set_DischargingType(DISCHARGING_TYPE Type)
{
	this->Discharging_Type = Type;
}

