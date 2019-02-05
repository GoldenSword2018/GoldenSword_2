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
static float value = 0;

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
			if(bullet->frame >= 500)
			{
				bullet->destroy();
				return;
			}

			bullet->frame++;
		}
	}
	value += 0.1f;
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

	D3DXMATRIXA16 matPosition;
	D3DXMatrixTranslation(&matPosition, this->transform->Get_Position().x, this->transform->Get_Position().y, this->transform->Get_Position().z);

	D3DXMATRIX matRotationZ;
	D3DXMatrixRotationZ(&matRotationZ, value);

	D3DXMATRIX matRotationFace;
	D3DXVECTOR3 face = this->transform->Get_Forward();
	D3DXVECTOR3 X, Y, Z; //X:右 Z:前 Y:上
	D3DXVECTOR3 Faceup = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	Z = face;
	D3DXVec3Cross(&X, D3DXVec3Normalize(&Y, &Faceup), &Z);
	D3DXVec3Normalize(&X, &X);
	D3DXVec3Normalize(&Y, D3DXVec3Cross(&Y, &Z, &X));

	//回転行列を作る
	matRotationFace._11 = X.x; matRotationFace._12 = X.y; matRotationFace._13 = X.z; matRotationFace._14 = 0;
	matRotationFace._21 = Y.x; matRotationFace._22 = Y.y; matRotationFace._23 = Y.z; matRotationFace._24 = 0;
	matRotationFace._31 = Z.x; matRotationFace._32 = Z.y; matRotationFace._33 = Z.z; matRotationFace._34 = 0;
	matRotationFace._41 = 0.0f; matRotationFace._42 = 0.0f; matRotationFace._43 = 0.0f; matRotationFace._44 = 1.0f;

	D3DXMATRIX matSize;
	D3DXMatrixScaling(&matSize, 0.1f, 0.1f, 0.1f);

	this->mtxWorld = matSize * matRotationZ * matRotationFace * matPosition;
}

void CBullet::render()
{
	NRender3D::Render(this->mesh,&this->mtxWorld);
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