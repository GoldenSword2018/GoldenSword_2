//
//	CPlayer.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CPLAYER_H
#define CPLAYER_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"

//Class
#include"CGameObject.h"

//================================================
//	�}�N����`	define
//================================================
#define SPEED_WALK (0.05f)
#define SPEED_RUN  (0.08f)

//================================================
//	�񋓌^		enum
//================================================


//================================================
//	�\����		struct/typedef
//================================================


//================================================
//	�O���[�o���ϐ��@global
//================================================


//================================================
//	�N���X		class
//================================================

#include"CCamera.h"
#include"CGun.h"

#include<d3dx9.h>

class CPlayer :public NRender3D::CGameObject
{
public:
	Camera Camera;
	CGun Gun;

public:
	float Aty;
	float Speed;
	bool bLean;		//[ true = �E / false = �� ]

public:
	CPlayer(CTransform* transform, AMesh* mesh);
	~CPlayer();

public:
	void Update();
	void Render();
};

void CameraBehavior(CPlayer* const player, D3DXVECTOR3 Distance);
void Set_GunRotate(CPlayer* const player);

#endif