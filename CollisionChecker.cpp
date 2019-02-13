// ===============================================================================================
// �v���W�F�N�g��: 
// �t�@�C����: CollisionChecker.cpp
// �T�v: 
// �쐬�� XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// �ǋL:                                                                                        
// MM/DD/YYYY Author: ����                                                                      
// �E�~�~�̕ύX�`�`�`�`                                                                         
// ===============================================================================================

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// �C���N���[�h�t�@�C��
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#include "CollisionChecker.h"
//
// Windows�n
// 
#include <list>
#include <d3dx9.h>

// 
// ����n
//

#include "Collider.h"
#include "CGameObject.h"
#include"CBullet.h"

using namespace NRender3D;
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// �}�N����`
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// �N���X: CollisionChecker
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

// --------------------------------------------------------------------------------------
//
// �N���X: CollisionChecker
// 
// --------------------------------------------------------------------------------------
CollisionChecker* CollisionChecker::pInstance = nullptr;

//
// �R���X�g���N�^
//

CollisionChecker::CollisionChecker()
{

}

// 
// �f�X�g���N�^
// 
CollisionChecker::~CollisionChecker()
{
	pProjectile.clear();
	pCore.clear();
}

// 
// �Q�b�^�[
//
CollisionChecker* CollisionChecker::Getinstance()
{
	if( pInstance == nullptr )
	{
		pInstance = new CollisionChecker();
	}

	return pInstance;
}

// 
// �o�^�֐�
//
void CollisionChecker::Register( CBullet* _pProjectile )
{
	pProjectile.push_back( nullptr );
	pProjectile.back() = _pProjectile;
}

void CollisionChecker::Register( CoreObject* pTmp)
{
	pCore.push_back( nullptr );
	pCore.back() = pTmp;
}

void CollisionChecker::Deregister( CBullet* _pProjectile )
{
	auto itrProj = pProjectile.begin();

	while( itrProj != pProjectile.end() )
	{
		if( ( *itrProj ) == _pProjectile )
		{
			pProjectile.erase( itrProj );
			return;
		}
		itrProj++;
	}
}

void CollisionChecker::Deregister( CoreObject* _pCoreObj )
{
	auto itrCore = pCore.begin();

	while( itrCore != pCore.end() )
	{
		if( ( *itrCore ) == _pCoreObj )
		{
			pCore.erase( itrCore );
			return;
		}
		itrCore++;
	}

}

//
// �Փ˔��肷�邼
//
void CollisionChecker::CheckCollision( void )
{

	for( auto itrCore = pCore.begin(); itrCore != pCore.end();  )
	{
		for( auto itrProj = pProjectile.begin(); itrProj != pProjectile.end();  )
		{
			if( CollisionCheckHelper::SphereVsSphere( ( *itrProj )->Collider, ( *itrCore )->ColShape ) )
			{
				( *itrProj )->hit();
				( *itrCore )->Hit();
				itrProj = pProjectile.erase( itrProj );
				itrCore = pCore.erase( itrCore );
				break;
			}
			else
			{
				itrProj++;
			}
		}
		if( itrCore != pCore.end() )
		{
			itrCore++;
		}
		
	}
}

//
// �����܂�
//
void CollisionChecker::Finalize( void )
{
	pProjectile.clear();
	pCore.clear();
}
/* +++++++++++++++ ���L<��> +++++++++++++++ */
/* ----- ���L<��> -----*/
// ���L<��>

/* ----- �֐��� XXXXXXXXXXXXXXXXXXXX ------------------------------------------------- */
/* �T�v XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  */
/* �߂�l: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX�@�@�@�@�@�@�@�@�@�@�@*/
/* arg0: Type VariableName �T�v                                                        */
/* ----------------------------------------------------------------------------------- */

//ReturnType FunctionName( Type arg0... )
// {
//     /* ----- �����J�n ----- */
//     int XXXXX = NULL// �T�v
//     Func01() // ����T�v
//     a = Func02();
//         // �֐���
//         // �T�v: XXXX
//         // �ߒl: XXXXXX
//     Func03( arg0, // �^�@������ �T�v
//             arg1, // �^�@������ �T�v
//             arg2 );

// }