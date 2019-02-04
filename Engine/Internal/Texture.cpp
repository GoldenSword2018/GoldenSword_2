//
//	Texture.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/13
//===============================================
#define _CRT_SECURE_NO_WARNINGS
#include<d3dx9.h>
#include<math.h>
#include"Texture.h"
#include"System.h"
#include"Animation.h"
#include"vector"

#define TEXTURE_FILE ("Texture/")
#define TEXTURE_NAME_NUM (60)

namespace NTexture
{
	//==============================================
	//	構造体
	//==============================================
	struct Path
	{
		Name name;
		const char TextureName[TEXTURE_NAME_NUM];
	};

	//==============================================
	//	グローバル変数
	//==============================================
	static Data Index[Name::NAME_END] = //データ
	{
		{ CubeTexture,"tex.png" },
		{ BillBoardTex,"bullet000.png" },
		{ MeshFieldTex,"MeshGround.jpg" },
		{ MeshCylinderTex,"skytex1.jpeg" },
		{ Billboard_Burst,"bomb.png" },
		{ Billboard_Shadow,"shadow000.jpg" },
		{ Mesh_Wall,"Wall.jpg" },
		{ Reticle,"Reticle.png"},
		{ TargetText,"Target_Text.png"},
		{ NumberTex,"Number.png"},
		{ NAME_NONE,"none.png" }
	};
	
	//==============================================
	//	関数
	//==============================================
	//
	//	Classのコンストラクタで呼び出すと
	//	System_GetDevice()などの関数はコンパイル時にデータが
	//	確定していない様子。
	//

	bool Load(Data* LoadData,const char* path)
	{
		HRESULT hr;
		char ErrorText[256] = {};

		char FilePath[TEXTURE_NAME_NUM + 10] = { '\0' };
		D3DXIMAGE_INFO Texture_Info;	//画像データ情報

		strcat(&FilePath[0], TEXTURE_FILE);
		strcat(&FilePath[0], path);

		//読み込みが失敗した時にはg_pTexture[i]にnullが置かれる
		hr = D3DXCreateTextureFromFile(System_GetDevice(), FilePath, &LoadData->pTexture);

		if (FAILED(hr))
		{
			//エラーの表示
			strcat(ErrorText, path);
			strcat(ErrorText, "\n");
			MessageBox(*System_GethWnd(), ErrorText, "読み込み失敗", MB_OK);
			DestroyWindow(*System_GethWnd());
			LoadData = NULL;
			return false;
		}
		else
		{
			//画像データ取得
			D3DXGetImageInfoFromFile(FilePath, &Texture_Info);
			LoadData->height = Texture_Info.Height;
			LoadData->width = Texture_Info.Width;
		}
		
		return true;
	}

	bool Load_Index(Data* LoadData,int Size)
	{
		for(int i=0;i<Size;i++)
		{
			Load(&LoadData[i],&LoadData[i].TexturePath[0]);
		}

		return true;
	}

	void UnLoad(Data* data)
	{
		if(data->pTexture != NULL)
		{
			data->pTexture->Release();
			data->pTexture = NULL;
		}
	}

	//------------------------------------
	//	初期化処理
	//------------------------------------
	void Initialize()
	{
		for(int i = 0; i <Name::NAME_END; i++)
		{
			Load(&Index[i],&Index[i].TexturePath[0]);
		}

		NTexture::FrameInit();	//フレームを初期化
	}

	//------------------------------------
	//	終了処理
	//------------------------------------
	void Finalize()
	{
		for (int i = 0; i < Name::NAME_END; i++)
		{
			if (Index[i].pTexture != NULL)
			{
				Index[i].pTexture->Release();
				Index[i].pTexture = NULL;
			}
		}
	}

	//------------------------------------
	//	Get_Texture
	//------------------------------------
	LPDIRECT3DTEXTURE9 Get_Texture(const Name name)
	{
		return Index[name].pTexture;
	}

	//------------------------------------
	//	Get_Data
	//------------------------------------
	Data* Get_Data(const Name name)
	{
		return &Index[name];
	}

	//------------------------------------
	//	Get_Width
	//------------------------------------
	UINT Get_Width(const Name name)
	{
		return Index[name].width;
	}

	//------------------------------------
	//	Get_Height
	//------------------------------------
	UINT Get_Height(const Name name)
	{
		return Index[name].height;
	}

	//==============================================
	//	Class
	//==============================================

	//=========================================
	//	Texture
	//=========================================

	Texture::Texture()
	{

	}

	Texture::~Texture()
	{
		
	}

	LPDIRECT3DTEXTURE9 Texture::lpTexture()
	{
		return Index[NAME_NONE].pTexture;
	}

	UINT Texture::Width()
	{
		return Index[NAME_NONE].width;
	}

	UINT Texture::Height()
	{
		return Index[NAME_NONE].height;
	}

	D3DXVECTOR2 Texture::TexCoord()
	{
		return{ 0.0f,0.0f };
	}

	D3DXVECTOR2 Texture::TexScale()
	{
		return{ 1.0f,1.0f };
	}


	//====================================
	//	NameTexture
	//====================================
	NameTexture::NameTexture(Name name, D3DXVECTOR2 TexCoord,D3DXVECTOR2 TexScale)
	{
		this->Coord = TexCoord;
		this->Scale = TexScale;
		this->name = name;
	}

	NameTexture::~NameTexture()
	{
		
	}

	LPDIRECT3DTEXTURE9 NameTexture::lpTexture()
	{
		return Index[this->name].pTexture;
	}

	UINT NameTexture::Width()
	{
		return Index[this->name].width;
	}

	UINT NameTexture::Height()
	{
		return Index[this->name].height;
	}

	D3DXVECTOR2 NameTexture::TexCoord()
	{
		return this->Coord;
	}

	D3DXVECTOR2 NameTexture::TexScale()
	{
		return this->Scale;
	}

	void NameTexture::Clip(UINT x, UINT y, UINT w, UINT h)
	{
		this->Coord = { (float)x / this->Width(),(float)y / this->Height() };
		this->Scale = { (float)w / this->Width(),(float)h / this->Height() };
	}

	//====================================
	//	CTexture
	//====================================
	CTexture::CTexture(Data* data, UINT x, UINT y, UINT w, UINT h)
	{
		this->m_lpdata = data;
		this->m_Coord = { (float)x / this->Width(),(float)y / this->Height() };
		this->m_Scale = { (float)w / this->Width(),(float)h / this->Height() };
		x = x;
	}
	
	CTexture::~CTexture()
	{

	}

	LPDIRECT3DTEXTURE9 CTexture::lpTexture()
	{
		return this->m_lpdata->pTexture;
	}
	UINT CTexture::Width()
	{
		return this->m_lpdata->width;
	}

	UINT CTexture::Height()
	{
		return this->m_lpdata->height;
	}

	D3DXVECTOR2 CTexture::TexCoord()
	{
		return this->m_Coord;
	}
	
	D3DXVECTOR2 CTexture::TexScale()
	{
		return this->m_Scale;
	}

	void CTexture::Clip(UINT x, UINT y, UINT w, UINT h)
	{
		this->m_Coord = { (float)x / this->Width(),(float)y / this->Height() };
		this->m_Scale = { (float)w / this->Width(),(float)h / this->Height() };
	}

	//====================================
	//	PathTexture
	//====================================
	PathTexture::PathTexture(const char* path,D3DXVECTOR2 TexCoord,D3DXVECTOR2 TexScale)
	{
		this->Coord = TexCoord;
		this->Scale = TexScale;
		Load(&this->data, path);
	}

	PathTexture::PathTexture(const char* path, UINT TexW, UINT TexH, UINT x, UINT y, UINT w, UINT h)
	{
		this->Coord = { (float)x / TexW,(float)y / TexH };
		this->Scale = { (float)w / TexW,(float)h / TexH };
		Load(&this->data, path);
	}

	PathTexture::~PathTexture()
	{
		//UnLoad(&this->data);
	}

	LPDIRECT3DTEXTURE9 PathTexture::lpTexture()
	{
		return this->data.pTexture;
	}

	UINT PathTexture::Width()
	{
		return this->data.width;
	}

	UINT PathTexture::Height()
	{
		return this->data.height;
	}

	D3DXVECTOR2 PathTexture::TexCoord()
	{
		return this->Coord;
	}

	D3DXVECTOR2 PathTexture::TexScale()
	{
		return this->Scale;
	}

	void PathTexture::Clip(UINT x, UINT y, UINT w, UINT h)
	{
		this->Coord = { (float)x / this->Width(),(float)y / this->Height() };
		this->Scale = { (float)w / this->Width(),(float)h / this->Height() };
	}

	//====================================
	//	CAnimation
	//====================================
	CAnimation::CAnimation(int MaxPatern, int YMaxPatern, int Waitframe)
	{
		this->AnimaPatern = 0;
		this->MaxPatern = MaxPatern;
		this->YMaxPatern = YMaxPatern;
		this->Waitframe = Waitframe;
		this->Createframe = NTexture::Get_Frame();
	}
}

