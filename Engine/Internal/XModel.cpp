//
//	XModel.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/19
//===============================================
//	変更者 Changed By 
//		Name:Minoda Takamasa DATE:2018/10/23
//		Name:HIROMASA IKEDA	 DATE:2018/11/15
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<d3dx9.h>

#include"XModel.h"
#include"System.h"

//Class


//===============================================
//	マクロ定義		define
//===============================================

//アクセス
struct Path
{
 	NModel::Name name;
	const char FileName[MODELS_FILE_NUM];	//モデルの入っているファイル(テクスチャを参照する為)
	const char ModelName[MODELS_NAME_NUM];	//xモデル
};

//===============================================
//	XModel 名前空間
//===============================================
namespace NModel
{
	//==============================================
	//	各モデルデータ
	//==============================================

	//各モデルのPathを設定
	static Path path[] =
	{
		{ AIRPLANE_BODY,"Airplane_Body","Airplane_Body.x" },
		{ AIRPLANE_PROPELLER,"Airplane_Propeller","Airplane_Propeller.x" },
		{ AIRPLANE_WingBD,"Airplane_WingBD","Airplane_WingBD.x" },
		{ AIRPLANE_WingBU,"Airplane_WingBU","Airplane_WingBU.x" },
		{ AIRPLANE_WingLD,"Airplane_WingLD","Airplane_WingLD.x" },
		{ AIRPLANE_WingLU,"Airplane_WingLU","Airplane_WingLU.x" },
		{ AIRPLANE_WingRD,"Airplane_WingRD","Airplane_WingRD.x" },
		{ AIRPLANE_WingRU,"Airplane_WingRU","Airplane_WingRU.x" },
		{ AIRPLANE_MODEL,"Airplane","Airplane.x" },
		{ TREE,"Tree","Tree.x" },
		{ BULLET,"Bullet","Bullet.x"},
		{ GUN,"Gun","Gun.x"},
		{ TARGET,"Target","Target.x"}
	};

	//データ保存
	static Data Index[NAME_END];

	//==============================================
	//	関数
	//==============================================

	//---------------------------------
	//	モデル読み込み
	//---------------------------------
	void XModel_Load(Data* LoadData,const char* File,const char* ModelFile)
	{
		HRESULT hr;
		char FilePath[MODELS_FILE_NUM + MODELS_NAME_NUM + 10] = { "\0" };

		strcat(FilePath,MODELS_FILE);
		strcat(FilePath,File);
		strcat(FilePath,"/");
		strcat(FilePath,ModelFile);

		LPD3DXBUFFER pD3DXMtrlBuffer = NULL;

		hr = D3DXLoadMeshFromX(
			FilePath,
			D3DXMESH_SYSTEMMEM,
			System_GetDevice(),
			NULL,
			&pD3DXMtrlBuffer,
			NULL,
			&LoadData->dwNumMaterials,
			&LoadData->pMesh
		);

		if (FAILED(hr))
		{
			char ErrorText[100] = { "\0" };
			strcat(ErrorText, FilePath);
			strcat(ErrorText, "\nモデルデータが読み込めませんでした。");

			MessageBox(*System_GethWnd(), ErrorText, "エラー", MB_OK);
			DestroyWindow(*System_GethWnd());
			return;
		}

		//モデルのテクスチャへのアクセス
		strcpy(FilePath, "\0");	//初期化
		strcat(FilePath, MODELS_FILE);
		strcat(FilePath, File);
		strcat(FilePath, "/");

		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
		LoadData->pMaterials = new D3DMATERIAL9[LoadData->dwNumMaterials];
		LoadData->pTextures = new LPDIRECT3DTEXTURE9[LoadData->dwNumMaterials];

		D3DXMATERIAL* pD3DXMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

		for (DWORD i = 0; i < LoadData->dwNumMaterials; i++)
		{
			LoadData->pMaterials[i] = d3dxMaterials[i].MatD3D;
			LoadData->pMaterials[i].Ambient = LoadData->pMaterials[i].Diffuse;
			LoadData->pTextures[i] = NULL;

			if (d3dxMaterials[i].pTextureFilename != NULL &&
				lstrlen(d3dxMaterials[i].pTextureFilename) > 0)
			{
				//テクスチャのパス
				char TexturePath[200] = { "\0" };
				strcat(TexturePath, FilePath);
				strcat(TexturePath, d3dxMaterials[i].pTextureFilename);

				hr = D3DXCreateTextureFromFile(
					System_GetDevice(),
					TexturePath,
					&LoadData->pTextures[i]
				);

				if (FAILED(hr))
				{
					char ErrorText[200] = { "\0" };
					strcat(ErrorText, TexturePath);
					strcat(ErrorText, "\nテクスチャ読み込みに失敗しました。");

					MessageBox(NULL, ErrorText, "エラー", MB_OK);
				}
			}
		}

		pD3DXMtrlBuffer->Release();
	}

	//---------------------------------
	//	XModel内Index読み込み
	//---------------------------------
	void Load(const int index)
	{
		XModel_Load(&Index[index],path[index].FileName,path[index].ModelName);
	}

	//---------------------------------
	//	初期化処理
	//---------------------------------
	void Initialize()
	{
		for(int index = 0; index<NAME_END; index++)
		{
			Load(index);
		}
	}

	//---------------------------------
	//	描画
	//---------------------------------
	void Render(const Name index)
	{
		//マテリアルの数だけループさせる
		for (DWORD i = 0; i < Index[index].dwNumMaterials; i++)
		{
			//マテリアル設定
			System_GetDevice()->SetMaterial(&Index[index].pMaterials[i]);
			//テクスチャ設定
			System_GetDevice()->SetTexture(0, Index[index].pTextures[i]);
			//レンダリング
			Index[index].pMesh->DrawSubset(i);
		}
	}

	void Render(const LPD3DXMESH pMesh, const D3DMATERIAL9* pMaterials, const LPDIRECT3DTEXTURE9* pTextures, const DWORD dwNumMaterials)
	{
		//マテリアルの数だけループさせる
		for (DWORD i = 0; i < dwNumMaterials; i++)
		{
			//マテリアル設定
			System_GetDevice()->SetMaterial(&pMaterials[i]);
			//テクスチャ設定
			System_GetDevice()->SetTexture(0, pTextures[i]);
			//レンダリング
			pMesh->DrawSubset(i);
		}
	}

	//---------------------------------
	//	終了処理
	//---------------------------------
	void Finalize()
	{
		for (DWORD i = 0; i < NAME_END; i++)
		{
			delete Index[i].pTextures;
			delete Index[i].pMaterials;
			Index[i].pMesh->Release();
		}
	}

	//---------------------------------
	//	モデル データ取得
	//---------------------------------
	Data* Get(const Name name)
	{
		return &Index[name];
	}
}
