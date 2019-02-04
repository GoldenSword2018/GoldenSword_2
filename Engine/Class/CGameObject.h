//
//	GameObject.h
//		Author:HIROMASA IKEDA	DATE:2018/09/30
//===============================================
#pragma once
#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include<d3dx9.h>
#include<vector>

//Class
#include"CTransform.h"
#include"CRender.h"

#include"XModel.h"

namespace NRender3D
{
	class CGameObject
	{
	public:
		CTransform* transform;
		AMesh* mesh;
	public:
		CGameObject();
		CGameObject(CTransform* transform,AMesh* mesh);
		~CGameObject();
	};
}


/*
//===============================================
//	GameObject　クラス
//===============================================
class GameObject
{
private:
	static std::vector<GameObject*> pIndex;

public:
	static void g_Update();	//全体更新
	static void g_Render();	//全体描画

public:
	Transform transform;	//位置
	Render3D render;		//描画

public:
	GameObject(Transform* pTransform);
	~GameObject();

public:
	void Set_Parent(GameObject* pParent);	//親を設定

public:
	virtual void Update();
	virtual void Render();

};

class CGameObject
{
public:
	//メンバ変数
	CTransform transform;

public:
	//インストラクタ
	CGameObject();
	//コンストラクタ
	~CGameObject();
	 
public:
	//基本関数
	virtual void Initialize();
	virtual void UpdateBegin();
	virtual void Render();
	virtual void UpdateEnd();
	virtual void Finalize();

public:

};
*/

#endif // !GAMEOBJECT_H


