//
//	CMesh.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/14
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include"common.h"
#include"System.h"
#include"Lighting.h"

//class	
#include"Cube.h"
#include"CMesh.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================

//===============================================
//	CMesh 抽象
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
AMesh::AMesh()
{
	
}

//===============================================
//	CStandardMesh
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CStandardMesh::CStandardMesh():AMesh()
{
	this->pTexture = new NTexture::Texture();
	this->Material.Diffuse = this->Material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	this->FVF = FVF_CUBE_VERTEX3D;
	this->PrimitiveType = CUBE_PRIMITIVE_TYPE;
	this->Model = GetModel_Cube();
	this->DataSize = sizeof(CubeVertex3D);
	this->PrimitiveCount = CUBE_PRIMITIVE_NUM;
}

//-------------------------------------
//	描画
//-------------------------------------
void CStandardMesh::begin()
{
	LPDIRECT3DDEVICE9 Device = System_GetDevice();
	Device->SetMaterial(&this->Material);

	Device->SetFVF(this->FVF);
	Device->SetTexture(0, pTexture->lpTexture());

	Device->DrawPrimitiveUP(this->PrimitiveType, this->PrimitiveCount, this->Model, this->DataSize);

	return;
}

//-------------------------------------
//	テクスチャ設定
//-------------------------------------
void CStandardMesh::Set_Texture(NTexture::Texture Texture)
{
	this->pTexture = &Texture;
}

void CStandardMesh::Set_Texture(NTexture::Texture* pTexture)
{
	this->pTexture = pTexture;
}

//===============================================
//	CXModelMesh Xモデルデータ
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CXModelMesh::CXModelMesh()
{
	this->pMesh = NULL;
	this->pMeshMaterials = NULL;
	this->pMeshTextures = NULL;
	this->dwNumMaterials = NULL;
}

CXModelMesh::CXModelMesh(char* ModelFile, char* path)
{
	NModel::Load_XModelMesh(this,ModelFile,path);
}

//-------------------------------------
//	描画
//-------------------------------------
void CXModelMesh::begin()
{
	NLighting::Set_Light(TRUE);

	//マテリアルの数だけループさせる
	for (DWORD i = 0; i < this->dwNumMaterials; i++)
	{
		//マテリアル設定
		System_GetDevice()->SetMaterial(&this->pMeshMaterials[i]);
		//テクスチャ設定
		System_GetDevice()->SetTexture(0, this->pMeshTextures[i]);
		//レンダリング
		this->pMesh->DrawSubset(i);
	}

	NLighting::Set_Light(FALSE);
}

//===============================================
//	モデル名
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CXModelName::CXModelName(NModel::Name name)
{
	this->Model = name;
}

//-------------------------------------
//	描画
//-------------------------------------
void CXModelName::begin()
{
	NModel::Data* pMesh = NModel::Get(Model);

	NLighting::Set_Light(TRUE);

	for(DWORD i = 0; i < pMesh->dwNumMaterials; i++)
	{
		System_GetDevice()->SetMaterial(&pMesh->pMaterials[i]);
		System_GetDevice()->SetTexture(0,pMesh->pTextures[i]);
		pMesh->pMesh->DrawSubset(i);
	}

	NLighting::Set_Light(FALSE);
}

namespace NModel
{
	void Load_XModelMesh(CXModelMesh* LoadMesh, char* ModelFile, char* path)
	{
		Data LoadData;
		XModel_Load(&LoadData, path, ModelFile);

		LoadMesh->pMesh = LoadData.pMesh;
		LoadMesh->pMeshMaterials = LoadData.pMaterials;
		LoadMesh->pMeshTextures = LoadData.pTextures;
		LoadMesh->dwNumMaterials = LoadData.dwNumMaterials;
	}
}
