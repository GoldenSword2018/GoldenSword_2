//
//	Screwdrop.cpp
//		Author:�n��	DATE:2018/10/23
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------
#include "Screwdrop.h"
#include "CScrew.h"

#include"CRender.h"
#include"CMesh.h"

//===============================================
//	�}�N����`
//===============================================
#define SCREW_DROP_SPEED (0.01f)�@�@	//�����鎞�̑��x
#define SCREW_ROTATION_SPEED (0.01f)	//��]���̈ړ����x
#define ROTATION_FRAME_MAX (120)		//��]�t���[����

//===============================================
//	�\����
//===============================================

//===============================================
//	�O���[�o���ϐ�
//===============================================
Screwdrop g_Screwdrop[SCREW_NUM];
static CXModelName* Model;

//===============================================
//	�֐�
//===============================================

//-------------------------------------
//	������
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
//	�X�V
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
				if (g_Screwdrop[i].ScrewPosition.y >= 0.0f/*�n��*/)
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
//	�`��
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
//	����
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
//	�폜
//-------------------------------------
void Screwdrop_DisEnable(int index)
{
	g_Screwdrop[index].IsEnable = false;
}
