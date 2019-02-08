//
//	CStageBlock.cpp
//		Author:YU NISHIMAKI		DATE:2018/11/13
//===============================================
//	変更者 Changed By
//		Name:YU NISHIMAKI		DATE:2019/02/05
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include<d3dx9.h>
#include"System.h"

//class
#include"CStageBlock.h"
#include"CCoreObject.h"


//===============================================
//	マクロ定義		define
//===============================================
const D3DXVECTOR3 GRAVITY(0.0f, -0.02f, 0.0f);	//重力


//===============================================
//	構造体宣言	struct
//===============================================

//===============================================
//	グローバル変数	global
//===============================================

// 頂点リスト
const StageBlockVertex g_StageVertex[] = {
	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(0.0f / 6, 0.0f) }, // 上面
	{ D3DXVECTOR3(0.5f , 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(1.0f / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(0.0f / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2(1.0f / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 1.0f) / 6, 0.0f) }, // 手前面
	{ D3DXVECTOR3(0.5f , 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 1.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 1.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 1.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 2.0f) / 6, 0.0f) }, // 右面
	{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 2.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 2.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 2.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 3.0f) / 6, 0.0f) }, // 奥面
	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 3.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 3.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 3.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 4.0f) / 6, 0.0f) }, // 左面
	{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 4.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 4.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 4.0f) / 6, 1.0f) },

	{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 5.0f) / 6, 0.0f) }, // 下面
	{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 5.0f) / 6, 0.0f) },
	{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((0.0f + 5.0f) / 6, 1.0f) },
	{ D3DXVECTOR3(0.5f , -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DCOLOR_RGBA(255, 255, 255, 255),	D3DXVECTOR2((1.0f + 5.0f) / 6, 1.0f) },
};


//===============================================
//	StageBlockクラス		class
//===============================================

//-------------------------------------
//	静的メンバ変数の初期化	static
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 StageBlock::pVertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 StageBlock::pIndexBuffer = NULL;

StageBlockVertex *StageBlock::pVertex = NULL;
WORD *StageBlock::pVertexIndex = NULL;

//-------------------------------------
//	初期化（頂点バッファ、インデックスバッファの確保）
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
//	終了処理（頂点バッファ、インデックスバッファの解放）
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
//	コンストラクタ
//-------------------------------------
StageBlock::StageBlock(CTransform* pTransform, NTexture::Name TextureIndex)
	:
	CGameObject(pTransform, NULL)
{
	this->Discharging_Type = RADIALLY;
	this->Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->DelayFrameForDrop = -1;

	pTexture = NTexture::Get_Texture(TextureIndex);
	pPrev = NULL;
	pNext = NULL;
}

StageBlock::StageBlock(CTransform* pTransform, NTexture::Name TextureIndex, DISCHARGING_TYPE type)
	: 
	CGameObject(pTransform, NULL)
{
	this->Discharging_Type = type;
	this->Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	this->DelayFrameForDrop = -1;

	pTexture = NTexture::Get_Texture(TextureIndex);
	pPrev = NULL;
	pNext = NULL;
}

//-------------------------------------
//	描画
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

	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->SetTexture(0, pTexture);
	pDevice->SetFVF(FVF_STAGE_BLOCK_VERTEX);
	pDevice->SetStreamSource(0, pVertexBuffer, 0, sizeof(StageBlockVertex));
	pDevice->SetIndices(pIndexBuffer);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, NUM_STAGE_VERTEX, 0, NUM_STAGE_VERTEX * 2 / 4);
}


//-------------------------------------
//	更新処理
//-------------------------------------
void StageBlock::Update()
{
	//--------------------------
	//	バラバラ
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
//	速度ベクトルセット
//-------------------------------------
void StageBlock::SetSpeed(D3DXVECTOR3 CorePosition, int CoreType)
{
	// 座標とりたい
	float SquaredDist = D3DXVec3LengthSq(&(transform->Get_Position() - CorePosition));

	switch (CoreType)
	{
	case CoreObject::CORE_JUDGE_TYPE_0:	//距離
		this->DelayFrameForDrop = (int)SquaredDist * WEIGHT + MARGIN;
		break;
	case CoreObject::CORE_JUDGE_TYPE_1:	// 子Armor全て一度に
		this->DelayFrameForDrop = WEIGHT + MARGIN;
		break;
	default:
		this->DelayFrameForDrop = WEIGHT + MARGIN; // 仮置きでType1をデフォルトに
		break;
	}

	// 速度を指定
	D3DXVECTOR3* pInitSpeed;

	switch (this->Discharging_Type)
	{

	case FALL:	//ずれて落ちる
		this->Speed = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		break;
	case RADIALLY: //放射状に広がる
		this->Speed = D3DXVECTOR3(this->transform->Get_Position() - CorePosition);
		D3DXVec3Normalize(&this->Speed, &this->Speed);
		this->Speed *=  STAGE_BLOCK_SPEED;
	}
}

//-------------------------------------
//	タイプをセット
//-------------------------------------
void StageBlock::Set_DischargingType(DISCHARGING_TYPE Type)
{
	this->Discharging_Type = Type;
}

