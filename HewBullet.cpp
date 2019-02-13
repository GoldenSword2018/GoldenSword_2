// ===============================================================================================
// プロジェクト名: 
// ファイル名: HewBullet.cpp
// 概要: 
// 作成日 XX/XX/XXXX Author: Hashimoto Yuto AT12E-275-29                                       
// 追記:                                                                                        
// MM/DD/YYYY Author: ○○                                                                      
// ・××の変更～～～～                                                                         
// ===============================================================================================

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// インクルードファイル
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
#include "HewBullet.h"
//
// Windows系
// 

// 
// 自作系
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
// クラス: HewBullet
//
// --------------------------------------------------------------------------------------
//
// 静的メンバ
//
HewBulletManager* HewBulletManager::pInstance = nullptr;

//
// コンストラクタ
// 

HewBulletManager::HewBulletManager()
{

}

//
// インスタンスゲッター
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
// 更新
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
// 描画
//
void HewBulletManager::Render( void )
{
	for( int cb = 0; cb < ppHewBullet.size(); cb++ )
	{
		ppHewBullet.at( cb )->Render();
	}
}
//
// おしまい
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
// 弾の生成と登録
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
// クラス: HewBullet
//
// --------------------------------------------------------------------------------------
//
// コンストラクタ
// 

HewBullet::HewBullet()
	:
	HewBullet( new CTransform() )
{
	// 当たり判定は引数付きコンストラクタで登録済み！  // <-この文言かきたくないんだけどどうしたらいい
}

HewBullet::HewBullet( CTransform* _pTransform )
	:
	CGameObject( _pTransform, new CXModelName( NModel::BULLET ) ), // para1後で変更 Model
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
	//X軸
	if( MF_WALL_WIDTH * 0.5f < transform->Get_Position().x )
	{
		Finalize();
	}

	if( transform->Get_Position().x < -MF_WALL_WIDTH *0.5f )
	{
		Finalize();
	}

	//Y軸
	if( 1000.0f < transform->Get_Position().y ) // マジックナンバーやつ
	{
		Finalize();
	}

	if( transform->Get_Position().y < -10.0f )
	{
		Finalize();
	}

	//z軸
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
// イベント
//

void HewBullet::Hit( void )
{
	// CBurst* burst = new CBurst( this->transform->Get_Position(), { 1.0f,1.0f,1.0f }, true );
	Finalize();;
}

/* +++++++++++++++ 注記<大> +++++++++++++++ */
/* ----- 注記<中> -----*/
// 注記<小>

/* ----- 関数名 XXXXXXXXXXXXXXXXXXXX ------------------------------------------------- */
/* 概要 XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX  */
/* 戻り値: XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX　　　　　　　　　　　*/
/* arg0: Type VariableName 概要                                                        */
/* ----------------------------------------------------------------------------------- */

//ReturnType FunctionName( Type arg0... )
// {
//     /* ----- 処理開始 ----- */
//     int XXXXX = NULL// 概要
//     Func01() // 動作概要
//     a = Func02();
//         // 関数名
//         // 概要: XXXX
//         // 戻値: XXXXXX
//     Func03( arg0, // 型　引数名 概要
//             arg1, // 型　引数名 概要
//             arg2 );

// }