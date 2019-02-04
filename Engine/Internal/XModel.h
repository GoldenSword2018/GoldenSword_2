//
//	XModel.h
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	変更者 Changed By
//		Name:Minoda Takamasa	DATE:2018/10/23
//
//-----------------------------------------------
//エラー表示
//
//	・Models//　
//		XModel::NameとPathの数が合っていない
//
//===============================================
#pragma once
#ifndef XMODEL_H
#define XMODEL_H

//================================================
//	インクルード	include
//================================================
#include<d3dx9.h>
#include<string.h>

//================================================
//	マクロ定義	define
//================================================
#define MODELS_FILE ("Models/")
#define MODELS_FILE_NUM (60)
#define MODELS_NAME_NUM (30)

//===============================================
//	XModel 名前空間
//===============================================
namespace NModel
{
	//==============================================
	//	構造体
	//==============================================

	//モデルのデータ型
	struct Data
	{
		LPD3DXMESH pMesh;
		D3DMATERIAL9* pMaterials;
		LPDIRECT3DTEXTURE9* pTextures;
		DWORD dwNumMaterials;
	};

	//==============================================
	//	列挙
	//==============================================

	//モデル名
	const enum Name
	{
		AIRPLANE_BODY,
		AIRPLANE_PROPELLER,
		AIRPLANE_WingBD,
		AIRPLANE_WingBU,
		AIRPLANE_WingLD,
		AIRPLANE_WingLU,
		AIRPLANE_WingRD,
		AIRPLANE_WingRU,
		AIRPLANE_MODEL,
		TREE,
		BULLET,
		GUN,
		TARGET,
		NAME_END,
		MODEL_NONE
	};

	//==============================================
	//	関数
	//==============================================
	void XModel_Load(Data* LoadData, const char* File, const char* ModelFile);
	void Render(const LPD3DXMESH pMesh,const D3DMATERIAL9* pMaterials,const LPDIRECT3DTEXTURE9* pTextures, const DWORD dwNumMaterials);
	void Render(const Name index);
	void Initialize();
	void Finalize();
	Data* Get(const Name name);
}

#endif