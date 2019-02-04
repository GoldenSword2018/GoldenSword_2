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

//===============================================
//	マクロ定義		define
//===============================================
#define SPEED_WALK (0.05f)
#define SPEED_RUN  (0.08f)

//===============================================
//	CPlayer
//===============================================
class CPlayer :public NRender3D::CGameObject
{
public:
	Camera Camera;
	CGun Gun;

public:
	float Aty;
	float Speed;
	bool bLean;		//[ true = 右 / false = 左 ]

public:
	CPlayer(CTransform* transform, AMesh* mesh);
	~CPlayer();

public:
	void Update();
	void Render();
};

//===============================================
//	関数
//===============================================
void CameraBehavior(CPlayer* const player, D3DXVECTOR3 Distance);
void Set_GunRotate(CPlayer* const player);

//===============================================
//	グローバル変数	global
//===============================================
static GameScene g_GameScene;
static double g_Time;
static CPlayer* Player;
static const D3DXVECTOR3 GroundPos(0.0f,0.0f,0.0f);
static const D3DXVECTOR3 GunPos(1.5f, 0.0f, 2.0f);
static int g_MaxTarget;

static 	D3DXVECTOR3 StageWall[4] =
{
	{ 0.0f,				0.0f,	MF_WALL_WIDTH / 2 },
	{ MF_WALL_WIDTH / 2,	0.0f,	0.0f },
	{ 0.0f,				0.0f,	-MF_WALL_WIDTH / 2 },
	{ -MF_WALL_WIDTH / 2,	0.0f,	0.0f }
};

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
}

//-------------------------------------
//	Getter
//-------------------------------------
NSCENE::AScene* Get_GameScene()
{
	return &g_GameScene;
}

//===============================================
//	CPlayer
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------

CPlayer::CPlayer(CTransform* transform, AMesh* mesh)
:
	Gun(
		new CTransform(GunPos, { 0.5f,0.5f,0.5f }, {0.0f,0.0f,0.0f}),
		{ 0.0f, 0.2f, 5.5f },
		10,
		10
		)
{
	this->Aty = 0.0f;
	this->Speed = SPEED_WALK;
	this->transform = transform;
	this->mesh = mesh;
	this->bLean = true;

	//Gunの設定
	this->Gun.transform->Set_Parent(this->transform);
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CPlayer::~CPlayer()
{
	delete this->transform;
	delete this->mesh;
}

//-------------------------------------
//	更新処理
//-------------------------------------
void CPlayer::Update()
{
	this->Gun.Update();

	//歩行切り替え
	if(Keyboard_IsPress(DIK_LSHIFT))
	{
		this->Speed = SPEED_RUN;
	}
	else
	{
		this->Speed = SPEED_WALK;
	}

	D3DXVECTOR3 Move(0.0f,0.0f,0.0f);

	//進行方向
	if (Keyboard_IsPress(DIK_W))
	{
		this->transform->LookAt(this->Camera.at);
		Move += this->transform->Get_Forward();
	}

	if (Keyboard_IsPress(DIK_A))
	{
		this->transform->LookAt(this->Camera.at);
		Move -= this->transform->Get_Right();
	}
	
	if (Keyboard_IsPress(DIK_S))
	{
		this->transform->LookAt(this->Camera.at);
		Move -= this->transform->Get_Forward();
	}

	if (Keyboard_IsPress(DIK_D))
	{
		this->transform->LookAt(this->Camera.at);
		Move += this->transform->Get_Right();
	}

	D3DXVec3Normalize(&Move, &Move);
	*this->transform->Position() += Move * this->Speed;

	//X軸
	if(this->transform->Get_Position().x + this->Speed> MF_WALL_WIDTH*0.5f )
	{
		this->transform->Position()->x -= this->Speed;
	}

	if (this->transform->Get_Position().x - this->Speed< -MF_WALL_WIDTH *0.5f)
	{
		this->transform->Position()->x += this->Speed;
	}

	//z軸
	if (this->transform->Get_Position().z + this->Speed > MF_WALL_WIDTH *0.5f)
	{
		this->transform->Position()->z -= this->Speed;
	}

	if (this->transform->Get_Position().z - this->Speed < -MF_WALL_WIDTH *0.5f)
	{
		this->transform->Position()->z += this->Speed;
	}

	//カメラ操作
	this->Camera.m_Rotation.y -= Mouse_IsAccelerationX() * 0.001f;
	this->Camera.m_Rotation.x += Mouse_IsAccelerationY() * 0.001f;
	this->Camera.m_Rotation.x = min(this->Camera.m_Rotation.x,1.2f);
	this->Camera.m_Rotation.x = max(this->Camera.m_Rotation.x,-1.0f);

	//Lean
	//左
	if(Keyboard_IsTrigger(DIK_Q))
	{
		this->bLean = false;
		this->Gun.transform->Position()->x = -GunPos.x;
	}

	//右
	if(Keyboard_IsTrigger(DIK_E))
	{
		this->bLean = true;
		this->Gun.transform->Position()->x = GunPos.x;
	}

	//ADS
	if (Mouse_IsLeftDown())
	{
		Set_GunRotate(this);

		this->transform->LookAt(this->Camera.at);
		CameraBehavior(this, { 0.75f,0.4f,-0.75f });

		//Lean　右
		if (this->bLean)
		{
			this->Camera.position += this->transform->Get_Position() + (this->Camera.Get_Right() * 0.5f);
			this->Camera.at = (this->Camera.Get_Forward()*10.0f) + this->transform->Get_Position() + (this->Camera.Get_Right() * 1.5f);
		}
		//Lean　左
		else
		{
			this->Camera.position += this->transform->Get_Position() + (this->Camera.Get_Right() * -0.5f);
			this->Camera.at = (this->Camera.Get_Forward()*10.0f) + this->transform->Get_Position() + (this->Camera.Get_Right() * -1.5f);
		}
	}
	else
	{
		CameraBehavior(this, { 2.0f, 0.8f, -2.0f });
		this->Camera.position += this->transform->Get_Position();
		this->Camera.at = (this->Camera.Get_Forward()*10.0f) + this->transform->Get_Position() + (this->Camera.Get_Right() * 1.5f);
	}

	//撃つ
	if(Mouse_IsRightDown())
	{
		Set_GunRotate(this);
		this->transform->LookAt(this->Camera.at);
		this->Gun.Burst(this->Camera.at, this->Camera.m_Rotation.x);
	}
	
}

//-------------------------------------
//	描画
//-------------------------------------
void CPlayer::Render()
{
	//描画
	NRender3D::Render(this->mesh, this->transform);
	//銃描画
	this->Gun.render();
	//影
	BillBoardShadow_Create(this->transform->Get_Position(),this->transform->Get_Scale() * 8.0f);
	//レティクル
	BillBoard_Create(this->Camera.at, {1.0f,1.0f,1.0f},NTexture::Get_Texture(NTexture::Reticle));
}

//===============================================
//	CameraBehavior カメラの動作
//===============================================
void CameraBehavior(CPlayer* const player, D3DXVECTOR3 Distance)
{
	float sinX = sinf(player->Camera.m_Rotation.x);
	float sinY = sinf(-player->Camera.m_Rotation.y);
	float cosY = cosf(-player->Camera.m_Rotation.y);

	player->Camera.position =
	{
		D3DXVECTOR3(
			sinY * ((sinX* sinX * -Distance.x) + Distance.x),
			(sinX * 1.0f) + Distance.y,
			cosY * ((sinX * sinX * -Distance.z) + Distance.z)
		)
	};
}

//銃の回転設定
void Set_GunRotate(CPlayer* const player)
{
	*player->Gun.transform->Rotation() = player->Camera.m_Rotation;
	player->Gun.transform->Rotation()->y = 0.0f;
}

int Get_GameTime()
{
	return (int)g_Time;
}