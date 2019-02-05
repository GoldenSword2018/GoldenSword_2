//
//	Game.cpp
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
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

#define _USE_MATH_DEFINES
#include<math.h>
#include<time.h>

#include"GameScene.h"
#include"ResultScene.h"

#include"Input.h"
#include"Fade.h"
#include"Billboard.h"
#include"system_timer.h"

//Class
#include"CGameObject.h"
#include"CCamera.h"
#include"Debug_font.h"
#include"CBullet.h"
#include"CGun.h"
#include"MeshField.h"
#include"CBurst.h"
#include"CTarget.h"
#include"Sprite.h"
#include"Lighting.h"

#include"Cube.h"
#include"CPlayer.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	関数
//===============================================

//===============================================
//	グローバル変数	global
//===============================================
static GameScene g_GameScene;
static double g_Time;
static CPlayer* Player;
static int g_MaxTarget;

static 	D3DXVECTOR3 StageWall[4] =
{
	{ 0.0f,				0.0f,	MF_WALL_WIDTH / 2 },
	{ MF_WALL_WIDTH / 2,	0.0f,	0.0f },
	{ 0.0f,				0.0f,	-MF_WALL_WIDTH / 2 },
	{ -MF_WALL_WIDTH / 2,	0.0f,	0.0f }
};

static const D3DXVECTOR3 GroundPos(0.0f, 0.0f, 0.0f);


//===============================================
//	関数定義
//===============================================

//===============================================
//	GameScene
//===============================================

//-------------------------------------
//	初期化
//-------------------------------------
void GameScene::Initialize()
{
	srand(time(NULL));
	g_Time = 0;

	Player = new CPlayer
	(
		new CTransform({ 0.0f,0.5f,0.0f }, { 0.1f,0.1f,0.1f }, {0.0f,0.0f,0.0f}),
		new CXModelMesh("human_Stand.x", "Human")
	);

	Player->Camera.Set_Main();

	CBullet::Initialize();
	CTarget::g_Initialize();

	g_MaxTarget = 50;
	for(int i = 0; i < g_MaxTarget; i++)
	{
		CTarget::Create({
			(float)( 50 - rand() % 100 ),
			(float)( 10 + rand() % 10  ),
			(float)( 50 - rand() % 100 )
		});
	}

	Fade_Triger(false, 100.0f, D3DCOLOR_RGBA(255, 255, 255, 255));

	g_Time = SystemTimer_GetAbsoluteTime();
	Cube_Initialize();
}

//-------------------------------------
//	前更新
//-------------------------------------
void GameScene::UpdateBegin()
{
	Player->Update();
	CBullet::Update();
	CTarget::g_Update();

	for(int i = 0; i <BULLET_NUM; i++)
	{
		if (!Get_BulletIsEnable(i)) continue;

		for(int j = 0; j < TARGET_NUM; j++)
		{
			if (!Get_TargetIsEnable(j)) continue;

			if(Collision::Judge(&Get_Bullet(i)->ColSphere, &Get_Target(j)->ColSphere))
			{
				Get_Bullet(i)->hit();
				Get_Target(j)->Hit();
			}
		}
	}

	if(Get_TargetNum() <= 0)
	{
		NSCENE::LoadScene(Get_ResultScene());
		Fade_Triger(true, 10, D3DCOLOR_RGBA(255, 255, 255, 255));
	}
}

//-------------------------------------
//	描画
//-------------------------------------
void GameScene::Render()
{
	NMeshField::Render_SkyDome(Player->transform->Get_Position(), NTexture::MeshCylinderTex);

	//wall
	NMeshField::Render_Wall(StageWall[0], { 1.0f,1.0f,1.0f }, { 0.0f, 0.0f,				0.0f }, NTexture::Mesh_Wall);
	NMeshField::Render_Wall(StageWall[1], { 1.0f,1.0f,1.0f }, { 0.0f, (float)(M_PI_2),	0.0f }, NTexture::Mesh_Wall);
	NMeshField::Render_Wall(StageWall[2], { 1.0f,1.0f,1.0f }, { 0.0f, (float)(M_PI),	0.0f }, NTexture::Mesh_Wall);
	NMeshField::Render_Wall(StageWall[3], { 1.0f,1.0f,1.0f }, { 0.0f, (float)(-M_PI_2),	0.0f }, NTexture::Mesh_Wall);

	NMeshField::Render_Ground(GroundPos, NTexture::MeshFieldTex);
	if (Get_TargetNum() > 0)
	{
		NRender2D::UI::CircleIndicator({ 120,500 }, D3DCOLOR_RGBA(255, 255, 255, 255), D3DCOLOR_RGBA(255, 0, 0, 255), 50, 20, g_MaxTarget - Get_TargetNum(), g_MaxTarget);
	}
	CTarget::g_Render();
	Player->Render();
	CBullet::Render();
	NRender2D::Sprite({ 120,500 }, { 100,50 }, D3DCOLOR_RGBA(255, 255, 255, 255), NTexture::Get_Texture(NTexture::TargetText));
	
	D3DXMATRIX World;
	D3DXMATRIX Trans;
	D3DXMATRIX Scale;
	D3DXMatrixTranslation(&Trans,0.0f,5.0f,0.0f);
	D3DXMatrixScaling(&Scale,1.0f,1.0f,1.0f);

	World = Scale * Trans;

	System_GetDevice()->SetTransform(D3DTS_WORLD, &World);
	System_GetDevice()->SetTexture(0,NTexture::Get_Texture(NTexture::NAME_NONE));
	Cube_Render();
}

//-------------------------------------
//	後更新
//-------------------------------------
void GameScene::UpdateEnd()
{

}

//-------------------------------------
//	終了処理
//-------------------------------------
void GameScene::Finalize()
{
	CBullet::Finalize();
	CTarget::g_Finalize();
	delete Player;
	g_Time = SystemTimer_GetAbsoluteTime() - g_Time;
	Cube_Finalize();
}

//-------------------------------------
//	Getter
//-------------------------------------
NSCENE::AScene* Get_GameScene()
{
	return &g_GameScene;
}

int Get_GameTime()
{
	return (int)g_Time;
}