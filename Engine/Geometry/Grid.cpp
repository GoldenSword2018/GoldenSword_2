//
//	Grid.cpp
//		Author:HIROMASA IEKDA	DATE:2018/09/27
//===============================================
#include<d3dx9.h>
#include"System.h"
#include"input.h"

#include"Grid.h"
#include"CCamera.h"
#include"CCamera.h"
#include"Lighting.h"

//===============================================
//	マクロ	
//===============================================
#define FVF_GRID_VERTEX3D (D3DFVF_XYZ | D3DFVF_DIFFUSE)

//===============================================
//	構造体
//===============================================
typedef struct GridVertex3D
{
	D3DXVECTOR3 Position;
	D3DCOLOR Color;
}GridVertex3D;

//===============================================
//	グローバル変数
//===============================================
static D3DMATERIAL9 g_Material;

static GridVertex3D g_Grid[46] = {};
static GridVertex3D g_AtArrow[18] = 
{
	//X軸
	{ D3DXVECTOR3(2.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,0,0,255) },
	{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,0,0,255) },
	{ D3DXVECTOR3(1.8f,0.2f,0.0f),D3DCOLOR_RGBA(255,0,0,255) },
	{ D3DXVECTOR3(2.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,0,0,255) },
	{ D3DXVECTOR3(1.8f,-0.2f,0.0f),D3DCOLOR_RGBA(255,0,0,255) },
	{ D3DXVECTOR3(2.0f,0.0f,0.0f),D3DCOLOR_RGBA(255,0,0,255) },

	//Z軸
	{ D3DXVECTOR3(0.0f,0.0f,2.0f),D3DCOLOR_RGBA(0,0,255,255) },
	{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_RGBA(0,0,255,255) },
	{ D3DXVECTOR3(0.0f,0.0f,2.0f),D3DCOLOR_RGBA(0,0,255,255) },
	{ D3DXVECTOR3(0.0f,0.2f,1.8f),D3DCOLOR_RGBA(0,0,255,255) },
	{ D3DXVECTOR3(0.0f,0.0f,2.0f),D3DCOLOR_RGBA(0,0,255,255) },
	{ D3DXVECTOR3(0.0f,-0.2f,1.8f),D3DCOLOR_RGBA(0,0,255,255) },

	//Y軸
	{ D3DXVECTOR3(0.0f,2.0f,0.0f),D3DCOLOR_RGBA(0,255,0,255) },
	{ D3DXVECTOR3(0.0f,0.0f,0.0f),D3DCOLOR_RGBA(0,255,0,255) },
	{ D3DXVECTOR3(0.0f,2.0f,0.0f),D3DCOLOR_RGBA(0,255,0,255) },
	{ D3DXVECTOR3(0.2f,1.8f,0.0f),D3DCOLOR_RGBA(0,255,0,255) },
	{ D3DXVECTOR3(0.0f,2.0f,0.0f),D3DCOLOR_RGBA(0,255,0,255) },
	{ D3DXVECTOR3(-0.2f,1.8f,0.0f),D3DCOLOR_RGBA(0,255,0,255) },
};

//===============================================
//	初期化
//===============================================
void Grid_Initialize()
{
#if !defined DISABLE_GRID
	g_Material.Diffuse = g_Material.Ambient = D3DXCOLOR(1.0f,1.0f,1.0f,1.0f);

	const float Mx = GRID_WIDTH * 5.0;
	const float Mz = GRID_WIDTH * 5.0;

	//グリッド
	for(int i = 0; i < 11; i++)
	{
		int n = i * 4;
		g_Grid[n].Position		= D3DXVECTOR3((float)GRID_WIDTH * (i - 5),0,-Mz);
		g_Grid[n + 1].Position	= D3DXVECTOR3((float)GRID_WIDTH * (i - 5),0, Mz);
		g_Grid[n + 2].Position	= D3DXVECTOR3(-Mx,0, (float)GRID_WIDTH * (i - 5));
		g_Grid[n + 3].Position	= D3DXVECTOR3(Mx, 0, (float)GRID_WIDTH * (i - 5));

		if(i == 5)
		{
			//XZ軸色
			g_Grid[n].Color		= D3DCOLOR_RGBA(0, 0, 255, 255);
			g_Grid[n + 1].Color = D3DCOLOR_RGBA(0, 0, 255, 255);
			g_Grid[n + 2].Color = D3DCOLOR_RGBA(255, 0, 0, 255);
			g_Grid[n + 3].Color = D3DCOLOR_RGBA(255, 0, 0, 255);
			continue;
		}

		g_Grid[n].Color		= GRID_COLOR;
		g_Grid[n + 1].Color = GRID_COLOR;
		g_Grid[n + 2].Color = GRID_COLOR;
		g_Grid[n + 3].Color = GRID_COLOR;
	}

	//Y軸
	g_Grid[44] = { D3DXVECTOR3(0,GRID_WIDTH * 5.0f,0),D3DCOLOR_RGBA(0,255,0,255)};
	g_Grid[45] = { D3DXVECTOR3(0,-GRID_WIDTH * 5.0f,0),D3DCOLOR_RGBA(0,255,0,255) };


#endif
}

//===============================================
//	描画
//===============================================
void Grid_Render()
{
#if !defined DISABLE_GRID

	NLighting::Set_MaterialDisEnable();	//マテリアル無効
	NLighting::Set_Light(FALSE);

	D3DXMATRIX mtxWorld;										//ワールド変換行列
	D3DXMatrixIdentity(&mtxWorld);								//単位行列の設定
	System_GetDevice()->SetTransform(D3DTS_WORLD, &mtxWorld);	//デバイスへ登録

	//------------------------------------
	//	描画
	//------------------------------------
	System_GetDevice()->SetFVF(FVF_GRID_VERTEX3D);
	System_GetDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 23, &g_Grid, sizeof(g_Grid[0]));


	D3DXMatrixIdentity(&mtxWorld);
	ACamera* pCamera = ACamera::Get_Main();
	D3DXMatrixTranslation(&mtxWorld,pCamera->at.x, pCamera->at.y, pCamera->at.z);
	System_GetDevice()->SetTransform(D3DTS_WORLD,&mtxWorld);
	System_GetDevice()->SetFVF(FVF_GRID_VERTEX3D);
	System_GetDevice()->DrawPrimitiveUP(D3DPT_LINELIST, 9, &g_AtArrow, sizeof(g_AtArrow[0]));

	NLighting::Set_MaterialEnable();

#endif
}