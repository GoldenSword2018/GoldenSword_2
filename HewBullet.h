// ===============================================================================================
// プロジェクト名: 
// ファイル名: HewBullet.h
// 作成日 XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// 追記:                                                                                        
// MM/DD/YYYY Author: ○○                                                                      
// ・××の変更～～～～                                                                         
// ===============================================================================================

#ifndef _HEWBULLET_H_
#define _HEWBULLET_H_
#pragma once

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// インクルードファイル
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//
// Windows系
// 
#include <vector>

// 
// 自作系
//
#include "Collider.h"
#include "CGameObject.h"
using namespace NRender3D;
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// 
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// --------------------------------------------------------------------------------------
//
// クラス: HewBullet
//
// --------------------------------------------------------------------------------------

class HewBullet : public CGameObject
{
public:
	HewBullet();
	HewBullet( CTransform* transform );
	~HewBullet();
public:
	float speed;
	ShapeSphere Collider;
public:
	void Update( void );
	void Render( void ); 
	void Finalize( void );
public: // 各イベント
	void Hit( void );
public:
	bool isDestroyed;

};

class HewBulletManager
{
private:
	HewBulletManager();
	static HewBulletManager* pInstance;
public:
	static HewBulletManager* GetInstance( void );
public:
	void Update( void );
	void Render( void );
	void Finalize( void );
private:
	std::vector<HewBullet*> ppHewBullet;
public:
	void CreateBullet( D3DXVECTOR3 pos, D3DXVECTOR3 at, float speed );
};

/* +++++++++++++++ 注記<大> +++++++++++++++ */
/* ----- 注記<中> -----*/
// 注記<小>

#endif // _HEWBULLET_H_