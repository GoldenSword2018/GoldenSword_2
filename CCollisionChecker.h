//
//	CCollisionChecker.h
//		Author:	Hashimoto Yuto DATE: 11/19/2018
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef _COLLISION_CHECKER_H_
#define _COLLISION_CHECKER_H_

//================================================
//	�C���N���[�h	include
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
//	�}�N����`	define
//================================================

#define COLLISION_BULLET_MAX    ( 1024 )
#define COLLISION_CORE_MAX      ( 1024 )
#define COLLISION_STAGEBLOCK_MAX	( 60000 )
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


//-------------------------------------
//	�N���X��
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
private: // �o�^�A�h���X vector�ł悢�ł� ------------------------------------------------------- CHANGE!>
	Player* pPlayer; // �����I�ɕ�����
	Bullet* pBulletCollection[ BULLET_MAX ];
	StageBlock* pStageBlock[ COLLISION_STAGEBLOCK_MAX ];	
	CoreObject* pCoreCollection[ COLLISION_CORE_MAX ];
public: // �o�^���� �ߒlbool����Ȃ��̂ł́H
	// �v���C���[
	bool RegisterCollision_Player( Player* pPlayer );
	bool DeregisterCollision_Player( Player* pPlayer );
	// �e
	bool RegisterCollision_Bullet( Bullet* pBullet );
	bool DeregisterCollision_Bullet( Bullet* pBullet );
	// �R�A
	bool RegisterCollision_CoreObject( CoreObject* pCore );
	bool DeregisterCollision_CoreObject( CoreObject* pCore );
	// �n�`
	bool RegisterCollision_StageBlock( StageBlock* pStageBlock );
	bool DeregisterCollision_StageBlock( StageBlock* pStageBlock );
private:
	void CheckBulletVsCoreObj( void );
	void CheckCollisionPlayerVsStageObj( void ); // �v���C���[ vs �n�` // ���O������
	// void CheckCollisionBulletVsStageObj( void );// �e vs �n�`

};
/*

*/
#endif