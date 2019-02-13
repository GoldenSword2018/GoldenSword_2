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

#include "CTimer.h"
// Hewでの追記箇所
#include"CollisionChecker.h"
#include"CStageBlock.h"
#include"CStageBlockManager.h"
#include"CCoreObject.h"
#include "Score.h"

#include"CPlayer.h"
#include"CGun.h"
#include "CGameUI.h"

//===============================================
//	関数
//===============================================


//===============================================
//	グローバル変数	global
//===============================================
static GameScene g_GameScene;
static double g_Time;
static CPlayer* Player;
static const D3DXVECTOR3 GroundPos(0.0f,0.0f,0.0f);
static int g_MaxTarget;

static 	D3DXVECTOR3 StageWall[4] =
{
	{ 0.0f,				0.0f,	MF_WALL_WIDTH / 2 },
	{ MF_WALL_WIDTH / 2,	0.0f,	0.0f },
	{ 0.0f,				0.0f,	-MF_WALL_WIDTH / 2 },
	{ -MF_WALL_WIDTH / 2,	0.0f,	0.0f }
};

// Hew
// static CoreObject* g_pScrew;
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
		new CXModelMesh("human_Stand.x", "Human"),
		new CGun(
			new CTransform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, {0.0f,0.0f,0.0f}),
			CGun::HANDGUN
		)
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

	// タイマー
	Timer::Reset();
	Timer::Start();
	Score_Initialize(); // スコアリセット！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！！
	Cube_Initialize();

	// Hew
	// ねじ生成
	CoreObjectManager::GetInstance()->CreateCore( D3DXVECTOR3( 10.0f, 5.0f, 0.0f ), 4, 4, 5 );
	CoreObjectManager::GetInstance()->CreateCore( D3DXVECTOR3( -10.0f, 5.0f, 0.0f ), 1, 1, 1 );
	CoreObjectManager::GetInstance()->CreateCore( D3DXVECTOR3( 0.0f, 5.0f, 0.0f ), 3, 3, 3 );
	Score_Initialize();
	// g_pScrew = new CoreObject( new CTransform( D3DXVECTOR3( 0, 5.0f, 10.0f ), D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 0, 0, 0 ) ), new CXModelMesh( "neji.x", "neji" ), CoreObject::CORE_JUDGE_TYPE_0, CoreObject::CORE_DIRECTION_FORWARD );
	// g_pScrew->SetBlocks( 4, 4, 5 );
}

//-------------------------------------
//	前更新
//-------------------------------------
void GameScene::UpdateBegin()
{
	Player->Update();
	CBullet::Update();
	CTarget::g_Update();

	// タイマーとシーン遷移
	Timer::Update( Get_ResultScene() );

	if( CoreObjectManager::GetInstance()->GetCurrentCoreExist() == 0 )
	{
		NSCENE::LoadScene( Get_ResultScene() );
		Fade_Triger( true, 10, D3DCOLOR_RGBA( 255, 255, 255, 255 ) );
	}

	CoreObjectManager::GetInstance()->UpdateCoreAll();
	StageBlockManager::GetInstance()->UpdateAll();
	CollisionChecker::Getinstance()->CheckCollision();
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

	NMeshField::Render_Ground(GroundPos, NTexture::MeshField_Ground);
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

	// Hew
	CoreObjectManager::GetInstance()->RenderCoreAll();
	StageBlockManager::GetInstance()->RenderAll();
	CollisionChecker::Getinstance()->CheckCollision();

	// 必ず最後にする
	GameUI::Render();
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
	g_Time = SystemTimer_GetAbsoluteTime() - g_Time;
	Cube_Finalize();

	//Hew
	StageBlock::Finalize();
	StageBlockManager::GetInstance()->Finalize();
	CoreObjectManager::GetInstance()->Finalize();
	delete Player;
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