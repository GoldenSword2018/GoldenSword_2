//
//	CCamera.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/17
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include<d3dx9.h>
#include<vector>
#include"common.h"
#include"input.h"
#include"System.h"

//classs
#include"CCamera.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	グローバル変数	global
//===============================================
ACamera*  ACamera::pMainCamera = NULL;

//===============================================
//	ACamera
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
ACamera::ACamera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov)
{
	this->m_Rotation = D3DXVECTOR3(0.0f,0.0f,0.0f);
	this->position = Position;
	this->at = At;
	this->atDistance = AtDistance;
	this->fov = fov;
}

//-------------------------------------
//	メインカメラの取得
//-------------------------------------
ACamera* ACamera::Get_Main()
{
	return pMainCamera;
}

//-------------------------------------
//	描画
//-------------------------------------
bool ACamera::Begin()
{
	if (pMainCamera == NULL)
	{
		MessageBox(*System_GethWnd(), "メインカメラが設定されていません。", "CCamera.cpp", MB_OK);
		DestroyWindow(*System_GethWnd());
		return false;
	}

	//------------------------------------
	//	ビュー変換行列
	//------------------------------------
	D3DXMATRIX mtxView;							//ビュー変換行列
	D3DXMatrixLookAtLH(&mtxView, &pMainCamera->position, &pMainCamera->at, &pMainCamera->Get_Up());	//変換
	System_GetDevice()->SetTransform(D3DTS_VIEW, &mtxView);		//デバイスへ登録
	pMainCamera->MtxView = mtxView;

	//------------------------------------
	//	プロジェクション変換行列
	//------------------------------------
	D3DXMATRIX mtxProjection;		//プロジェクション変換行列
	D3DXMatrixPerspectiveFovLH(&mtxProjection, D3DXToRadian(60), (float)WINDOWSCREEN_WIDTH / WINDOWSCREEN_HEIGHT, 0.1f, 100.0f);	//Fovは画角　変換
	System_GetDevice()->SetTransform(D3DTS_PROJECTION, &mtxProjection);	//デバイスへ登録
	pMainCamera->MtxProjection = mtxProjection;

	return true;
}

D3DXVECTOR3 ACamera::Get_ScreenToWorld(float z)
{
	D3DXVECTOR3 pOut(0.0f,0.0f,0.0f);

	D3DXMATRIX InvView, InvPrj, VP, InvViewport;
	D3DXMatrixInverse( &InvView,NULL, &this->MtxView);
	D3DXMatrixInverse( &InvPrj, NULL, &this->MtxProjection);
	D3DXMatrixIdentity( &VP );

	VP._11 = WINDOWSCREEN_WIDTH_2;
	VP._22 = WINDOWSCREEN_HEIGHT_2;
	VP._41 = WINDOWSCREEN_WIDTH_2;
	VP._42 = WINDOWSCREEN_HEIGHT_2;

	D3DXMatrixInverse(&InvViewport, NULL, &VP);

	D3DXMATRIX tmp = InvViewport * InvPrj * InvView;
	D3DXVec3TransformCoord( &pOut,&D3DXVECTOR3(Mouse_IsMouseX(),Mouse_IsMouseY(),z),&tmp);

	return pOut;
}

//-------------------------------------
//	View行列取得
//-------------------------------------
D3DXMATRIX ACamera::Get_ViewMatrix()
{
	return pMainCamera->MtxView;
}

//-------------------------------------
//	メインカメラに設定
//-------------------------------------
void ACamera::Set_Main()
{
	pMainCamera = this;
}

//-------------------------------------
//	そっち向く
//-------------------------------------
void ACamera::LookingAt(D3DXVECTOR3 AtPosition)
{
	this->at = AtPosition;
	this->position = this->at - (this->Get_Forward() * this->atDistance);
}

D3DXVECTOR3 ACamera::Get_Forward()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//right
	D3DXVECTOR3 forward(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformNormal(&forward, &forward, &MtxRotation);
	D3DXVec3Normalize(&forward, &forward);

	return forward;
}

D3DXVECTOR3 ACamera::Get_Up()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//up
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVec3TransformNormal(&up, &up, &MtxRotation);
	D3DXVec3Normalize(&up, &up);

	return up;
}

D3DXVECTOR3 ACamera::Get_Right()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//right
	D3DXVECTOR3 right(1.0f, 0.0f, 0.0f);
	D3DXVec3TransformNormal(&right, &right, &MtxRotation);
	D3DXVec3Normalize(&right, &right);

	return right;
}

//===============================================
//	Camera
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Camera::Camera(D3DXVECTOR3 Position, D3DXVECTOR3 At, float AtDistance, float fov)
:
	ACamera(Position,At,AtDistance,fov)
{
	
}

//-------------------------------------
//	更新
//-------------------------------------
void Camera::Update()
{

}

//===============================================
//	OperationCamera
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
OperationCamera::OperationCamera(D3DXVECTOR3 Position, D3DXVECTOR3 At,float AtDistance,float fov)
:
	ACamera(Position,At,AtDistance,fov)
{
	this->Speed = CAMERA_INITIALSPEED;
	this->SpeedMag = 1.0f;
}

//-------------------------------------
//	更新
//-------------------------------------
void OperationCamera::Update()
{
	//------------------------------------
	//	カメラ
	//------------------------------------

	D3DXVECTOR3 front = this->Get_Forward();
	D3DXVECTOR3 right = this->Get_Right();
	right.y = 0.0f;

	if(Keyboard_IsPress(DIK_LCONTROL))
	{
		if(Mouse_IsRightDown())
		{
			this->m_Rotation.y += Mouse_IsAccelerationX() * 0.001f;
			this->m_Rotation.x += Mouse_IsAccelerationY() * 0.001f;
		}

		this->position = at - this->Get_Forward() * this->atDistance;
	}
	else
	{
		if(Keyboard_IsPress(DIK_LSHIFT))
		{
			SpeedMag += 0.05f;
			SpeedMag = min(SpeedMag,20.0f);
		}
		else
		{
			SpeedMag = 1.0f;
		}

		if (Mouse_IsRightDown())
		{
			this->m_Rotation.y += Mouse_IsAccelerationX() * 0.001f;
			this->m_Rotation.x += Mouse_IsAccelerationY() * 0.001f;
		}

		if (Keyboard_IsPress(DIK_W))
		{
			this->position += front * this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_S))
		{
			this->position -= front * this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_A))
		{
			this->position += right * this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_D))
		{
			this->position -= right * this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_Q))
		{
			this->position.y -= this->Speed * SpeedMag;
		}

		if (Keyboard_IsPress(DIK_E))
		{
			this->position.y += this->Speed * SpeedMag;
		}

		this->atDistance += Mouse_IsAccelerationZ() *0.005f;

		if (this->atDistance > 1.0f)
		{
			this->position -= this->Get_Forward() * Mouse_IsAccelerationZ() * 0.005f;
		}
		else
		{
			this->atDistance = 1.0f;
		}
	}

	this->at = this->Get_Forward() * this->atDistance + this->position;

	return;
}

