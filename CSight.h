//
//	Sight.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef SIGHT_H
#define SIGHT_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

#include"CGameObject.h"
#include"XModel.h"
//Class

//================================================
//	マクロ定義	define
//================================================


//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//================================================
//	クラス		class
//================================================
class CSight:NRender3D::CGameObject
{
//---グローバル---------------------------------------
public:
	//サイトの種類
	typedef enum
	{
		NORMAL,
		OPTICAL,
		END
	}TYPE;
private:
	//サイトのモデルデータ
	static NRender3D::CGameObject* Index[END];
public:
	static void InitLoad();
	static void FinalLoad();
	static CGameObject Get_SightObj(TYPE type);

//---ローカル---------------------------------------
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