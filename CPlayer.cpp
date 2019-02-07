//
//	CPlayer.cpp
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include"CPlayer.h"

//class
#include"Input.h"
#include"Billboard.h"
#include"MeshField.h"

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================
static const D3DXVECTOR3 GunPos(1.5f, 0.0f, 2.0f);

//===============================================
//	�N���X��		class
//===============================================

//===============================================
//	CPlayer
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------

CPlayer::CPlayer(CTransform* transform, AMesh* mesh)
	:
	Gun(
		new CTransform(GunPos, { 0.5f,0.5f,0.5f }, { 0.0f,0.0f,0.0f }),
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

	//Gun�̐ݒ�
	this->Gun.transform->Set_Parent(this->transform);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
CPlayer::~CPlayer()
{

}

//-------------------------------------
//	�X�V����
//-------------------------------------
void CPlayer::Update()
{
	this->Gun.Update();

	//���s�؂�ւ�
	if (Keyboard_IsPress(DIK_LSHIFT))
	{
		this->Speed = SPEED_RUN;
	}
	else
	{
		this->Speed = SPEED_WALK;
	}

	D3DXVECTOR3 Move(0.0f, 0.0f, 0.0f);

	//�i�s����
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

	//X��
	if (this->transform->Get_Position().x + this->Speed> MF_WALL_WIDTH*0.5f)
	{
		this->transform->Position()->x -= this->Speed;
	}

	if (this->transform->Get_Position().x - this->Speed< -MF_WALL_WIDTH *0.5f)
	{
		this->transform->Position()->x += this->Speed;
	}

	//z��
	if (this->transform->Get_Position().z + this->Speed > MF_WALL_WIDTH *0.5f)
	{
		this->transform->Position()->z -= this->Speed;
	}

	if (this->transform->Get_Position().z - this->Speed < -MF_WALL_WIDTH *0.5f)
	{
		this->transform->Position()->z += this->Speed;
	}

	//�J��������
	this->Camera.m_Rotation.y -= Mouse_IsAccelerationX() * 0.001f;
	this->Camera.m_Rotation.x += Mouse_IsAccelerationY() * 0.001f;
	this->Camera.m_Rotation.x = min(this->Camera.m_Rotation.x, 1.2f);
	this->Camera.m_Rotation.x = max(this->Camera.m_Rotation.x, -1.0f);

	//Lean
	//��
	if (Keyboard_IsTrigger(DIK_Q))
	{
		this->bLean = false;
		this->Gun.transform->Position()->x = -GunPos.x;
	}

	//�E
	if (Keyboard_IsTrigger(DIK_E))
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

		//Lean�@�E
		if (this->bLean)
		{
			this->Camera.position += this->transform->Get_Position() + (this->Camera.Get_Right() * 0.5f);
			this->Camera.at = (this->Camera.Get_Forward()*10.0f) + this->transform->Get_Position() + (this->Camera.Get_Right() * 1.5f);
		}
		//Lean�@��
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

	//����
	if (Mouse_IsRightDown())
	{
		Set_GunRotate(this);
		this->transform->LookAt(this->Camera.at);
		this->Gun.Burst(this->Camera.at, this->Camera.m_Rotation.x);
	}

}

//-------------------------------------
//	�`��
//-------------------------------------
void CPlayer::Render()
{
	//�`��
	NRender3D::Render(this->mesh, this->transform);
	//�e�`��
	this->Gun.render();
	//�e
	BillBoardShadow_Create(this->transform->Get_Position(), this->transform->Get_Scale() * 8.0f);
	//���e�B�N��
	BillBoard_Create(this->Camera.at, { 1.0f,1.0f,1.0f }, NTexture::Get_Texture(NTexture::Reticle));
}

//===============================================
//	CameraBehavior �J�����̓���
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

//�e�̉�]�ݒ�
void Set_GunRotate(CPlayer* const player)
{
	*player->Gun.transform->Rotation() = player->Camera.m_Rotation;
	player->Gun.transform->Rotation()->y = 0.0f;
}