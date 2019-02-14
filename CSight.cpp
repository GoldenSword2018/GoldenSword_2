//
//	Sight.cpp
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

#include"CSight.h"
using namespace NRender3D;
//class

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	���[�h��`
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================

//Index
//@ transform : CSight����̈ړ��� ���f���̒��S�Y���������ړI
//@ mesh		 : Model�f�[�^
CGameObject* CSight::Index[CSight::END];

//===============================================
//	�N���X��		class
//===============================================
void CSight::InitLoad()
{
	Index[NORMAL] = new CGameObject(
		new CTransform({ 0.0f,0.0f,0.0f }, { 0.7f,0.7f,0.7f }, { 0.0f,0.0f,0.0f }),
		new CXModelMesh("sight.x", "Sight")
	);

	Index[OPTICAL] = new CGameObject(
		new CTransform({ 0.0f,0.0f,0.0f }, { 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }),
		new CXModelMesh("sight2.x", "Sight")
	);
}

void CSight::FinalLoad()
{
	for (int i = 0; i < CSight::END; i++)
	{
		delete Index[i];
	}
}


CGameObject CSight::Get_SightObj(TYPE type)
{
	return *Index[type];
}


//-------------------------------------
//	�����o�֐���
//-------------------------------------
CSight::CSight()
:
	CGameObject(
		new CTransform(),
		NULL
	)
{

}



CSight::~CSight()
{

}

//�e,����,�T�C�g���
void CSight::Set(CTransform* parent,D3DXVECTOR3 distance,TYPE type)
{
	this->m_type = type;
	*this->transform = *Index[type]->transform;
	this->transform->Set_Parent(parent);

	D3DXVECTOR3 vec1 = distance;
	D3DXVECTOR3 vec2 = *Index[type]->transform->Position();

	vec1.x += vec2.x;
	vec1.y += vec2.y;
	vec1.z += vec2.z;

	this->transform->Set_Position(vec1);
}

void CSight::Set(TYPE type)
{
	this->m_type = type;
}

void CSight::render()
{
	D3DXMATRIX MtxWorld;
	MtxWorld = Index[m_type]->transform->Get_MtxWorld() * this->transform->Get_MtxWorld();

	NRender3D::Render(Index[m_type]->mesh,&MtxWorld);
}