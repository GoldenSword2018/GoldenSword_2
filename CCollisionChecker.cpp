//
//	CCollisionChecker.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

//class
#include "CCollisionChecker.h"
#include "CCollisionShape.h"

//===============================================
//	マクロ定義		define
//===============================================
void Collision_PushBack(ShapeOBB *pShapeMovable, ShapeOBB *pShapeStable);


//===============================================
//	グローバル変数	global
//===============================================


//===============================================
//	Tmp Collision Collection
//===============================================

TmpCollisionChecker* TmpCollisionChecker::pInstance = NULL;		//インスタンス

//-------------------------------------
//	GetInstance
//-------------------------------------
TmpCollisionChecker* TmpCollisionChecker::GetInstance( void )
{
	if( !pInstance )
	{
		pInstance = new TmpCollisionChecker();
	}

	return pInstance;
}

TmpCollisionChecker::TmpCollisionChecker()
{
	// NULL初期化
	pPlayer = NULL;

	for( int bi = 0; bi < BULLET_MAX; bi++ )
	{
		pBulletCollection[ bi ] = NULL;
	}

	for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
	{
		pCoreCollection[ ci ] = NULL;
	}
	
	for( int si = 0; si < COLLISION_STAGEBLOCK_MAX; si++ )
	{
		pStageBlock[ si ] = NULL;
	}
}

//-------------------------------------
//	RegisterCollision_Player プレイヤリストに登録
//-------------------------------------
bool TmpCollisionChecker::RegisterCollision_Player( Player* Collision )
{
	if( !pPlayer )
	{
		pPlayer = Collision;
	}
	return false;
}

//-------------------------------------
//	DeregisterCollision_Player プレイヤリストから解除
//-------------------------------------
bool TmpCollisionChecker::DeregisterCollision_Player( Player* Collision )
{
	if( pPlayer )
	{
		pPlayer = NULL;
	}
	return false;
}

//-------------------------------------
//	RegisterCollision_Bullet 弾リストに登録
//-------------------------------------
bool TmpCollisionChecker::RegisterCollision_Bullet( Bullet* Collision )
{
	for( int bi = 0; bi < BULLET_MAX; bi++ )
	{
		if( pBulletCollection[ bi ] == NULL )
		{
			pBulletCollection[ bi ] = Collision;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	DeregisterCollison_Bullet 弾リストから解除
//-------------------------------------
bool TmpCollisionChecker::DeregisterCollision_Bullet( Bullet* Collision )
{
	for( int bi = 0; bi < BULLET_MAX; bi++ )
	{
		if( pBulletCollection[ bi ] == Collision )
		{
			pBulletCollection[ bi ] = NULL;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	RegisterCollision_CoreObject コアリストに登録
//-------------------------------------
bool TmpCollisionChecker::RegisterCollision_CoreObject( CoreObject* Collision )
{
	for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
	{
		if( pCoreCollection[ ci ] == NULL )
		{
			pCoreCollection[ ci ] = Collision;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	DeregisterCollision_CoreObject コアリストから解除
//-------------------------------------
bool TmpCollisionChecker::DeregisterCollision_CoreObject( CoreObject* Collision )
{
	for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
	{
		if( pCoreCollection[ ci ] == Collision )
		{
			pCoreCollection[ ci ] = NULL;
			return true;
		}
	}
	return false;
}


//-------------------------------------
//	RegisterCollision_StageBlock 地形リストから解除
//-------------------------------------
bool TmpCollisionChecker::RegisterCollision_StageBlock( StageBlock* pNewStageBlock )
{
	for( int si = 0; si < COLLISION_STAGEBLOCK_MAX; si++ )
	{
		if( pStageBlock[ si ] == NULL )
		{
			pStageBlock[ si ] = pNewStageBlock;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	DeregisterCollision_StageBlock 地形リストから解除
//-------------------------------------
bool TmpCollisionChecker::DeregisterCollision_StageBlock( StageBlock* pNewStageBlock )
{
	for( int si = 0; si < COLLISION_STAGEBLOCK_MAX; si++ )
	{
		if( pStageBlock[ si ] == pNewStageBlock )
		{
			pStageBlock[ si ] = NULL;
			return true;
		}
	}
	return false;
}

//-------------------------------------
//	CheckCollision 衝突チェック
//-------------------------------------
void TmpCollisionChecker::CheckCollision( void )
{
	CheckBulletVsCoreObj();
	CheckCollisionPlayerVsStageObj();
}


////-------------------------------------
////	CheckBulletVsCoreObj 
////  当たり判定チェック 弾vsスコアオブジェクト
////-------------------------------------
//void TmpCollisionChecker::CheckBulletVsCoreObj( void )
//{
//	for( int bi = 0; bi < BULLET_MAX; bi++ )
//	{
//		for( int ci = 0; ci < COLLISION_CORE_MAX; ci++ )
//		{
//			if( pBulletCollection[ bi ] != NULL && pCoreCollection[ ci ] != NULL )
//			{
//				if( CollisionCheck::SphereVsSphere( pBulletCollection[ bi ]->ColSphape, pCoreCollection[ ci ]->ColShape ) )
//				{
//					pCoreCollection[ ci ]->Hit();
//					Bullet_GetBullet( bi )->DisEnable();  // ------------------------------------------------------------------------------------------ここの処理のためにHitした時の処理とかを見直す必要あるのでは CHANGE!>
//				}
//				else
//				{
//					// null
//				}
//			}
//			else
//			{
//				// null
//			}
//		}
//	}
//}
//
//
//void TmpCollisionChecker::CheckCollisionPlayerVsStageObj( void )
//{
//	for( int si = 0; si < COLLISION_STAGEBLOCK_MAX; si++ )
//	{
//		if( pStageBlock[ si ] != NULL && pPlayer != NULL )
//		{
//			if( CollisionCheck::OBBVsOBB( pStageBlock[ si ]->ColShape, pPlayer->ColShape ) )
//			{ // Hit
//				pPlayer->ColShape.Color = D3DCOLOR_RGBA( 255, 0, 0, 255 );
//				Collision_PushBack(&pPlayer->ColShape, &pStageBlock[si]->ColShape);
//			}
//			else
//			{ // No Hit
//				// null
//			}
//		}
//		else
//		{ // Invalid pointer
//			 // null
//		}
//	}
//}

void Collision_PushBack(ShapeOBB *pShapeMovable, ShapeOBB *pShapeStable)
{

	float diffX = (pShapeStable->pParentTransform->Get_Position().x - pShapeMovable->pParentTransform->Get_Position().x);		// X座標差分
	float diffY = (pShapeStable->pParentTransform->Get_Position().y - pShapeMovable->pParentTransform->Get_Position().y);		// Y座標差分
	float diffZ = (pShapeStable->pParentTransform->Get_Position().z - pShapeMovable->pParentTransform->Get_Position().z);		// Z座標差分

	float absX = fabs(diffX);														// X差分絶対値
	float absY = fabs(diffY);														// Y差分絶対値
	float absZ = fabs(diffZ);														// Z差分絶対値

	float lX = (pShapeStable->Length[1] + pShapeMovable->Length[1]) - absX;			// Xめり込み量
	float lY = (pShapeStable->Length[2] + pShapeMovable->Length[2]) - absY;			// Yめり込み量
	float lZ = (pShapeStable->Length[0] + pShapeMovable->Length[0]) - absZ;			// Zめり込み量

	if (lX > lY)
	{
		if (lY > lZ)
		{
			// Zめり込みが一番少ない
			if (diffZ >= 0)
			{
				// 固定物が奥側にある
				D3DXVECTOR3 NewPos = pShapeMovable->pParentTransform->Get_Position();
				NewPos.z = pShapeStable->pParentTransform->Get_Position().z - ( pShapeStable->Length[ 0 ] + pShapeMovable->Length[ 0 ] );
				pShapeMovable->pParentTransform->Set_Position( NewPos );
			}
			else
			{
				// 固定物が手前側にある
				D3DXVECTOR3 NewPos = pShapeMovable->pParentTransform->Get_Position();
				NewPos.z = pShapeStable->pParentTransform->Get_Position().z + ( pShapeStable->Length[ 0 ] + pShapeMovable->Length[ 0 ] );
				pShapeMovable->pParentTransform->Set_Position( NewPos );
			}
		}
		else
		{
			// Yめり込みが一番少ない
			if (diffY >= 0)
			{
				// 固定物が上側にある
				D3DXVECTOR3 NewPos = pShapeMovable->pParentTransform->Get_Position();
				NewPos.y = pShapeStable->pParentTransform->Get_Position().y - ( pShapeStable->Length[ 2 ] + pShapeMovable->Length[ 2 ] );
				pShapeMovable->pParentTransform->Set_Position( NewPos );
			}
			else
			{
				// 固定物が下側にある
				D3DXVECTOR3 NewPos = pShapeMovable->pParentTransform->Get_Position();
				NewPos.y = pShapeStable->pParentTransform->Get_Position().y + ( pShapeStable->Length[ 2 ] + pShapeMovable->Length[ 2 ] );
				pShapeMovable->pParentTransform->Set_Position( NewPos );
			}
		}
	}
	else
	{
		if (lX > lZ)
		{
			// Zめり込みが一番少ない
			if (diffZ >= 0)
			{
				// 固定物が奥側にある
				D3DXVECTOR3 NewPos = pShapeMovable->pParentTransform->Get_Position();
				NewPos.z = pShapeStable->pParentTransform->Get_Position().z - ( pShapeStable->Length[ 0 ] + pShapeMovable->Length[ 0 ] );
				pShapeMovable->pParentTransform->Set_Position( NewPos );
			}
			else
			{
				// 固定物が手前側にある
				D3DXVECTOR3 NewPos = pShapeMovable->pParentTransform->Get_Position();
				NewPos.z = pShapeStable->pParentTransform->Get_Position().z + ( pShapeStable->Length[ 0 ] + pShapeMovable->Length[ 0 ] );
				pShapeMovable->pParentTransform->Set_Position( NewPos );
			}
		}
		else
		{
			// Xめり込みが一番少ない
			if (diffX >= 0)
			{
				// 固定物が右側にある
				D3DXVECTOR3 NewPos = pShapeMovable->pParentTransform->Get_Position();
				NewPos.x = pShapeStable->pParentTransform->Get_Position().x - ( pShapeStable->Length[ 1 ] + pShapeMovable->Length[ 1 ] );
				pShapeMovable->pParentTransform->Set_Position( NewPos );
			}
			else
			{
				// 固定物が左側にある
				D3DXVECTOR3 NewPos = pShapeMovable->pParentTransform->Get_Position();
				NewPos.x = pShapeStable->pParentTransform->Get_Position().x + ( pShapeStable->Length[ 1 ] + pShapeMovable->Length[ 1 ] );
				pShapeMovable->pParentTransform->Set_Position( NewPos );
			}
		}
	}
}
