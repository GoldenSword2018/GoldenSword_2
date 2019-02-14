//
//	CGun.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CGUN_H
#define CGUN_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include"CGameObject.h"

//パーツ
#include"CSight.h"

//================================================
//	マクロ定義	define
//================================================
#define GUN_SHAKE (20)			//ブレ
#define GUN_SHAKE_VAR (1)		//ブレ変化値
#define GUN_SHAKE_MAG (0.1f)	//ブレ倍率

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

typedef class GunData_tag
{
public:
	NRender3D::CGameObject* Model;	//モデル

	//アタッチメント位置
	const D3DXVECTOR3 SightPos;			//サイト位置
	const D3DXVECTOR3 MuzzlePos;		//マズル位置
	const D3DXVECTOR3 UnderBarrel;		//アンダーバレル位置
	const D3DXVECTOR3 Magazine;			//マガジン位置

	const float Rate;				//レート
	const float Recoil;				//リコイル
	const int Max_BulletNum;		//マガジン総弾数

	const D3DXVECTOR3 Muzzle;		//銃口位置
	const D3DXVECTOR3 Grip;			//グリップ

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
//---グローバル---------------------------------------
public:
	//銃の種類
	typedef enum
	{
		HANDGUN,
		END
	}TYPE;
	static GunData* Index[END];

//---関数---------------------------------------------
public:
	static void InitLoad();		//モデル読み込み
	static void FinalUnLoad();	//モデル破棄

//---ローカル-----------------------------------------
private:
	CSight* m_Sight;			//サイト
private:
	TYPE	m_type;				//銃の種類
	float	m_Rate;				//レート
	float	m_Recoil;			//リコイル
	int		m_Max_BulletNum;	//マガジン総弾数
	D3DXVECTOR3 m_Muzzle;		//弾口位置
private:
	float m_wait;				//次弾待機
	int m_BulletNum;			//弾数

//---関数---------------------------------------------
public:
	//コンストラクタ
	CGun(CTransform* transform,TYPE type);
	//デストラクタ
	~CGun();
public:
	void Update();
	void render() override;
	void Burst(D3DXVECTOR3 target, float x);	//撃つ
public:
	D3DXVECTOR3 Get_Muzzle();	//銃口位置取得
public:
	void Set(CSight::TYPE type);	//サイト設定
	void Set(TYPE Type);		//タイプ設定
};

#endif