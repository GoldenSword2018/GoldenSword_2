//
//	Screwdrop.cpp
//		Author:ハン	DATE:2018/10/23
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------
#include "Screwdrop.h"
#include "CScrew.h"

#include"CRender.h"
#include"CMesh.h"

//===============================================
//	マクロ定義
//===============================================
#define SCREW_DROP_SPEED (0.01f)　　	//落ちる時の速度
#define SCREW_ROTATION_SPEED (0.01f)	//回転時の移動速度
#define ROTATION_FRAME_MAX (120)		//回転フレーム数

//===============================================
//	構造体
//===============================================

//===============================================
//	グローバル変数
//===============================================
Screwdrop g_Screwdrop[SCREW_NUM];
static CXModelName* Model;

//===============================================
//	関数
//===============================================

//-------------------------------------
//	初期化
//-------------------------------------
void Screwdrop_Init()
{
	for (int i = 0; i < SCREW_NUM; i++)
	{
		g_Screwdrop[i].IsEnable = false;
		g_Screwdrop[i].ScrewPosition = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		g_Screwdrop[i].face = D3DXVECTOR3(0.5f, 0.5f, 0.5f);
		g_Screwdrop[i].rotation_count = 0;
	}

	Model = new CXModelName(NModel::TREE);
}

//-------------------------------------
//	更新
//-------------------------------------
void Screwdrop_Update()
{
	for (int i = 0; i< SCREW_NUM; i++)
	{
		if (g_Screwdrop[i].IsEnable)
		{
			if (g_Screwdrop[i].rotation_count <= ROTATION_FRAME_MAX)
			{
				g_Screwdrop[i].ScrewPosition += g_Screwdrop[i].face * SCREW_ROTATION_SPEED;
				g_Screwdrop[i].rotation_count++;
			}
			else
			{
				if (g_Screwdrop[i].ScrewPosition.y >= 0.0f/*地面*/)
				{
					g_Screwdrop[i].ScrewPosition.y -= 0.01f;
				}
				else
				{
					Screwdrop_DisEnable(i);
				}
			}
		}
	}
}

//-------------------------------------
//	描画
//-------------------------------------
void Screwdrop_Render()
{
	for (int i = 0; i < SCREW_NUM; i++)
	{
		if (g_Screwdrop[i].IsEnable)
		{
			D3DXMATRIX mtxWorld;
			D3DXMATRIX mtxRotation;
			D3DXMATRIX mtxTranslation;

			D3DXMatrixTranslation(&mtxTranslation, g_Screwdrop[i].ScrewPosition.x, g_Screwdrop[i].ScrewPosition.y, g_Screwdrop[i].ScrewPosition.z);

			D3DXMatrixRotationAxis(&mtxRotation, &g_Screwdrop[i].face,D3DXToRadian(g_Screwdrop[i].rotation_count));	

			mtxWorld = mtxRotation * mtxTranslation;
			NRender3D::Render(Model, &mtxWorld);
		}
	}
}

//-------------------------------------
//	生成
//-------------------------------------
void  Screwdrop_Create(D3DXVECTOR3 pos_screw, D3DXVECTOR3 face)
{
	for (int i = 0; i< SCREW_NUM; i++)
	{
		if (!g_Screwdrop[i].IsEnable)
		{
			g_Screwdrop[i].ScrewPosition = pos_screw;
			g_Screwdrop[i].face = face;
			g_Screwdrop[i].IsEnable = true;
			g_Screwdrop[i].rotation_count = 0;
			return;
		}
	}
}

//-------------------------------------
//	削除
//-------------------------------------
void Screwdrop_DisEnable(int index)
{
	g_Screwdrop[index].IsEnable = false;
}
