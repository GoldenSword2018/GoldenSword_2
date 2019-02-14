// ===============================================================================================
// �v���W�F�N�g��: 
// �t�@�C����: HewBullet.cpp
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
#include "HewBullet.h"
//
// Windows�n
// 

// 
// ����n
//
#include "CGameObject.h"
#include "CollisionChecker.h"
#include "CBurst.h"
#include "MeshField.h"
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
//
// �ÓI�����o
//
HewBulletManager* HewBulletManager::pInstance = nullptr;

//
// �R���X�g���N�^
// 

HewBulletManager::HewBulletManager()
{

}

//
// �C���X�^���X�Q�b�^�[
//
HewBulletManager* HewBulletManager::GetInstance( void )
{
	if( pInstance == nullptr )
	{
		pInstance = new HewBulletManager();
	}

	return pInstance;
}

// 
// �X�V
//
void HewBulletManager::Update( void )
{
	for( auto cb = ppHewBullet.begin(); cb != ppHewBullet.end(); cb++ )
	{
		( *cb )->Update();
	}

	for( int cb = 0; cb < ppHewBullet.size(); cb++ )
	{
		if( ppHewBullet.at( cb )->isDestroyed == true )
		{
			delete ppHewBullet.at( cb );
			ppHewBullet.erase( ppHewBullet.begin() + cb );
		}
	}
}

//
// �`��
//
void HewBulletManager::Render( void )
{
	for( int cb = 0; cb < ppHewBullet.size(); cb++ )
	{
		ppHewBullet.at( cb )->Render();
	}
}
//
// �����܂�
//
void HewBulletManager::Finalize( void )
{
	int i = 0;
	for( auto cb = ppHewBullet.begin(); cb != ppHewBullet.end(); cb++ )
	{
		delete ( *cb );
	}
	ppHewBullet.clear();
}
// 
// �e�̐����Ɠo�^
// 
void HewBulletManager::CreateBullet( D3DXVECTOR3 _Pos, D3DXVECTOR3 _At, float _X )
{
	D3DXVECTOR3 vec;
	D3DXVECTOR3 vec1 = _At - _Pos;
	D3DXVec3Normalize( &vec1, &vec1 );
	vec.x = _X;
	vec.y = atan2f( vec1.x, vec1.z );
	vec.z = 0.0f;

	ppHewBullet.emplace_back( new HewBullet( new CTransform( _Pos, D3DXVECTOR3( 0.025f, 0.025f, 0.025f ), vec ) ) );
	ppHewBullet.back()->speed = 1.0f;

}
// --------------------------------------------------------------------------------------
//
// �N���X: HewBullet
//
// --------------------------------------------------------------------------------------
//
// �R���X�g���N�^
// 

HewBullet::HewBullet()
	:
	HewBullet( new CTransform() )
{
	// �����蔻��͈����t���R���X�g���N�^�œo�^�ς݁I  // <-���̕������������Ȃ��񂾂��ǂǂ������炢��
}

HewBullet::HewBullet( CTransform* _pTransform )
	:
	CGameObject( _pTransform, new CXModelName( NModel::BULLET ) ), // para1��ŕύX Model
	Collider( transform, 1.0f ),
	isDestroyed( false )
{
	CollisionChecker::Getinstance()->Register(this);
}

HewBullet::~HewBullet()
{
	CollisionChecker::Getinstance()->Deregister(this);
}

// 
// 
//
void HewBullet::Update()
{
	transform->Set_Position( transform->Get_Position() + transform->Get_Forward() * speed );
	//X��
	if( MF_WALL_WIDTH * 0.5f < transform->Get_Position().x )
	{
		Finalize();
	}

	if( transform->Get_Position().x < -MF_WALL_WIDTH *0.5f )
	{
		Finalize();
	}

	//Y��
	if( 1000.0f < transform->Get_Position().y ) // �}�W�b�N�i���o�[���
	{
		Finalize();
	}

	if( transform->Get_Position().y < -10.0f )
	{
		Finalize();
	}

	//z��
	if( MF_WALL_WIDTH * 0.5f < transform->Get_Position().z  )
	{
		Finalize();
	}

	if( transform->Get_Position().z < -MF_WALL_WIDTH * 0.5f )
	{
		Finalize();
	}
}

void HewBullet::Render( void )
{
	NRender3D::Render( this->mesh, this->transform );
}

void HewBullet::Finalize( void )
{
	// isDestroyed = true;
}
//
// �C�x���g
//

void HewBullet::Hit( void )
{
	// CBurst* burst = new CBurst( this->transform->Get_Position(), { 1.0f,1.0f,1.0f }, true );
	Finalize();;
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