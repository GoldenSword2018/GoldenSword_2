// ===============================================================================================
// プロジェクト名: 
// ファイル名: CollisionChecker.h
// 作成日 XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// 追記:                                                                                        
// MM/DD/YYYY Author: ○○                                                                      
// ・××の変更～～～～                                                                         
// ===============================================================================================

#ifndef _COLLISION_CHECKER_H_
#define _COLLISION_CHECKER_H_
#pragma once

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// インクルードファイル
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//
// Windows系
// 
#include <list>
#include <d3dx9.h>
// 
// 自作系
//
#include "Collider.h"
#include"CBullet.h"
#include "CCoreObject.h"
using namespace NRender3D;
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// 
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
class CollisionChecker
{
private:
	CollisionChecker();
	~CollisionChecker();
	static CollisionChecker* pInstance;
public:
	static CollisionChecker* Getinstance();
private:
	std::list<CBullet*> pProjectile;
	std::list<CoreObject*> pCore;
public:
	void Register( CBullet* pProjectile );
	void Register( CoreObject* pTmp );
	void Deregister( CBullet* pProjectile );
	void Deregister( CoreObject* pCoreObj );
public:
	void CheckCollision( void );
	void Finalize( void );
};
/* +++++++++++++++ 注記<大> +++++++++++++++ */
/* ----- 注記<中> -----*/
// 注記<小>

#endif // _COLLISION_CHECKER_H_