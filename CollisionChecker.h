// ===============================================================================================
// �v���W�F�N�g��: 
// �t�@�C����: CollisionChecker.h
// �쐬�� XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// �ǋL:                                                                                        
// MM/DD/YYYY Author: ����                                                                      
// �E�~�~�̕ύX�`�`�`�`                                                                         
// ===============================================================================================

#ifndef _COLLISION_CHECKER_H_
#define _COLLISION_CHECKER_H_
#pragma once

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// �C���N���[�h�t�@�C��
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//
// Windows�n
// 
#include <list>
#include <d3dx9.h>
// 
// ����n
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
/* +++++++++++++++ ���L<��> +++++++++++++++ */
/* ----- ���L<��> -----*/
// ���L<��>

#endif // _COLLISION_CHECKER_H_