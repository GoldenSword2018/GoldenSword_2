//
//	CBullet.cpp
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
#include"CBullet.h"
#include<vector>
#define _USE_MATH_DEFINES
#include<math.h>

//class
#include"Texture.h"
#include"Animation.h"
#include"MeshField.h"
#include"Billboard.h"
#include"CBurst.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================
static CBullet Index[BULLET_NUM];
static NTexture::NameTexture AnimaBillboard(NTexture::Billboard_Burst, { 0.0f,0.0f }, {768.0f/6.0f,384.0f/3.0f});

//===============================================
//	クラス名		class
//===============================================
CBullet::CBullet()
:
	CGameObject(
		new CTransform({ 0.0f,0.0f,0.0f }, { 0.025f,0.025f,0.025f }, { 0.0f,0.0f,0.0f }),
		new CXModelName(NModel::BULLET)
	),
	animation(18,6,1),
	ColSphere(this->transform->Position(),0.5f)
{
	this->bEnable = false;
	this->frame = 0;
}

CBullet::~CBullet()
{
	
}

void CBullet::Initialize()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		Index[i].bEnable = false;
	}
}

void CBullet::Update()
{
	for(int i = 0; i < BULLET_NUM; i++)
	{
		if (Index[i].bEnable)
		{
			CBullet* bullet = &Index[i];
			*bullet->transform->Position() += bullet->transform->Get_Forward() * BULLET_SPEED;
			bullet->update();
			if(bullet->frame >= 100)
			{
				bullet->destroy();
				return;
			}

			bullet->frame++;
		}
	}
}

void CBullet::Render()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (Index[i].bEnable)
		{
			Index[i].render();
		}
	}
}

void CBullet::Finalize()
{
	for (int i = 0; i < BULLET_NUM; i++)
	{
		Index[i].bEnable = false;
	}
}

void CBullet::Create(D3DXVECTOR3 position,D3DXVECTOR3 at,float x)
{
	D3DXVECTOR3 vec;
	D3DXVECTOR3 vec1 = at - position;
	D3DXVec3Normalize(&vec1,&vec1);
	vec.x = x;
	vec.y = atan2f(vec1.x,vec1.z);
	vec.z = 0.0f;

	for (int i = 0; i < BULLET_NUM; i++)
	{
		if (!Index[i].bEnable)
		{
			CBurst* burst = new CBurst(position, { 0.2f,0.2f,0.2f }, false);
			CBullet* bullet = &Index[i];
			*bullet->transform->Position() = position;
			bullet->transform->Set_Rotation(vec);
			bullet->bEnable = true;
			bullet->frame = 0;
			bullet->animation.Createframe = NTexture::Get_Frame();
			return;
		}
	}
}

void CBullet::update()
{
	//X軸
	if (this->transform->Get_Position().x > MF_WALL_WIDTH*0.5f)
	{
		this->destroy();
	}

	if (this->transform->Get_Position().x < -MF_WALL_WIDTH *0.5f)
	{
		this->destroy();
	}

	//z軸
	if (this->transform->Get_Position().z  > MF_WALL_WIDTH *0.5f)
	{
		this->destroy();
	}

	if (this->transform->Get_Position().z < -MF_WALL_WIDTH *0.5f)
	{
		this->destroy();
	}

}

void CBullet::render()
{
	NRender3D::Render(this->mesh,this->transform);
}

void CBullet::destroy()
{
	this->bEnable = false;
}

void CBullet::hit()
{
	CBurst* burst = new CBurst(this->transform->Get_Position(), {1.0f,1.0f,1.0f},true);
	this->destroy();
}

CBullet* Get_Bullet(int num)
{
	return &Index[num];
}

bool Get_BulletIsEnable(int num)
{
	return Index[num].bEnable;
}