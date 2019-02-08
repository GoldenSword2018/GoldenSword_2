//
//	CCoreObject.cpp	
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#include<d3dx9.h>
#include<vector>
#include"System.h"

//Class
#include"Cube.h"
#include"CCoreObject.h"
#include"CCollisionShape.h"
#include"XModel.h"
#include"CStageBlockManager.h"
#include"Cube.h"

#include "Debug_Collision.h"

#include"Input.h"

// �����蔻��o�^ ------------------------------------------------------------------------------------------------------------------- TMP!>


//===============================================
//	�O���[�o���ϐ�
//===============================================
static CXModelName ScrewModel(NModel::NAME_END);		// �l�W���f��


//===============================================
//	CoreObject	�N���X
//===============================================

//-------------------------------------
//	�R���X�g���N�^
//-------------------------------------
// �R���X�g���N�^�ł�Shape�n�N���X�̏�������CoreObject���g��transform�̃A�h���X��^���邱��. ������pTransform�̓R���X�g���N�^�I����,�j�������.
CoreObject::CoreObject(CTransform* pTransform, AMesh* pMesh, CORE_DISCHARGE_JUDGE_TYPE Type, CoreObject::CORE_DIRECTION face)
: 
	CGameObject(pTransform, pMesh),
	ColShape(pTransform, 1.0f)
{
	this->bHit = false;
	SetFace(face);
	this->direction = face;
	this->Type = Type;
	this->SetBlocks(0, 0, 0);
}

//-------------------------------------
//	�f�X�g���N�^
//-------------------------------------
CoreObject::~CoreObject()
{
	delete this->transform;
	delete this->mesh;
}

//-------------------------------------
//	�l�W�̌����ݒ�
//-------------------------------------
void CoreObject::SetFace(CORE_DIRECTION face)
{
	D3DXVECTOR3 Face;
	switch (face)
	{
	case CoreObject::CORE_DIRECTION_FORWARD:
		this->face = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		this->right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case CoreObject::CORE_DIRECTION_BEHIND:
		this->face = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		this->right = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case CoreObject::CORE_DIRECTION_UP:
		this->face = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		this->right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		this->up = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		break;
	case CoreObject::CORE_DIRECTION_DOWN:
		this->face = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		this->right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		this->up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		break;
	case CoreObject::CORE_DIRECTION_RIGHT:
		this->face = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		this->right = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case CoreObject::CORE_DIRECTION_LEFT:
		this->face = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		this->right = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case CoreObject::CORE_DIRECTION_MAX:
		break;
	default:
		break;
	}
}


//-------------------------------------
//	�e�ɓ�������
//-------------------------------------
void CoreObject::Hit()
{
	this->bHit = true;

	// �ێ����Ă�u���b�N�ɉ����ău���b�N�𐶐����Ĕ�΂�
	for (int i = 0; i < this->BlockWidth; i++)
	{
		for (int j = 0; j < this->BlockHeight; j++)
		{
			for (int k = 0; k < this->BlockDepth; k++)
			{
				// ��������u���b�N�̍��W
				D3DXVECTOR3 position = this->transform->Get_Position() + this->right * ((float)i - this->BlockWidth * 0.5f + 0.5f) + this->up * ((float)j - this->BlockHeight * 0.5f + 0.5f) + this->face * (k + 1.0f);
				// �u���b�N����
				StageBlockManager::GetInstance()->CreateBlock(new CTransform(position, D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)), RADIALLY, this->transform->Get_Position(), this->Type);
			}
		}
	}
	
	// �X�R�A���Z
}

//-------------------------------------
//	�X�V����
//-------------------------------------
void CoreObject::Update()
{
#ifdef _DEBUG
	if (Keyboard_IsTrigger(DIK_RETURN))
		Hit();
#endif
}

//-------------------------------------
//	�`��
//-------------------------------------
void CoreObject::Render()
{
	// �܂�������Ă��Ȃ�
	if (!this->bHit)
	{
		D3DXMATRIX mtxWorld;			// ���[���h�ϊ��s��
		D3DXMATRIX mtxTranslation;		// ���s�ړ��s��
		D3DXMATRIX mtxRotation;			// ��]�s��
		D3DXMATRIX mtxScaling;			// �g��k���s��
		
		D3DXMATRIX mtxTransform;		// 
		D3DXMATRIX mtxRotationY;		// 
		D3DXMATRIX mtxRotationAxis;		// 
		D3DXVECTOR3 vecFaceGroud;		// 
		D3DXVECTOR3 vecRight;			// 

		D3DXMatrixTranslation(&mtxTranslation, 0.0f, -0.5f, 0.0f);
		D3DXMatrixScaling(&mtxScaling, 0.5f, 0.5f, 0.5f);
		mtxTransform = mtxTranslation * mtxScaling;


		//===============================================================

		// ���s�ړ��s��
		D3DXMatrixTranslation(&mtxTranslation, this->transform->Get_Position().x, this->transform->Get_Position().y, this->transform->Get_Position().z);

		// ��]�s��
		switch (this->direction)
		{
		case CoreObject::CORE_DIRECTION_FORWARD:
			D3DXMatrixIdentity(&mtxRotation);
			break;
		case CoreObject::CORE_DIRECTION_BEHIND:
			D3DXMatrixRotationY(&mtxRotation, D3DX_PI);
			break;
		case CoreObject::CORE_DIRECTION_UP:
			D3DXMatrixRotationX(&mtxRotation, -D3DX_PI / 2);
			break;
		case CoreObject::CORE_DIRECTION_DOWN:
			D3DXMatrixRotationX(&mtxRotation, D3DX_PI / 2);
			break;
		case CoreObject::CORE_DIRECTION_RIGHT:
			D3DXMatrixRotationY(&mtxRotation, D3DX_PI / 2);
			break;
		case CoreObject::CORE_DIRECTION_LEFT:
			D3DXMatrixRotationY(&mtxRotation, -D3DX_PI / 2);
			break;
		case CoreObject::CORE_DIRECTION_MAX:
			break;
		default:
			break;
		}

		// �g��k���s��
		D3DXMatrixScaling(&mtxScaling, 1.0f, 1.0f, 1.0f);

		//����
		mtxWorld = mtxTransform * mtxRotation * mtxScaling * mtxTranslation;
		
		//�l�W�̕`��
		NRender3D::Render(mesh, &mtxWorld);

		//�����蔻��̕`��
		ColShape.DebugDraw();

		//����ڂĂ̕`��
		RenderBox();
	}
}

void CoreObject::RenderBox()
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	// ���_���X�g
	CubeVertex3D Vertex[]
		=
	{
		{ D3DXVECTOR3(-0.5f, 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // ��O��
		{ D3DXVECTOR3(0.5f , 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	D3DXVECTOR2((float)this->BlockWidth, 0.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	D3DXVECTOR2(0.0f, (float)this->BlockHeight) },
		{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	D3DXVECTOR2((float)this->BlockWidth, (float)this->BlockHeight) },

		{ D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // �E��
		{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DXVECTOR2((float)this->BlockDepth, 0.0f) },
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, (float)this->BlockHeight) },
		{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DXVECTOR2((float)this->BlockDepth, (float)this->BlockHeight) },

		{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // ����
		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DXVECTOR2((float)this->BlockWidth, 0.0f) },
		{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DXVECTOR2(0.0f, (float)this->BlockHeight) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DXVECTOR2((float)this->BlockWidth, (float)this->BlockHeight) },

		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // ����
		{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DXVECTOR2((float)this->BlockDepth, 0.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, (float)this->BlockHeight) },
		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DXVECTOR2((float)this->BlockDepth, (float)this->BlockHeight) },

		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // ���
		{ D3DXVECTOR3(0.5f , 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DXVECTOR2((float)this->BlockWidth, 0.0f) },
		{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DXVECTOR2(0.0f, (float)this->BlockDepth) },
		{ D3DXVECTOR3(0.5f , 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DXVECTOR2((float)this->BlockWidth, (float)this->BlockDepth) },

		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // ����
		{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DXVECTOR2((float)this->BlockWidth, 0.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DXVECTOR2(0.0f, (float)this->BlockDepth) },
		{ D3DXVECTOR3(0.5f , -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DXVECTOR2((float)this->BlockWidth, (float)this->BlockDepth) }
	};

	// ���_�C���f�b�N�X�̍쐬
	WORD Index[36];
	for (int i = 0; i < 6; i++)
	{
		Index[i * 6 + 0] = (WORD)i * 4 + 0;
		Index[i * 6 + 1] = (WORD)i * 4 + 1;
		Index[i * 6 + 2] = (WORD)i * 4 + 2;
		Index[i * 6 + 3] = (WORD)i * 4 + 1;
		Index[i * 6 + 4] = (WORD)i * 4 + 3;
		Index[i * 6 + 5] = (WORD)i * 4 + 2;
	}

	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxScaling;
	D3DXMATRIX mtxRotation;

	// �͂�ڂĒ��S���W
	D3DXVECTOR3 position = this->transform->Get_Position() + this->face * this->BlockDepth * 0.5f;
	D3DXMatrixTranslation(&mtxTranslation, position.x, position.y, position.z);

	// ��]�s��
	switch (this->direction)
	{
	case CoreObject::CORE_DIRECTION_FORWARD:
		D3DXMatrixIdentity(&mtxRotation);
		break;
	case CoreObject::CORE_DIRECTION_BEHIND:
		D3DXMatrixRotationY(&mtxRotation, D3DX_PI);
		break;
	case CoreObject::CORE_DIRECTION_UP:
		D3DXMatrixRotationX(&mtxRotation, -D3DX_PI / 2);
		break;
	case CoreObject::CORE_DIRECTION_DOWN:
		D3DXMatrixRotationX(&mtxRotation, D3DX_PI / 2);
		break;
	case CoreObject::CORE_DIRECTION_RIGHT:
		D3DXMatrixRotationY(&mtxRotation, D3DX_PI / 2);
		break;
	case CoreObject::CORE_DIRECTION_LEFT:
		D3DXMatrixRotationY(&mtxRotation, -D3DX_PI / 2);
		break;
	case CoreObject::CORE_DIRECTION_MAX:
		break;
	default:
		break;
	}

	// �g��k���s��
	D3DXMatrixScaling(&mtxScaling, this->BlockWidth, this->BlockHeight, this->BlockDepth);

	// �s��̍���
	mtxWorld = mtxScaling * mtxRotation * mtxTranslation;

	// �`��
	pDevice->SetFVF(FVF_CUBE_VERTEX3D);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->SetTexture(0, NTexture::Get_Texture(NTexture::CubeTexture));

	pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 24, 12, Index, D3DFMT_INDEX16, Vertex, sizeof(Vertex[0]));
}

//-------------------------------------
//	�l�W�̌����̎擾
//-------------------------------------
D3DXVECTOR3 CoreObject::GetFace()
{
	return this->face;
}

//-------------------------------------
//	����ݒ�
//-------------------------------------
void CoreObject::Set_JudgeType(CORE_DISCHARGE_JUDGE_TYPE Type)
{
	this->Type = Type;
}

//-------------------------------------
//	�u���b�N���ݒ�
//-------------------------------------
void CoreObject::SetBlocks(int x, int y, int z)
{
	this->BlockWidth = x;
	this->BlockHeight = y;
	this->BlockDepth = z;
	this->NumBlocks = x * y * z;
}
