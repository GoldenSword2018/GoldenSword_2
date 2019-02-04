//
//	Billboard.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include<d3dx9.h>
#include"System.h"
#include"CCamera.h"
#include"Texture.h"
#include"Lighting.h"

//Class
#include"CTransform.h"
#include"Billboard.h"
#include"Animation.h"

//===============================================
//	マクロ定義		define
//===============================================
#define BILLBORAD_MAX (20)	//最大数
#define FVF_BILLBOARD (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

struct BillboardVertex
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;	
	D3DXVECTOR2 TexCoord;
};


//===============================================
//	グローバル変数	global
//===============================================
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;

static BillboardVertex* g_pBillboard_Vertex = NULL;

static D3DMATERIAL9 g_Material = {};

static BillboardVertex Billboard[4] = 
{
	{ { -0.5f,0.5f,0.0f  },{ 0.0f,0.0f,-1.0f },{ 0.0f,0.0f } },
	{ {  0.5f,0.5f,0.0f  },{ 0.0f,0.0f,-1.0f },{ 1.0f,0.0f } },
	{ { -0.5f,-0.5f,0.0f },{ 0.0f,0.0f,-1.0f },{ 0.0f,1.0f } },
	{ {  0.5f,-0.5f,0.0f },{ 0.0f,0.0f,-1.0f },{ 1.0f,1.0f } }
};

std::vector<ABillboard*> ABillboard::pIndex;

//===============================================
//	ABillbord
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
ABillboard::ABillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale)
{
	this->Position = Position;
	this->Scale = Scale;
	pIndex.push_back(this);
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
ABillboard::~ABillboard()
{
	auto itr = pIndex.begin();
	while (itr != pIndex.end())
	{
		if (*itr == this)
		{
			pIndex.erase(itr);
			break;
		}
		itr++;
	}
}

void ABillboard::g_Update()
{
	for(int i = 0; i< pIndex.size(); i++)
	{
		pIndex.at(i)->Update();
	}
	

	/* itrが崩れてしまうので不使用
	auto itr = pIndex.begin();
	while (itr != pIndex.end())
	{
		ABillboard* billboard = *itr;
		billboard->Update();
		itr++;
	}
	*/

}

void ABillboard::g_Render()
{
	
	for(int i = 0; i < pIndex.size(); i++)
	{
		pIndex.at(i)->Render();
	}
	
	/* itrが崩れてしまうので不使用
	auto itr = pIndex.begin();
	while (itr != pIndex.end())
	{
		ABillboard* billboard = *itr;
		billboard->Render();
		itr++;
	}
	*/
}

//===============================================
//	CBillboard
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CBillboard::CBillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale):ABillboard(Position,Scale)
{

}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CBillboard::~CBillboard()
{

}

//-------------------------------------
//	更新処理
//-------------------------------------
void CBillboard::Update()
{

}

//-------------------------------------
//	描画処理
//-------------------------------------
void CBillboard::Render()
{
	
}

//
////===============================================
////	AnimationBillboard
////===============================================
//
////-------------------------------------
////	コンストラクタ
////-------------------------------------
//AnimationBillboard::AnimationBillboard(D3DXVECTOR3 Position,D3DXVECTOR3 Scale):ABillboard(Position,Scale)
//{
//
//}
//
////-------------------------------------
////	デストラクタ
////-------------------------------------
//AnimationBillboard::~AnimationBillboard()
//{
//
//}
//
////-------------------------------------
////	更新処理
////-------------------------------------
//void AnimationBillboard::Update()
//{
//	if(this->animation.AnimaPatern >= this->animation.MaxPatern)
//	{
//		this->~AnimationBillboard();
//	}
//}
//
////-------------------------------------
////	描画処理
////-------------------------------------
//void AnimationBillboard::Render()
//{
//	float width = (float)texture.Width();
//	float height = (float)texture.Height();
//
//	//animation.AnimaPatern = min((Animation_GetFrame()/animation.Waitframe),animation.MaxPatern);
//	animation.AnimaPatern = (NRender2D::Get_Frame() / animation.Waitframe) % animation.MaxPatern;
//
//	D3DXVECTOR2 TexCoord = { (float)texture.TexScale().x * (animation.AnimaPatern % animation.YMaxPatern),(float)texture.TexScale().y * (animation.AnimaPatern/animation.YMaxPatern)};
//
//	float u0 = (float)TexCoord.x / width;
//	float v0 = (float)TexCoord.y / height;
//	float u1 = u0 + (float)texture.TexScale().x / width;
//	float v1 = v0 + (float)texture.TexScale().y / height;
//
//	BillboardVertex Polygon[4];
//	memcpy(&Polygon[0],&Billboard[0],sizeof(BillboardVertex) * 4);
//	Polygon[0].TexCoord = {u0,v0};
//	Polygon[1].TexCoord = {u1,v0};
//	Polygon[2].TexCoord = {u0,v1};
//	Polygon[3].TexCoord = {u1,v1};
//
//	D3DXMATRIX InvView = InvMatrix();
//
//	D3DXMATRIX MtxTransform;
//	D3DXMatrixTranslation(&MtxTransform, Position.x, Position.y, Position.z);
//
//	D3DXMATRIX MtxScaling;
//	D3DXMatrixScaling(&MtxScaling, Scale.x, Scale.y, Scale.z);
//
//	D3DXMATRIX MtxWorld;
//	D3DXMatrixIdentity(&MtxWorld);
//	MtxWorld = InvView * MtxScaling *MtxTransform;
//
//	LPDIRECT3DDEVICE9 Device = System_GetDevice();
//	Device->SetTransform(D3DTS_WORLD, &MtxWorld);
//	Device->SetMaterial(&g_Material);
//
//	Device->SetFVF(FVF_BILLBOARD);
//	Device->SetTexture(0, this->texture.lpTexture());
//	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2,&Polygon,sizeof(BillboardVertex));
//}

//===============================================
//	関数			function
//===============================================

//-------------------------------------
//	初期化処理
//-------------------------------------
void Billboard_Initialize()
{
	g_Material.Diffuse = g_Material.Ambient = { 1.0f,1.0f,1.0f,1.0f };

	System_GetDevice()->CreateVertexBuffer(
		sizeof(BillboardVertex)* 4,
		D3DUSAGE_WRITEONLY,
		FVF_BILLBOARD,
		D3DPOOL_MANAGED,
		&g_pVertexBuffer,
		NULL
	);

	g_pVertexBuffer->Lock(0, 0, (void**)&g_pBillboard_Vertex, 0);

	memcpy(&g_pBillboard_Vertex[0],&Billboard[0],sizeof(BillboardVertex) * 4);

	g_pVertexBuffer->Unlock();
}

//-------------------------------------
//	生成処理
//-------------------------------------
void BillBoard_Create(D3DXVECTOR3 position)
{
	D3DXMATRIX InvView = InvMatrix();

	D3DXMATRIX MtxTransform;
	D3DXMatrixTranslation(&MtxTransform,position.x,position.y,position.z);

	D3DXMATRIX MtxWorld;
	D3DXMatrixIdentity(&MtxWorld);
	MtxWorld *= InvView * MtxTransform;

	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetTransform(D3DTS_WORLD,&MtxWorld);
	Device->SetMaterial(&g_Material);
	Device->SetTexture(0,NTexture::Get_Texture(NTexture::BillBoardTex));

	Device->SetStreamSource(0,g_pVertexBuffer,0,sizeof(BillboardVertex));
	Device->SetFVF(FVF_BILLBOARD);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP,0,2);

}

void BillBoard_Create(CTransform* pTransform)
{
	D3DXMATRIX InvView = InvMatrix();

	D3DXMATRIX MtxTransform;
	D3DXMatrixTranslation(&MtxTransform, pTransform->Position()->x,pTransform->Position()->y, pTransform->Position()->z);

	D3DXMATRIX MtxScaling;
	D3DXMatrixScaling(&MtxScaling,pTransform->Scale()->x,pTransform->Scale()->y,pTransform->Scale()->z);

	D3DXMATRIX MtxWorld;
	D3DXMatrixIdentity(&MtxWorld);
	MtxWorld = InvView * MtxScaling *MtxTransform;

	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetTransform(D3DTS_WORLD, &MtxWorld);
	Device->SetMaterial(&g_Material);
	Device->SetTexture(0, NTexture::Get_Texture(NTexture::BillBoardTex));

	Device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillboardVertex));
	Device->SetFVF(FVF_BILLBOARD);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
}

void BillBoard_Create(D3DXVECTOR3 Position, D3DXVECTOR3 Scale,PDIRECT3DTEXTURE9 pTexture)
{
	D3DXMATRIX InvView = InvMatrix();

	D3DXMATRIX MtxTransform;
	D3DXMatrixTranslation(&MtxTransform, Position.x, Position.y, Position.z);

	D3DXMATRIX MtxScaling;
	D3DXMatrixScaling(&MtxScaling,Scale.x,  Scale.y, Scale.z);

	D3DXMATRIX MtxWorld;
	D3DXMatrixIdentity(&MtxWorld);
	MtxWorld = InvView * MtxScaling *MtxTransform;

	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetRenderState(D3DRS_ZENABLE,FALSE);
	Device->SetTransform(D3DTS_WORLD, &MtxWorld);
	Device->SetMaterial(&g_Material);
	Device->SetTexture(0, pTexture);

	Device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillboardVertex));
	Device->SetFVF(FVF_BILLBOARD);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
	Device->SetRenderState(D3DRS_ZENABLE, TRUE);
}

void AnimaBillBoard_Create(D3DXVECTOR3 Position,D3DXVECTOR3 Scale,NTexture::Texture* pTexture,NTexture::CAnimation* pAnimation)
{
	float width = (float)pTexture->Width();
	float height = (float)pTexture->Height();

	//pAnimation->AnimaPatern	= min((Animation_GetFrame()/pAnimation->Waitframe),pAnimation->MaxPatern);
	pAnimation->AnimaPatern = ((NTexture::Get_Frame() - pAnimation->Createframe) / pAnimation->Waitframe) % pAnimation->MaxPatern;

	D3DXVECTOR2 TexCoord = { (float)pTexture->TexScale().x * (pAnimation->AnimaPatern % pAnimation->YMaxPatern),(float)pTexture->TexScale().y * (pAnimation->AnimaPatern / pAnimation->YMaxPatern) };

	float u0 = (float)TexCoord.x / width;
	float v0 = (float)TexCoord.y / height;
	float u1 = u0 + (float)pTexture->TexScale().x / width;
	float v1 = v0 + (float)pTexture->TexScale().y / height;

	BillboardVertex Polygon[4];
	memcpy(&Polygon[0], &Billboard[0], sizeof(BillboardVertex) * 4);
	Polygon[0].TexCoord = { u0,v0 };
	Polygon[1].TexCoord = { u1,v0 };
	Polygon[2].TexCoord = { u0,v1 };
	Polygon[3].TexCoord = { u1,v1 };

	D3DXMATRIX InvView = InvMatrix();

	D3DXMATRIX MtxTransform;
	D3DXMatrixTranslation(&MtxTransform, Position.x, Position.y, Position.z);

	D3DXMATRIX MtxScaling;
	D3DXMatrixScaling(&MtxScaling, Scale.x, Scale.y, Scale.z);

	D3DXMATRIX MtxWorld;
	D3DXMatrixIdentity(&MtxWorld);
	MtxWorld = InvView * MtxScaling *MtxTransform;

	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetTransform(D3DTS_WORLD, &MtxWorld);
	Device->SetMaterial(&g_Material);

	Device->SetFVF(FVF_BILLBOARD);
	Device->SetTexture(0, pTexture->lpTexture());
	Device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Polygon, sizeof(BillboardVertex));
}

void BillBoardShadow_Create(D3DXVECTOR3 Position,D3DXVECTOR3 Scale)
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationX(&MtxRotation,D3DXToRadian(90));

	D3DXMATRIX MtxTransform;
	D3DXMatrixTranslation(&MtxTransform, Position.x, 0.002f, Position.z);

	D3DXMATRIX MtxScaling;
	D3DXMatrixScaling(&MtxScaling, Scale.x, Scale.y, Scale.z);

	D3DXMATRIX MtxWorld;
	D3DXMatrixIdentity(&MtxWorld);
	MtxWorld = MtxScaling * MtxRotation *MtxTransform;

	LPDIRECT3DDEVICE9 Device = System_GetDevice();

	NLighting::Set_AlphaTest(true,200);
	Device->SetRenderState(D3DRS_BLENDOP,D3DBLENDOP_REVSUBTRACT);
	Device->SetRenderState(D3DRS_SRCBLEND,D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND,D3DBLEND_ONE);

	Device->SetTransform(D3DTS_WORLD, &MtxWorld);

	Device->SetMaterial(&g_Material);
	Device->SetTexture(0, NTexture::Get_Texture(NTexture::Billboard_Shadow));

	Device->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(BillboardVertex));
	Device->SetFVF(FVF_BILLBOARD);
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	Device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	Device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	//背景DSETのブレンド設定
	Device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

	NLighting::Set_AlphaTest(false,0);
}

//-------------------------------------
//	終了処理
//-------------------------------------
void BillBoard_Finalaize()
{
	if(g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
}

D3DXMATRIX InvMatrix()
{
	D3DXMATRIX InvView;
	D3DXMatrixTranspose(&InvView, &ACamera::Get_ViewMatrix());
	InvView._14 = 0.0f;
	InvView._24 = 0.0f;
	InvView._34 = 0.0f;
	return InvView;
}