//
//	CCoreObject.cpp	
//		Author:HIROMASA IKEDA	DATE:2018/10/13
//===============================================
#include<d3dx9.h>
#include<vector>
#include"System.h"

//Class
#include"Cube.h"
#include"CCoreObject.h"
#include"XModel.h"
#include"CStageBlockManager.h"
#include"Cube.h"

#include "Debug_Collision.h"

#include"Input.h"

// スコア
#include "Score.h"
#include "CTimer.h"
// 当たり判定系
#include "Collider.h"
#include "CollisionChecker.h"

//===============================================
//	グローバル変数
//===============================================
static CXModelName ScrewModel(NModel::NAME_END);		// ネジモデル


//===============================================
//	CoreObject	クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
// コンストラクタでのShape系クラスの初期化はCoreObject自身のtransformのアドレスを与えること. 引数のpTransformはコンストラクタ終了後,破棄される.
CoreObject::CoreObject(CTransform* pTransform, AMesh* pMesh, CORE_DISCHARGE_JUDGE_TYPE Type, CoreObject::CORE_DIRECTION face)
: 
	CGameObject(pTransform, pMesh),
	ColShape(pTransform, 1.0f)
{
	this->bHit = false;
	SetFace(face);
	this->direction = face;
	this->JudgeType = Type;
	this->SetBlocks(0, 0, 0);

	CollisionChecker::Getinstance()->Register( this );
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CoreObject::~CoreObject()
{
	CollisionChecker::Getinstance()->Deregister( this );
}

//-------------------------------------
//	ネジの向き設定
//-------------------------------------
void CoreObject::SetFace(CORE_DIRECTION face)
{
	D3DXVECTOR3 Face;
	switch (face)
	{
	case CoreObject::CORE_DIRECTION_FORWARD:
		this->face = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		this->right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case CoreObject::CORE_DIRECTION_BEHIND:
		this->face = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		this->right = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case CoreObject::CORE_DIRECTION_UP:
		this->face = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		this->right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		this->up = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		break;
	case CoreObject::CORE_DIRECTION_DOWN:
		this->face = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
		this->right = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		this->up = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		break;
	case CoreObject::CORE_DIRECTION_RIGHT:
		this->face = D3DXVECTOR3(1.0f, 0.0f, 0.0f);
		this->right = D3DXVECTOR3(0.0f, 0.0f, -1.0f);
		this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case CoreObject::CORE_DIRECTION_LEFT:
		this->face = D3DXVECTOR3(-1.0f, 0.0f, 0.0f);
		this->right = D3DXVECTOR3(0.0f, 0.0f, 1.0f);
		this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		break;
	case CoreObject::CORE_DIRECTION_MAX:
		break;
	default:
		break;
	}
}


//-------------------------------------
//	弾に当たった
//-------------------------------------
void CoreObject::Hit()
{

	if( bHit == false )
	{
		// 保持してるブロックに応じてブロックを生成して飛ばす
		for( int i = 0; i < this->BlockWidth; i++ )
		{
			for( int j = 0; j < this->BlockHeight; j++ )
			{
				for( int k = 0; k < this->BlockDepth; k++ )
				{
					// 生成するブロックの座標
					D3DXVECTOR3 position = this->transform->Get_Position() + this->right * ( (float) i - this->BlockWidth * 0.5f + 0.5f ) + this->up * ( (float) j - this->BlockHeight * 0.5f + 0.5f ) + this->face * ( k + 1.0f );
					// ブロック生成
					StageBlockManager::GetInstance()->CreateBlock( new CTransform( position, D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ), RADIALLY, this->transform->Get_Position(), this->JudgeType, CoreType );
				}
			}
		}

		// スコア加算
		Score_Plus( NumBlocks );
		switch( this->CoreType )
		{
			case CoreObject::CORE_TYPE_NORMAL:
				break;
			case CoreObject::CORE_TYPE_TIME_GAIN:
				Timer::AddTime( 5 );
				break;
			case CoreObject::CORE_TYPE_DOUBLE_POINT:
				Score_Plus( NumBlocks );
				break;
			case CoreObject::CORE_TYPE_MAX:
				break;
			default:
				break;
		}
		// スコア加算
		Score_Plus( NumBlocks );
	}
	this->bHit = true;
}

//-------------------------------------
//	生きてるコアの数を返す
//-------------------------------------
unsigned int CoreObjectManager::GetCurrentCoreExist( void ) const
{
	unsigned int ExistCoreCnt = 0;
	auto itrCore = ppCoreCollection.begin();
	while( itrCore != ppCoreCollection.end() )
	{
		if( ( *itrCore )->bHit == false )
		{
			ExistCoreCnt++;
		}
		itrCore++;
	}
	return ExistCoreCnt;
}
//-------------------------------------
//	更新処理
//-------------------------------------
void CoreObject::Update()
{
#ifdef _DEBUG
	if (Keyboard_IsTrigger(DIK_RETURN))
		Hit();
#endif
}

//-------------------------------------
//	描画
//-------------------------------------
void CoreObject::Render()
{
	// まだ撃たれていない
	if (!this->bHit)
	{
		D3DXMATRIX mtxWorld;			// ワールド変換行列
		D3DXMATRIX mtxTranslation;		// 平行移動行列
		D3DXMATRIX mtxRotation;			// 回転行列
		D3DXMATRIX mtxScaling;			// 拡大縮小行列
		
		D3DXMATRIX mtxTransform;		// 
		D3DXMATRIX mtxRotationY;		// 
		D3DXMATRIX mtxRotationAxis;		// 
		D3DXVECTOR3 vecFaceGroud;		// 
		D3DXVECTOR3 vecRight;			// 

		D3DXMatrixTranslation(&mtxTranslation, 0.0f, -0.5f, 0.0f);
		D3DXMatrixScaling(&mtxScaling, 0.5f, 0.5f, 0.5f);
		mtxTransform = mtxTranslation * mtxScaling;


		//===============================================================

		// 平行移動行列
		D3DXMatrixTranslation(&mtxTranslation, this->transform->Get_Position().x, this->transform->Get_Position().y, this->transform->Get_Position().z);

		// 回転行列
		switch (this->direction)
		{
		case CoreObject::CORE_DIRECTION_FORWARD:
			D3DXMatrixIdentity(&mtxRotation);
			break;
		case CoreObject::CORE_DIRECTION_BEHIND:
			D3DXMatrixRotationY(&mtxRotation, D3DX_PI);
			break;
		case CoreObject::CORE_DIRECTION_UP:
			D3DXMatrixRotationX(&mtxRotation, -D3DX_PI / 2);
			break;
		case CoreObject::CORE_DIRECTION_DOWN:
			D3DXMatrixRotationX(&mtxRotation, D3DX_PI / 2);
			break;
		case CoreObject::CORE_DIRECTION_RIGHT:
			D3DXMatrixRotationY(&mtxRotation, D3DX_PI / 2);
			break;
		case CoreObject::CORE_DIRECTION_LEFT:
			D3DXMatrixRotationY(&mtxRotation, -D3DX_PI / 2);
			break;
		case CoreObject::CORE_DIRECTION_MAX:
			break;
		default:
			break;
		}

		// 拡大縮小行列
		D3DXMatrixScaling(&mtxScaling, 1.0f, 1.0f, 1.0f);

		//合成
		mtxWorld = mtxTransform * mtxRotation * mtxScaling * mtxTranslation;
		
		//ネジの描画
		NRender3D::Render(mesh, &mtxWorld);

		//当たり判定の描画
		ColShape.DebugDraw();

		//張りぼての描画
		RenderBox();
	}
}

void CoreObject::RenderBox()
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = System_GetDevice();

	// 頂点リスト
	CubeVertex3D Vertex[]
		=
	{
		{ D3DXVECTOR3(-0.5f, 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // 手前面
		{ D3DXVECTOR3(0.5f , 0.5f , -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	D3DXVECTOR2((float)this->BlockWidth, 0.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	D3DXVECTOR2(0.0f, (float)this->BlockHeight) },
		{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, 0.0f, -1.0f),	D3DXVECTOR2((float)this->BlockWidth, (float)this->BlockHeight) },

		{ D3DXVECTOR3(0.5f, 0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // 右面
		{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DXVECTOR2((float)this->BlockDepth, 0.0f) },
		{ D3DXVECTOR3(0.5f, -0.5f, -0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, (float)this->BlockHeight) },
		{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(1.0f, 0.0f, 0.0f),	D3DXVECTOR2((float)this->BlockDepth, (float)this->BlockHeight) },

		{ D3DXVECTOR3(0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // 奥面
		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DXVECTOR2((float)this->BlockWidth, 0.0f) },
		{ D3DXVECTOR3(0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DXVECTOR2(0.0f, (float)this->BlockHeight) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, 0.0f, 1.0f),	D3DXVECTOR2((float)this->BlockWidth, (float)this->BlockHeight) },

		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // 左面
		{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DXVECTOR2((float)this->BlockDepth, 0.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DXVECTOR2(0.0f, (float)this->BlockHeight) },
		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(-1.0f, 0.0f, 0.0f),	D3DXVECTOR2((float)this->BlockDepth, (float)this->BlockHeight) },

		{ D3DXVECTOR3(-0.5f, 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // 上面
		{ D3DXVECTOR3(0.5f , 0.5f, 0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DXVECTOR2((float)this->BlockWidth, 0.0f) },
		{ D3DXVECTOR3(-0.5f, 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DXVECTOR2(0.0f, (float)this->BlockDepth) },
		{ D3DXVECTOR3(0.5f , 0.5f, -0.5f),	D3DXVECTOR3(0.0f, 1.0f, 0.0f),	D3DXVECTOR2((float)this->BlockWidth, (float)this->BlockDepth) },

		{ D3DXVECTOR3(-0.5f, -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DXVECTOR2(0.0f, 0.0f) }, // 下面
		{ D3DXVECTOR3(0.5f , -0.5f, -0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DXVECTOR2((float)this->BlockWidth, 0.0f) },
		{ D3DXVECTOR3(-0.5f, -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DXVECTOR2(0.0f, (float)this->BlockDepth) },
		{ D3DXVECTOR3(0.5f , -0.5f, 0.5f),	D3DXVECTOR3(0.0f, -1.0f, 0.0f),	D3DXVECTOR2((float)this->BlockWidth, (float)this->BlockDepth) }
	};

	// 頂点インデックスの作成
	WORD Index[36];
	for (int i = 0; i < 6; i++)
	{
		Index[i * 6 + 0] = (WORD)i * 4 + 0;
		Index[i * 6 + 1] = (WORD)i * 4 + 1;
		Index[i * 6 + 2] = (WORD)i * 4 + 2;
		Index[i * 6 + 3] = (WORD)i * 4 + 1;
		Index[i * 6 + 4] = (WORD)i * 4 + 3;
		Index[i * 6 + 5] = (WORD)i * 4 + 2;
	}

	D3DXMATRIX mtxWorld;
	D3DXMATRIX mtxTranslation;
	D3DXMATRIX mtxScaling;
	D3DXMATRIX mtxRotation;

	// はりぼて中心座標
	D3DXVECTOR3 position = this->transform->Get_Position() + this->face * this->BlockDepth * 0.5f;
	D3DXMatrixTranslation(&mtxTranslation, position.x, position.y, position.z);

	// 回転行列
	switch (this->direction)
	{
	case CoreObject::CORE_DIRECTION_FORWARD:
		D3DXMatrixIdentity(&mtxRotation);
		break;
	case CoreObject::CORE_DIRECTION_BEHIND:
		D3DXMatrixRotationY(&mtxRotation, D3DX_PI);
		break;
	case CoreObject::CORE_DIRECTION_UP:
		D3DXMatrixRotationX(&mtxRotation, -D3DX_PI / 2);
		break;
	case CoreObject::CORE_DIRECTION_DOWN:
		D3DXMatrixRotationX(&mtxRotation, D3DX_PI / 2);
		break;
	case CoreObject::CORE_DIRECTION_RIGHT:
		D3DXMatrixRotationY(&mtxRotation, D3DX_PI / 2);
		break;
	case CoreObject::CORE_DIRECTION_LEFT:
		D3DXMatrixRotationY(&mtxRotation, -D3DX_PI / 2);
		break;
	case CoreObject::CORE_DIRECTION_MAX:
		break;
	default:
		break;
	}

	// 拡大縮小行列
	D3DXMatrixScaling(&mtxScaling, this->BlockWidth, this->BlockHeight, this->BlockDepth);

	// 行列の合成
	mtxWorld = mtxScaling * mtxRotation * mtxTranslation;

	// 描画
	pDevice->SetFVF(FVF_CUBE_VERTEX3D);
	pDevice->SetTransform(D3DTS_WORLD, &mtxWorld);
	pDevice->SetTexture(0, NTexture::Get_Texture(NTexture::CubeTexture));

	pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 24, 12, Index, D3DFMT_INDEX16, Vertex, sizeof(Vertex[0]));
}

//-------------------------------------
//	ネジの向きの取得
//-------------------------------------
D3DXVECTOR3 CoreObject::GetFace()
{
	return this->face;
}

//-------------------------------------
//	判定設定
//-------------------------------------
void CoreObject::Set_JudgeType(CORE_DISCHARGE_JUDGE_TYPE Type)
{
	this->JudgeType = Type;
}

//-------------------------------------
//	ブロック数設定
//-------------------------------------
void CoreObject::SetBlocks(int x, int y, int z)
{
	this->BlockWidth = x;
	this->BlockHeight = y;
	this->BlockDepth = z;
	this->NumBlocks = x * y * z;
}


//===============================================
//	CoreObjectManager	クラス
//===============================================

CoreObjectManager* CoreObjectManager::pInstance = nullptr;

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CoreObjectManager::CoreObjectManager()
{

}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CoreObjectManager::~CoreObjectManager()
{

}

//-------------------------------------
//	インスタンスのゲッター
//-------------------------------------
CoreObjectManager* CoreObjectManager::GetInstance( void )
{
	if( pInstance == nullptr )
	{
		pInstance = new CoreObjectManager();
		pInstance->pCoreModel = new CXModelMesh( "neji.x", "neji" );
		CXModelData::Model = pInstance->pCoreModel;
	}

	return pInstance;
}

//-------------------------------------
// CoreObject生成
//-------------------------------------
void CoreObjectManager::CreateCore( D3DXVECTOR3 _Pos, unsigned int _X, unsigned int _Y, unsigned int _Z )
{
	ppCoreCollection.push_back( new CoreObject( new CTransform( _Pos, D3DXVECTOR3( 1.0f, 1.0f, 1.0f ), D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) ),
												new CXModelData(),
												CoreObject::CORE_JUDGE_TYPE_0, CoreObject::CORE_DIRECTION_FORWARD ) );
	ppCoreCollection.back()->SetBlocks( _X, _Y, _Z );
}

//-------------------------------------
// CoreObject更新
//-------------------------------------
void CoreObjectManager::UpdateCoreAll( void )
{
	for( auto itr = ppCoreCollection.begin(); itr != ppCoreCollection.end(); itr++ )
	{
		( *itr )->Update();
	}
}

//-------------------------------------
// CoreObject描画
//-------------------------------------
void CoreObjectManager::RenderCoreAll( void )
{
	for( auto itr = ppCoreCollection.begin(); itr != ppCoreCollection.end(); itr++ )
	{
		( *itr )->Render();
	}
}

//-------------------------------------
// CoreObjectおわり
//-------------------------------------
void CoreObjectManager::Finalize( void )
{
	for( auto itr = ppCoreCollection.begin(); itr != ppCoreCollection.end(); itr++ ) // やばければこれ直す.
	{
		delete ( *itr );
	}
	ppCoreCollection.clear();
}