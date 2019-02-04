//
//	CBurst.cpp
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
#include"CBurst.h"
#include<vector>

//class
#include"Lighting.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================
static NTexture::NameTexture g_Texture(NTexture::Billboard_Burst, { 0.0f,0.0f }, { 768.0f / 6.0f,384.0f / 3.0f });

//===============================================
//	CBurst
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CBurst::CBurst(D3DXVECTOR3 Position, D3DXVECTOR3 Scale,bool bDepthTest)
:
	ABillboard(Position,Scale)
{
	this->animation = new NTexture::CAnimation(17, 6, 1);
	this->texture = &g_Texture;
	this->Position = Position;
	this->Scale = Scale;
	this->bDepthTest = bDepthTest;
}

CBurst::CBurst(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, NTexture::Texture* texture, NTexture::CAnimation* animation, bool bDepthTest)
:
	ABillboard(Position,Scale)

{
	this->texture = texture;
	this->animation = animation;
	this->bDepthTest = bDepthTest;
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CBurst::~CBurst()
{
	delete this->animation;
}

//-----------------------------------------------
//	メンバ
//-----------------------------------------------

//-------------------------------------
//	更新
//-------------------------------------
void CBurst::Update()
{
	if(this->animation->AnimaPatern == this->animation->MaxPatern -1)
	{
		this->~CBurst();
	}
}

//-------------------------------------
//	描画
//-------------------------------------
void CBurst::Render()
{
	if (this->bDepthTest)
	{
		NLighting::Set_DepthTest(FALSE);
		AnimaBillBoard_Create(this->Position, this->Scale, this->texture, this->animation);
		NLighting::Set_DepthTest(TRUE);
	}
	else
	{
		NLighting::Set_AlphaTest(TRUE, 200);
		AnimaBillBoard_Create(this->Position, this->Scale, this->texture, this->animation);
		NLighting::Set_AlphaTest(FALSE, 0);
	}
}