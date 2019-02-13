//
//	CGun.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CGUN_H
#define CGUN_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"

//Class
#include"CGameObject.h"

//�p�[�c
#include"CSight.h"

//================================================
//	�}�N����`	define
//================================================
#define GUN_SHAKE (20)			//�u��
#define GUN_SHAKE_VAR (1)		//�u���ω��l
#define GUN_SHAKE_MAG (0.1f)	//�u���{��

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

typedef class GunData_tag
{
public:
	NRender3D::CGameObject* Model;	//���f��

	//�A�^�b�`�����g�ʒu
	const D3DXVECTOR3 SightPos;			//�T�C�g�ʒu
	const D3DXVECTOR3 MuzzlePos;		//�}�Y���ʒu
	const D3DXVECTOR3 UnderBarrel;		//�A���_�[�o�����ʒu
	const D3DXVECTOR3 Magazine;			//�}�K�W���ʒu

	const float Rate;				//���[�g
	const float Recoil;				//���R�C��
	const int Max_BulletNum;		//�}�K�W�����e��

	const D3DXVECTOR3 Muzzle;		//�e���ʒu
	const D3DXVECTOR3 Grip;			//�O���b�v

public:
	GunData_tag(
		NRender3D::CGameObject* Model,
		D3DXVECTOR3 SightPos,
		D3DXVECTOR3 MuzzlePos,
		D3DXVECTOR3 UnderBarrel,
		D3DXVECTOR3 Magazine,
		float Rate,
		float Recoil,
		int BulletNum,
		D3DXVECTOR3 Muzzle,
		D3DXVECTOR3 Grip
	);

}GunData;

//-------------------------------------
//	CGun
//-------------------------------------
class CGun:public NRender3D::CGameObject
{
//---�O���[�o��---------------------------------------
public:
	//�e�̎��
	typedef enum
	{
		HANDGUN,
		END
	}TYPE;
	static GunData* Index[END];

//---�֐�---------------------------------------------
public:
	static void InitLoad();		//���f���ǂݍ���
	static void FinalUnLoad();	//���f���j��

//---���[�J��-----------------------------------------
private:
	CSight* m_Sight;			//�T�C�g
private:
	TYPE	m_type;				//�e�̎��
	float	m_Rate;				//���[�g
	float	m_Recoil;			//���R�C��
	int		m_Max_BulletNum;	//�}�K�W�����e��
	D3DXVECTOR3 m_Muzzle;		//�e���ʒu
private:
	float m_wait;				//���e�ҋ@
	int m_BulletNum;			//�e��

//---�֐�---------------------------------------------
public:
	//�R���X�g���N�^
	CGun(CTransform* transform,TYPE type);
	//�f�X�g���N�^
	~CGun();
public:
	void Update();
	void render() override;
	void Burst(D3DXVECTOR3 target, float x);	//����
public:
	D3DXVECTOR3 Get_Muzzle();	//�e���ʒu�擾
public:
	void Set(CSight::TYPE type);	//�T�C�g�ݒ�
	void Set(TYPE Type);		//�^�C�v�ݒ�
};

#endif