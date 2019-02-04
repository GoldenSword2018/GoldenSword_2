//
//	MeshField.cpp
//		Author:HIROMASA IKEDA	DATE:2018/11/27
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"
#include"MeshField.h"
#include"System.h"

#define FVF_MF_VERTEX3D (D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1)

//-------------------------------------
//	構造体
//-------------------------------------
struct Vertex3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR2 Coord;
};

//------------------------------------
//	グローバル変数
//-----------------------------------

//	MeshField Ground
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pGround_VertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 g_pGround_IndexBuffer = NULL;

Vertex3D* g_pGround_Vertex = NULL;
WORD* g_pGround_Index = NULL;

const int Ground_ReturnNum = MF_GROUND_GRID_DEPTH- 1;
const int Ground_VertexNum = ((MF_GROUND_GRID_WIDTH + 1) * 2)*MF_GROUND_GRID_DEPTH + (2 * Ground_ReturnNum);

//	MeshField Cylinder
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pCylinder_VertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 g_pCylinder_IndexBuffer = NULL;

Vertex3D* g_pCylinder_Vertex = NULL;
WORD* g_pCylinder_Index = NULL;

const int Cylinder_VertexNum = (MF_CYLINDER_GRID_WIDTH + 1) * (MF_CYLINDER_GRID_HEIGHT + 1) + ((MF_CYLINDER_GRID_HEIGHT - 1) * 2);

//	MeshField SkyDome
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pSkyDome_VertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 g_pSkyDome_IndexBuffer = NULL;

Vertex3D* g_pSkyDome_Vertex = NULL;
WORD* g_pSkyDome_Index = NULL;

const int SkyDome_VertexNum = (MF_SKYDORM_GRID_WIDTH + 1) * (MF_SKYDORM_GRID_HEIGHT + 1) + ((MF_SKYDORM_GRID_WIDTH - 1) * 2);

//	MeshField Wall
//-------------------------------------
LPDIRECT3DVERTEXBUFFER9 g_pWall_VertexBuffer = NULL;
LPDIRECT3DINDEXBUFFER9 g_pWall_IndexBuffer = NULL;

Vertex3D* g_pWall_Vertex = NULL;
WORD* g_pWall_Index = NULL;

const int Wall_ReturnNum = MF_WALL_GRID_HEIGHT - 1;
const int Wall_VertexNum = ((MF_WALL_GRID_WIDTH + 1)*2) * MF_WALL_GRID_HEIGHT + (Wall_ReturnNum * 2);

const float fWidth = MF_WALL_WIDTH / MF_WALL_GRID_WIDTH;
const float fHeight = MF_WALL_HEIGHT / MF_WALL_GRID_HEIGHT;

const float fInitX = -MF_WALL_WIDTH * 0.5f;
const float fInitY = MF_WALL_HEIGHT * 0.5f;

//	マテリアル
//-------------------------------------
D3DMATERIAL9 g_Material;


//===============================================
//	NMeshField
//===============================================
namespace NMeshField
{
	//------------------------------------
	//	初期化
	//------------------------------------

	//------------------------------------
	//	Initialize_Ground
	//------------------------------------
	void Init_Ground()
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();
		Device->CreateVertexBuffer(
			sizeof(Vertex3D) * (MF_GROUND_GRID_WIDTH + 1) * (MF_GROUND_GRID_DEPTH + 1),
			D3DUSAGE_WRITEONLY,
			FVF_MF_VERTEX3D,
			D3DPOOL_MANAGED,
			&g_pGround_VertexBuffer,
			NULL
		);

		Device->CreateIndexBuffer(
			sizeof(DWORD) * Ground_VertexNum,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pGround_IndexBuffer,
			NULL
		);

		int nCount = 0;

		g_pGround_VertexBuffer->Lock(0,0,(void**)&g_pGround_Vertex,0);

		const float fWidth = MF_GROUND_SCALE_WIDTH / MF_GROUND_GRID_WIDTH;
		const float fDepth = MF_GROUND_SCALE_DEPTH / MF_GROUND_GRID_DEPTH;

		const float Initx = -MF_GROUND_SCALE_WIDTH * 0.5f;
		const float Initz = MF_GROUND_SCALE_DEPTH * 0.5f;

		float x = Initx;
		float z = Initz;

		for(int i = 0; i< (MF_GROUND_GRID_DEPTH + 1); i++)
		{
			for(int j = 0; j < (MF_GROUND_GRID_WIDTH + 1); j++)
			{
				g_pGround_Vertex[nCount + j].Position = D3DXVECTOR3(x, 0, z);
				g_pGround_Vertex[nCount + j].Normal = D3DXVECTOR3(0, -1, 0);
				g_pGround_Vertex[nCount + j].Coord = D3DXVECTOR2((float)j, (float)i);
				x += fWidth;
			}

			nCount += (MF_GROUND_GRID_WIDTH + 1);
			x = Initx;
			z -= fDepth;
		}

		g_pGround_VertexBuffer->Unlock();

		nCount = 0;

		g_pGround_IndexBuffer->Lock(0,0,(void**)&g_pGround_Index,0);

		for(int i = 0; i < MF_GROUND_GRID_DEPTH; i++)
		{
			int j = 0;

			
			//縮退ポリゴン
			if(i > 0)
			{
				g_pGround_Index[nCount] = g_pGround_Index[nCount - 1];
				g_pGround_Index[nCount + 1] = ((MF_GROUND_GRID_WIDTH + 1) * (i + 1)) + j;
				nCount += 2;
			}
			
			
			for(j = 0; j < (MF_GROUND_GRID_WIDTH + 1); j++)
			{
				g_pGround_Index[nCount] = ((MF_GROUND_GRID_WIDTH + 1) * (i + 1)) + j;
				g_pGround_Index[nCount + 1] = ((MF_GROUND_GRID_WIDTH + 1) * i) + j;
				nCount += 2;
			}
		}

		g_pGround_IndexBuffer->Unlock();
	}

	//------------------------------------
	//	Initialize_Cylinder
	//------------------------------------
	void Init_Cylinder()
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();
		Device->CreateVertexBuffer(
			sizeof(Vertex3D) * (MF_CYLINDER_GRID_HEIGHT + 1) * (MF_CYLINDER_GRID_WIDTH  +1),
			D3DUSAGE_WRITEONLY,
			FVF_MF_VERTEX3D,
			D3DPOOL_MANAGED,
			&g_pCylinder_VertexBuffer,
			NULL
		);

		Device->CreateIndexBuffer(
			sizeof(DWORD) * Cylinder_VertexNum,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pCylinder_IndexBuffer,
			NULL
		);

		int nCount = 0;

		g_pCylinder_VertexBuffer->Lock(0,0,(void**)&g_pCylinder_Vertex,0);

		float th = (float)(1.0f / MF_CYLINDER_GRID_HEIGHT);
		float tw = (float)(1.0f / (MF_CYLINDER_GRID_WIDTH * 2));

		for(int i = 0; i < (MF_CYLINDER_GRID_HEIGHT + 1); i++)
		{
			float y = (float)MF_CYLINDER_HEIGHT * i;

			for(int j = 0; j < MF_CYLINDER_GRID_WIDTH + 1; j++)
			{
				float x = (float)MF_CYLINDER_RADIUS * sinf(float(j * MF_CYLINDER_ANGLE));
				float z = (float)MF_CYLINDER_RADIUS * cosf(float(j * MF_CYLINDER_ANGLE));

				g_pCylinder_Vertex[nCount].Position = { x,y,z };
				g_pCylinder_Vertex[nCount].Normal = {0,-1,0};
				g_pCylinder_Vertex[nCount].Coord = { tw * j, 1 - (th * i)};
				nCount++;
			}
		}

		g_pCylinder_VertexBuffer->Unlock();

		nCount = 0;

		g_pCylinder_IndexBuffer->Lock(0,0,(void**)&g_pCylinder_Index,0);

		for(int i = 0; i < MF_CYLINDER_GRID_HEIGHT + 1; i++)
		{
			int j = 0;

			//縮退ポリゴン
			if(i > 0)
			{
				g_pCylinder_Index[nCount] = g_pCylinder_Index[nCount - 1];
				g_pCylinder_Index[nCount + 1] = ((MF_CYLINDER_GRID_WIDTH + 1) * i) + j;
				nCount += 2;
			}

			//回転
			for(; j < (MF_CYLINDER_GRID_WIDTH + 1); j++)
			{
				g_pCylinder_Index[nCount] = ((MF_CYLINDER_GRID_WIDTH + 1) * i) + j;
				g_pCylinder_Index[nCount + 1] = ((MF_CYLINDER_GRID_WIDTH + 1) * (i + 1) + j);
				nCount += 2;
			}
		}

		g_pCylinder_IndexBuffer->Unlock();
	}

	//------------------------------------
	//	Initialize_SkyDome
	//------------------------------------
	void Init_SkyDome()
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();
		Device->CreateVertexBuffer(
			sizeof(Vertex3D) * (MF_SKYDORM_GRID_WIDTH + 1) * (MF_SKYDORM_GRID_HEIGHT + 1),
			D3DUSAGE_WRITEONLY,
			FVF_MF_VERTEX3D,
			D3DPOOL_MANAGED,
			&g_pSkyDome_VertexBuffer,
			NULL
		);

		Device->CreateIndexBuffer(
			sizeof(DWORD) * SkyDome_VertexNum,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pSkyDome_IndexBuffer,
			NULL
		);

		int nCount = 0;

		g_pSkyDome_VertexBuffer->Lock(0,0,(void**)&g_pSkyDome_Vertex,0);

		float th = (float)(1.0f / MF_SKYDORM_GRID_HEIGHT);
		float tw = (float)(1.0f / MF_SKYDORM_GRID_WIDTH);

		for(int i = 0; i< MF_SKYDORM_GRID_HEIGHT + 1; i++)
		{
			float y = (float)(MF_SKYDORM_RADIUS * sinf(float(MF_SKYDORM_ANGLE_HEIGHT * i)));
			float radius = (float)(MF_SKYDORM_RADIUS * cosf(float(MF_SKYDORM_ANGLE_HEIGHT * i)));

			for(int j = 0; j < MF_SKYDORM_GRID_WIDTH + 1; j++)
			{
				float x = radius * sinf(float(MF_SKYDORM_ANGLE_WIDTH * j));
				float z = radius * cosf(float(MF_SKYDORM_ANGLE_WIDTH * j));

				g_pSkyDome_Vertex[nCount].Position = { x,y,z};
				g_pSkyDome_Vertex[nCount].Normal = { 0,-1,0};
				g_pSkyDome_Vertex[nCount].Coord = { tw * j, 1 - (th * i)};
				nCount++;
			}
		}

		g_pSkyDome_VertexBuffer->Unlock();

		nCount = 0;

		g_pSkyDome_IndexBuffer->Lock(0,0,(void**)&g_pSkyDome_Index,0);

		for(int i = 0; i < MF_SKYDORM_GRID_HEIGHT + 1; i++)
		{
			int j = 0;
			
			//縮退ポリゴン
			if(i > 0)
			{
				g_pSkyDome_Index[nCount] = g_pSkyDome_Index[nCount - 1];
				g_pSkyDome_Index[nCount + 1] = ((MF_SKYDORM_GRID_WIDTH + 1) * i) + j;
				nCount += 2;
			}
			
			for(j; j < MF_SKYDORM_GRID_WIDTH + 1; j++)
			{
				g_pSkyDome_Index[nCount] = ((MF_SKYDORM_GRID_WIDTH + 1) * i) + j;
				g_pSkyDome_Index[nCount + 1] = (MF_SKYDORM_GRID_WIDTH + 1) * (i + 1) + j;
				nCount += 2;
			}

		}

		g_pSkyDome_IndexBuffer->Unlock();
	}

	void Init_Wall()
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();
		Device->CreateVertexBuffer(
			sizeof(Vertex3D) * (MF_WALL_GRID_WIDTH + 1) * (MF_WALL_GRID_HEIGHT + 1),
			D3DUSAGE_WRITEONLY,
			FVF_MF_VERTEX3D,
			D3DPOOL_MANAGED,
			&g_pWall_VertexBuffer,
			NULL
		);
		Device->CreateIndexBuffer(
			sizeof(DWORD) * Wall_VertexNum,
			D3DUSAGE_WRITEONLY,
			D3DFMT_INDEX16,
			D3DPOOL_MANAGED,
			&g_pWall_IndexBuffer,
			NULL
		);

		int nCount = 0;

		float x = fInitX;
		float y = fInitY;

		g_pWall_VertexBuffer->Lock(0,0,(void**)&g_pWall_Vertex,0);

		for (int i = 0; i < MF_WALL_GRID_HEIGHT + 1; i++)
		{
			for (int j = 0; j < MF_WALL_GRID_WIDTH + 1; j++)
			{
				g_pWall_Vertex[nCount + j].Position = D3DXVECTOR3(x, y, 0.0f);
				g_pWall_Vertex[nCount + j].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
				g_pWall_Vertex[nCount + j].Coord = D3DXVECTOR2((float)j, (float)i);
				x += fWidth;
			}
			nCount += MF_WALL_GRID_WIDTH + 1;
			x = fInitX;
			y -= fHeight;
		}

		g_pWall_VertexBuffer->Unlock();

		nCount = 0;

		g_pWall_IndexBuffer->Lock(0,0,(void**)&g_pWall_Index,0);

		for(int i = 0; i < MF_WALL_GRID_HEIGHT; i++)
		{
			int j = 0;

			if(i > 0)
			{
				g_pWall_Index[nCount] = g_pWall_Index[nCount - 1];
				g_pWall_Index[nCount + 1] = (MF_WALL_GRID_WIDTH + 1) * (i + 1) + j;
				nCount += 2;
			}

			for(j = 0; j < MF_WALL_GRID_WIDTH + 1; j++)
			{
				g_pWall_Index[nCount] = (MF_WALL_GRID_WIDTH + 1) * (i + 1) + j;
				g_pWall_Index[nCount + 1] = (MF_WALL_GRID_WIDTH + 1) * i + j;
				nCount += 2;
			}
		}

		g_pWall_IndexBuffer->Unlock();
	}

	//------------------------------------
	//	初期化
	//------------------------------------
	void Initialize()
	{
		g_Material.Diffuse = g_Material.Ambient = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
		
		Init_Ground();
		Init_Cylinder();
		Init_SkyDome();
		Init_Wall();
	}
	
	//------------------------------------
	//	描画
	//------------------------------------

	//Ground
	void Render_Ground(const D3DXVECTOR3 Center,const NTexture::Name TextureName)
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();
		D3DXMATRIX mtxWorld;
		D3DXMatrixTranslation(&mtxWorld,Center.x,Center.y,Center.z);
		Device->SetTransform(D3DTS_WORLD,&mtxWorld);
		Device->SetMaterial(&g_Material);
		Device->SetStreamSource(0,g_pGround_VertexBuffer,0,sizeof(Vertex3D));
		Device->SetIndices(g_pGround_IndexBuffer);
		Device->SetFVF(FVF_MF_VERTEX3D);
		Device->SetTexture(0,NTexture::Get_Texture(TextureName));
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,Ground_VertexNum,0, Ground_VertexNum - 2);
	}

	//Cylinder
	void Render_Cylinder(const D3DXVECTOR3 Center,const NTexture::Name TextureName)
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();
		D3DXMATRIX mtxWorld;
		D3DXMatrixTranslation(&mtxWorld,Center.x,Center.y,Center.z);
		Device->SetTransform(D3DTS_WORLD,&mtxWorld);
		Device->SetMaterial(&g_Material);
		Device->SetStreamSource(0,g_pCylinder_VertexBuffer,0,sizeof(Vertex3D));
		Device->SetIndices(g_pCylinder_IndexBuffer);
		Device->SetTexture(0,NTexture::Get_Texture(TextureName));
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,Cylinder_VertexNum,0,(MF_CYLINDER_GRID_HEIGHT * MF_CYLINDER_GRID_WIDTH + ((MF_CYLINDER_GRID_HEIGHT - 1) * 2)) * 2);
	}

	//SkyDome
	void Render_SkyDome(const D3DXVECTOR3 Center, const NTexture::Name TextureName)
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();
		D3DXMATRIX mtxWorld;
		D3DXMatrixTranslation(&mtxWorld,Center.x, Center.y, Center.z);
		Device->SetTransform(D3DTS_WORLD,&mtxWorld);
		Device->SetMaterial(&g_Material);
		Device->SetStreamSource(0,g_pSkyDome_VertexBuffer,0,sizeof(Vertex3D));
		Device->SetIndices(g_pSkyDome_IndexBuffer);
		Device->SetFVF(FVF_MF_VERTEX3D);
		Device->SetTexture(0, NTexture::Get_Texture(TextureName));
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,SkyDome_VertexNum, 0, (MF_SKYDORM_GRID_HEIGHT * MF_SKYDORM_GRID_WIDTH + (MF_SKYDORM_GRID_HEIGHT - 1) * 2) * 2);
	}

	//Wall
	void Render_Wall(const D3DXVECTOR3 Center, const D3DXVECTOR3 Scale , const D3DXVECTOR3 Rotate, const NTexture::Name TextureName)
	{
		LPDIRECT3DDEVICE9 Device = System_GetDevice();

		D3DXMATRIX mtxWorld,mtxTrans,mtxRotate,mtxScale;
		D3DXMatrixTranslation(&mtxTrans, Center.x, Center.y + MF_WALL_HEIGHT * 0.5f, Center.z);
		D3DXMatrixScaling(&mtxScale,Scale.x,Scale.y,Scale.z);
		D3DXMatrixRotationYawPitchRoll(&mtxRotate,Rotate.y,Rotate.x,Rotate.z);
		mtxWorld = mtxScale * mtxRotate * mtxTrans;

		Device->SetTransform(D3DTS_WORLD,&mtxWorld);

		Device->SetMaterial(&g_Material);
		Device->SetStreamSource(0,g_pWall_VertexBuffer,0,sizeof(Vertex3D));
		Device->SetIndices(g_pWall_IndexBuffer);
		Device->SetFVF(FVF_MF_VERTEX3D);
		Device->SetTexture(0,NTexture::Get_Texture(TextureName));
		Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP,0,0,Wall_VertexNum,0,Wall_VertexNum-2);
	}

	//未動作
	void Render_Wall_Enclosure(const D3DXVECTOR3 Center, const D3DXVECTOR3 Scale,const NTexture::Name TextureName)
	{
		D3DXVECTOR3 Position = Center;
		Position.z += MF_WALL_WIDTH * Scale.z;
		Render_Wall(Position, { 0.0f,0.0f,0.0f },Scale, TextureName);
		
		Position = Center;
		Position.z -= MF_WALL_WIDTH * Scale.z;
		Render_Wall(Position, {0.0f,(float)(M_PI),0.0f}, Scale,TextureName);
		

		Position = Center;
		Position.x += MF_WALL_WIDTH * Scale.x;
		Render_Wall(Position, { 0.0f,(float)M_PI_2,0.0f }, Scale,TextureName);
		
		Position = Center;
		Position.x -= MF_WALL_WIDTH * Scale.x;
		Render_Wall(Position, { 0.0f,(float)-M_PI_2,0.0f }, Scale,TextureName);
		
	}

	//------------------------------------
	//	終了処理
	//------------------------------------

	//Finalize_Ground
	void Final_Ground()
	{
		if (g_pGround_IndexBuffer)
		{
			g_pGround_IndexBuffer->Release();
			g_pGround_IndexBuffer = NULL;
		}

		if (g_pGround_VertexBuffer)
		{
			g_pGround_VertexBuffer->Release();
			g_pGround_VertexBuffer = NULL;
		}
	}

	//Finalize_Sylinder
	void Final_Cylinder()
	{
		if (g_pCylinder_IndexBuffer)
		{
			g_pCylinder_IndexBuffer->Release();
			g_pCylinder_IndexBuffer = NULL;
		}

		if (g_pCylinder_VertexBuffer)
		{
			g_pCylinder_VertexBuffer->Release();
			g_pCylinder_VertexBuffer = NULL;
		}
	}

	//Finalize_SkyDome
	void Final_SkyDome()
	{
		if (g_pSkyDome_IndexBuffer)
		{
			g_pSkyDome_IndexBuffer->Release();
			g_pSkyDome_IndexBuffer = NULL;
		}

		if (g_pSkyDome_VertexBuffer)
		{
			g_pSkyDome_VertexBuffer->Release();
			g_pSkyDome_VertexBuffer = NULL;
		}
	}

	//------------------------------------
	//	終了処理
	//------------------------------------
	void Finalize()
	{
		Final_SkyDome();
		Final_Cylinder();
		Final_Ground();
	}
}