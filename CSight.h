//
//	Sight.h
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef SIGHT_H
#define SIGHT_H

//================================================
//	�C���N���[�h	include
//================================================
#include"common.h"

#include"CGameObject.h"
#include"XModel.h"
//Class

//================================================
//	�}�N����`	define
//================================================


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
class CSight:NRender3D::CGameObject
{
//---�O���[�o��---------------------------------------
public:
	//�T�C�g�̎��
	typedef enum
	{
		NORMAL,
		OPTICAL,
		END
	}TYPE;
private:
	//�T�C�g�̃��f���f�[�^
	static NRender3D::CGameObject* Index[END];
public:
	static void InitLoad();
	static void FinalLoad();
	static CGameObject Get_SightObj(TYPE type);

//---���[�J��---------------------------------------
private:
	TYPE m_type;
public:
	CSight();
	~CSight();
public:
	void render() override;

public:
	void Set(CTransform* parent, D3DXVECTOR3 distance, TYPE type);
	void Set(TYPE type);
};

#endif