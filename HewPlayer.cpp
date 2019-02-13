// ===============================================================================================
// プロジェクト名: 
// ファイル名: HewPlayer.cpp
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
#include "HewPlayer.h"
//
// Windows系
// 

// 
// 自作系
//
#include"Input.h"

#include "Billboard.h"
#include "MeshField.h"


#include "CGameObject.h"
using namespace NRender3D;
#include "CCamera.h"
#include "CGun.h"
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// 
// プロトタイプ宣言
// 
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
void CameraBehavior( CPlayer* const player, D3DXVECTOR3 Distance );
void Set_GunRotate( CPlayer* const player );


//===============================================
//	CPlayer
//===============================================

static const D3DXVECTOR3 GunPos( 1.5f, 0.0f, 2.0f );
//-------------------------------------
//	コンストラクタ
//-------------------------------------

CPlayer::CPlayer( CTransform* transform, AMesh* mesh )
	:
	Gun(
		new CTransform( GunPos, { 0.5f,0.5f,0.5f }, { 0.0f,0.0f,0.0f } ),
		CGun::HANDGUN
	)
{
	this->Aty = 0.0f;
	this->Speed = SPEED_WALK;
	this->transform = transform;
	this->mesh = mesh;
	this->bLean = true;

	//Gunの設定
	this->Gun.transform->Set_Parent( this->transform );
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CPlayer::~CPlayer()
{
	delete this->transform;
	delete this->mesh;
}

//-------------------------------------
//	更新処理
//-------------------------------------
void CPlayer::Update()
{
	this->Gun.Update();

	//歩行切り替え
	if( Keyboard_IsPress( DIK_LSHIFT ) )
	{
		this->Speed = SPEED_RUN;
	}
	else
	{
		this->Speed = SPEED_WALK;
	}

	D3DXVECTOR3 Move( 0.0f, 0.0f, 0.0f );

	//進行方向
	if( Keyboard_IsPress( DIK_W ) )
	{
		this->transform->LookAt( this->Camera.at );
		Move += this->transform->Get_Forward();
	}

	if( Keyboard_IsPress( DIK_A ) )
	{
		this->transform->LookAt( this->Camera.at );
		Move -= this->transform->Get_Right();
	}

	if( Keyboard_IsPress( DIK_S ) )
	{
		this->transform->LookAt( this->Camera.at );
		Move -= this->transform->Get_Forward();
	}

	if( Keyboard_IsPress( DIK_D ) )
	{
		this->transform->LookAt( this->Camera.at );
		Move += this->transform->Get_Right();
	}

	D3DXVec3Normalize( &Move, &Move );
	*this->transform->Position() += Move * this->Speed;

	//X軸
	if( this->transform->Get_Position().x + this->Speed> MF_WALL_WIDTH*0.5f )
	{
		this->transform->Position()->x -= this->Speed;
	}

	if( this->transform->Get_Position().x - this->Speed< -MF_WALL_WIDTH *0.5f )
	{
		this->transform->Position()->x += this->Speed;
	}

	//z軸
	if( this->transform->Get_Position().z + this->Speed > MF_WALL_WIDTH *0.5f )
	{
		this->transform->Position()->z -= this->Speed;
	}

	if( this->transform->Get_Position().z - this->Speed < -MF_WALL_WIDTH *0.5f )
	{
		this->transform->Position()->z += this->Speed;
	}

	//カメラ操作
	this->Camera.m_Rotation.y -= Mouse_IsAccelerationX() * 0.001f;
	this->Camera.m_Rotation.x += Mouse_IsAccelerationY() * 0.001f;
	this->Camera.m_Rotation.x = min( this->Camera.m_Rotation.x, 1.2f );
	this->Camera.m_Rotation.x = max( this->Camera.m_Rotation.x, -1.0f );

	//Lean
	//左
	if( Keyboard_IsTrigger( DIK_Q ) )
	{
		this->bLean = false;
		this->Gun.transform->Position()->x = -GunPos.x;
	}

	//右
	if( Keyboard_IsTrigger( DIK_E ) )
	{
		this->bLean = true;
		this->Gun.transform->Position()->x = GunPos.x;
	}

	//ADS
	if( Mouse_IsLeftDown() )
	{
		Set_GunRotate( this );

		this->transform->LookAt( this->Camera.at );
		CameraBehavior( this, { 0.75f,0.4f,-0.75f } );

		//Lean　右
		if( this->bLean )
		{
			this->Camera.position += this->transform->Get_Position() + ( this->Camera.Get_Right() * 0.5f );
			this->Camera.at = ( this->Camera.Get_Forward()*10.0f ) + this->transform->Get_Position() + ( this->Camera.Get_Right() * 1.5f );
		}
		//Lean　左
		else
		{
			this->Camera.position += this->transform->Get_Position() + ( this->Camera.Get_Right() * -0.5f );
			this->Camera.at = ( this->Camera.Get_Forward()*10.0f ) + this->transform->Get_Position() + ( this->Camera.Get_Right() * -1.5f );
		}
	}
	else
	{
		CameraBehavior( this, { 2.0f, 0.8f, -2.0f } );
		this->Camera.position += this->transform->Get_Position();
		this->Camera.at = ( this->Camera.Get_Forward()*10.0f ) + this->transform->Get_Position() + ( this->Camera.Get_Right() * 1.5f );
	}

	//撃つ
	if( Keyboard_IsPress( DIK_SPACE ) )//Mouse_IsRightDown() )
	{
		Set_GunRotate( this );
		this->transform->LookAt( this->Camera.at );
		this->Gun.Burst( this->Camera.at, this->Camera.m_Rotation.x );
	}

}

//-------------------------------------
//	描画
//-------------------------------------
void CPlayer::Render()
{
	//描画
	NRender3D::Render( this->mesh, this->transform );
	//銃描画
	this->Gun.render();
	//影
	BillBoardShadow_Create( this->transform->Get_Position(), this->transform->Get_Scale() * 8.0f );
	//レティクル
	BillBoard_Create( this->Camera.at, { 1.0f,1.0f,1.0f }, NTexture::Get_Texture( NTexture::Reticle ) );
}

//===============================================
//	CameraBehavior カメラの動作
//===============================================
void CameraBehavior( CPlayer* const player, D3DXVECTOR3 Distance )
{
	float sinX = sinf( player->Camera.m_Rotation.x );
	float sinY = sinf( -player->Camera.m_Rotation.y );
	float cosY = cosf( -player->Camera.m_Rotation.y );

	player->Camera.position =
	{
		D3DXVECTOR3(
			sinY * ( ( sinX* sinX * -Distance.x ) + Distance.x ),
			( sinX * 1.0f ) + Distance.y,
			cosY * ( ( sinX * sinX * -Distance.z ) + Distance.z )
		)
	};
}

//銃の回転設定
void Set_GunRotate( CPlayer* const player )
{
	*player->Gun.transform->Rotation() = player->Camera.m_Rotation;
	player->Gun.transform->Rotation()->y = 0.0f;
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