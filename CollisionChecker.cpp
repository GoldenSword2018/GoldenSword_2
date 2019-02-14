// ===============================================================================================
// プロジェクト名: 
// ファイル名: CollisionChecker.cpp
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
#include "CollisionChecker.h"
//
// Windows系
// 
#include <list>
#include <d3dx9.h>

// 
// 自作系
//

#include "Collider.h"
#include "CGameObject.h"
#include"CBullet.h"

using namespace NRender3D;
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// マクロ定義
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// クラス: CollisionChecker
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-

// --------------------------------------------------------------------------------------
//
// クラス: CollisionChecker
// 
// --------------------------------------------------------------------------------------
CollisionChecker* CollisionChecker::pInstance = nullptr;

//
// コンストラクタ
//

CollisionChecker::CollisionChecker()
{

}

// 
// デストラクタ
// 
CollisionChecker::~CollisionChecker()
{
	pProjectile.clear();
	pCore.clear();
}

// 
// ゲッター
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
// 登録関数
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
// 衝突判定するぞ
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
// おしまい
//
void CollisionChecker::Finalize( void )
{
	pProjectile.clear();
	pCore.clear();
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