// ===============================================================================================
// �v���W�F�N�g��: 
// �t�@�C����: HewBullet.h
// �쐬�� XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// �ǋL:                                                                                        
// MM/DD/YYYY Author: ����                                                                      
// �E�~�~�̕ύX�`�`�`�`                                                                         
// ===============================================================================================

#ifndef _HEWBULLET_H_
#define _HEWBULLET_H_
#pragma once

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// �C���N���[�h�t�@�C��
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

//
// Windows�n
// 
#include <vector>

// 
// ����n
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
// �N���X: HewBullet
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
public: // �e�C�x���g
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

/* +++++++++++++++ ���L<��> +++++++++++++++ */
/* ----- ���L<��> -----*/
// ���L<��>

#endif // _HEWBULLET_H_