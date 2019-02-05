//
//	CCollisionChecker.h
//		Author:	Hashimoto Yuto DATE: 11/19/2018
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef _COLLISION_CHECKER_H_
#define _COLLISION_CHECKER_H_

//================================================
//	インクルード	include
//================================================
#include"common.h"

#include <vector>
using namespace std;

//Class
class ShapeSphere;
class ShapeOBB;
class Player;
class Bullet;
class CoreObject;
class StageBlock;
//================================================
//	マクロ定義	define
//================================================

#define COLLISION_BULLET_MAX    ( 1024 )
#define COLLISION_CORE_MAX      ( 1024 )
#define COLLISION_STAGEBLOCK_MAX	( 60000 )
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


//-------------------------------------
//	クラス名
//-------------------------------------
class TmpCollisionChecker
{
	// ---- public -------------------------------------
public:
	static TmpCollisionChecker* GetInstance( void );
public:
	void CheckCollision( void );
	// -------------------------------------------------
private:
	TmpCollisionChecker();
	TmpCollisionChecker( const TmpCollisionChecker& ) {};
private:
	static TmpCollisionChecker* pInstance;
private: // 登録アドレス vectorでよいです ------------------------------------------------------- CHANGE!>
	Player* pPlayer; // 将来的に複数化
	Bullet* pBulletCollection[ BULLET_MAX ];
	StageBlock* pStageBlock[ COLLISION_STAGEBLOCK_MAX ];	
	CoreObject* pCoreCollection[ COLLISION_CORE_MAX ];
public: // 登録処理 戻値boolいらないのでは？
	// プレイヤー
	bool RegisterCollision_Player( Player* pPlayer );
	bool DeregisterCollision_Player( Player* pPlayer );
	// 弾
	bool RegisterCollision_Bullet( Bullet* pBullet );
	bool DeregisterCollision_Bullet( Bullet* pBullet );
	// コア
	bool RegisterCollision_CoreObject( CoreObject* pCore );
	bool DeregisterCollision_CoreObject( CoreObject* pCore );
	// 地形
	bool RegisterCollision_StageBlock( StageBlock* pStageBlock );
	bool DeregisterCollision_StageBlock( StageBlock* pStageBlock );
private:
	void CheckBulletVsCoreObj( void );
	void CheckCollisionPlayerVsStageObj( void ); // プレイヤー vs 地形 // 名前が微妙
	// void CheckCollisionBulletVsStageObj( void );// 弾 vs 地形

};
/*

*/
#endif