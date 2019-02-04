//
//	Transform.cpp
//		Author:HIROMASA IKEDA	DATA:2018/11/22
//===============================================
#include<d3dx9.h>
#include"CTransform.h"

//===============================================
//	グローバル変数
//===============================================

//=========================================================
//	CTransform
//=========================================================

//===============================================
//	Constructor/Destroctor
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
CTransform::CTransform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation)
{
	this->m_bEnable_Convert = true;
	this->m_bConverted = false;

	this->m_pParent = NULL;

	//ワールド位置を設定
	this->m_Position = Position;
	this->m_Rotation = Rotation;
	this->m_Scale = Scale;

	this->Get_MtxWorld();
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
CTransform::~CTransform()
{
	this->m_pParent = NULL;

	//子を持っているなら
	if (this->m_pChild.size() > 0)
	{
		for (int i = 0; i < this->m_pChild.size(); i++)
		{
			//親を無くす
			this->m_pChild.at(i)->Release_Parent();
		}
	}
}

//===============================================
//	行列変換
//===============================================

//-------------------------------------
//	行列変換 開始
//-------------------------------------

D3DXMATRIX CTransform::Convert()
{
	if (this->m_bConverted == true || this->m_bEnable_Convert == true) return this->m_MtxWorld;

	D3DXMatrixIdentity(&this->m_MtxWorld);
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	this->m_MtxWorld = this->m_MtxScale * this->m_MtxRotation * this->m_MtxTransform;

	if (this->Have_a_Parent())
	{
		this->m_MtxWorld *= this->m_pParent->Convert();
	}

	this->m_bConverted = true;

	return this->m_MtxWorld;
}

//-------------------------------------
//	ワールド情報
//-------------------------------------

D3DXVECTOR3* CTransform::Position()
{
	this->Get_Position();
	return &this->m_Position;
}

D3DXVECTOR3* CTransform::Rotation()
{
	this->Get_Rotation();
	return &this->m_Rotation;
}

D3DXVECTOR3* CTransform::Scale()
{
	this->Get_Scale();
	return &this->m_Scale;
}

//・Get Position	位置情報
D3DXVECTOR3 CTransform::Get_Position()
{
	if (this->Have_a_Parent())
	{
		D3DXVECTOR3 position(1.0f,1.0f,1.0f);
		D3DXVec3TransformCoord(&position, &position, &this->Get_MtxWorld());
		return position;
	}

	return this->m_Position;
}

//・Get Rotation	回転情報
//	親のワールド回転値に自身の回転値を加算
//
D3DXVECTOR3 CTransform::Get_Rotation()
{
	if (this->Have_a_Parent())
	{
		this->m_Rotation += this->m_pParent->Get_Rotation();
	}

	return this->m_Rotation;
}

//・Get Scale		大きさ情報
//	親のスケール値に自身のスケール値を乗算
//	
D3DXVECTOR3 CTransform::Get_Scale()
{
	D3DXVECTOR3 Scale = this->m_Scale;

	if (this->Have_a_Parent())
	{
		D3DXVECTOR3 ParentScale = this->m_pParent->Get_Scale();
		Scale.x *= ParentScale.x;
		Scale.y *= ParentScale.y;
		Scale.z *= ParentScale.z;
	}

	return Scale;
}

//Set Position
void CTransform::Set_Position(D3DXVECTOR3 Position)
{
	//親との相対位置を算出
	if (this->Have_a_Parent())
	{
		Position -= this->m_pParent->Get_Position();
	}

	this->m_Position = Position;

	return;
}

//Set Rotation
void CTransform::Set_Rotation(D3DXVECTOR3 Rotation)
{
	if (this->Have_a_Parent())
	{
		Rotation -= this->m_pParent->Get_Rotation();
	}

	this->m_Rotation = Rotation;

	return;
}

//Set Scale
void CTransform::Set_Scale(D3DXVECTOR3 Scale)
{
	if (this->Have_a_Parent())
	{
		D3DXVECTOR3 scale = this->m_pParent->Get_Scale();
		Scale.x /= scale.x;
		Scale.y /= scale.y;
		Scale.z /= scale.z;
	}

	this->m_Scale = Scale;
	return;
}

//-------------------------------------
//	行列関係
//-------------------------------------

D3DXMATRIX* CTransform::MtxTransform()
{
	this->Get_MtxTransform();
	return &this->m_MtxTransform;
}

D3DXMATRIX* CTransform::MtxScale()
{
	this->Get_MtxScale();
	return &this->m_MtxScale;
}

D3DXMATRIX* CTransform::MtxRotation()
{
	this->Get_MtxRotation();
	return &this->m_MtxRotation;
}

D3DXMATRIX* CTransform::MtxWorld()
{
	this->Get_MtxWorld();
	return &this->m_MtxWorld;
}

//	Get MtxTransform	位置行列
D3DXMATRIX CTransform::Get_MtxTransform()
{
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);

	if (this->Have_a_Parent())
	{
		this->m_MtxTransform *= this->m_pParent->Get_MtxTransform();
	}

	return this->m_MtxTransform;
}

//	Get MtxRotation	回転行列
D3DXMATRIX CTransform::Get_MtxRotation()
{
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	if (this->Have_a_Parent())
	{
		this->m_MtxRotation *= this->m_pParent->Get_MtxRotation();
	}

	return this->m_MtxRotation;
}

//	Get MtxScale	サイズ行列
D3DXMATRIX CTransform::Get_MtxScale()
{
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);

	if (this->Have_a_Parent())
	{
		this->m_MtxScale *= this->m_pParent->Get_MtxScale();
	}

	return this->m_MtxScale;
}

//	Get MtxWorld ワールド空間行列
D3DXMATRIX CTransform::Get_MtxWorld()
{
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);

	this->m_MtxWorld = this->m_MtxScale * this->m_MtxRotation * this->m_MtxTransform;

	if (this->Have_a_Parent())
	{
		this->m_MtxWorld *= this->m_pParent->Get_MtxWorld();
	}

	return this->m_MtxWorld;
}

//-------------------------------------
//	相対行列 取得
//-------------------------------------

D3DXMATRIX CTransform::Get_localMtxTransform()
{
	D3DXMatrixTranslation(&this->m_MtxTransform, this->m_Position.x, this->m_Position.y, this->m_Position.z);
	return this->m_MtxTransform;
}

D3DXMATRIX CTransform::Get_localMtxScale()
{
	D3DXMatrixScaling(&this->m_MtxScale, this->m_Scale.x, this->m_Scale.y, this->m_Scale.z);
	return this->m_MtxScale;
}

D3DXMATRIX CTransform::Get_localMtxRotation()
{
	D3DXMatrixRotationYawPitchRoll(&this->m_MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);
	return this->m_MtxRotation;
}

D3DXMATRIX CTransform::Get_localMtxWorld()
{
	this->m_MtxWorld = this->Get_MtxScale() * this->Get_MtxRotation() * this->Get_MtxTransform();
	return this->m_MtxWorld;
}

//-------------------------------------
//	行列　設定
//-------------------------------------

void CTransform::Set_MtxTransform(D3DXMATRIX MtxTransform)
{
	this->m_MtxTransform = MtxTransform;
}

void CTransform::Set_MtxScale(D3DXMATRIX MtxScale)
{
	this->m_MtxScale = MtxScale;
}

void CTransform::Set_MtxRotation(D3DXMATRIX MtxRotation)
{
	this->m_MtxRotation = MtxRotation;
}

void CTransform::Set_MtxWorld(D3DXMATRIX MtxWorld)
{
	this->m_MtxWorld = MtxWorld;
}

//-------------------------------------
//	相対位置 取得
//-------------------------------------

D3DXVECTOR3 CTransform::Get_localPosition()
{
	return this->m_Position;
}

D3DXVECTOR3 CTransform::Get_localRotation()
{
	return this->m_Rotation;
}

D3DXVECTOR3 CTransform::Get_localScale()
{
	return this->m_Scale;
}

//-------------------------------------
//	相対位置 設定
//-------------------------------------

void CTransform::Set_localPosition(D3DXVECTOR3 position)
{
	this->m_Position = position;
}

void CTransform::Set_localRotation(D3DXVECTOR3 rotation)
{
	this->m_Rotation = rotation;
}

void CTransform::Set_localScale(D3DXVECTOR3 scale)
{
	this->m_Scale = scale;
}

//-------------------------------------
//	方向関係
//-------------------------------------

//Get 上
D3DXVECTOR3 CTransform::Get_Up()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//up
	D3DXVECTOR3 up(0.0f, 1.0f, 0.0f);
	D3DXVec3TransformNormal(&up, &up, &MtxRotation);
	D3DXVec3Normalize(&up, &up);

	MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//right
	D3DXVECTOR3 right(1.0f, 0.0f, 0.0f);
	D3DXVec3TransformNormal(&right, &right, &MtxRotation);
	D3DXVec3Normalize(&right, &right);

	return right;
}

//Get 前
D3DXVECTOR3 CTransform::Get_Forward()
{
	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	//right
	D3DXVECTOR3 forward(0.0f, 0.0f, 1.0f);
	D3DXVec3TransformNormal(&forward, &forward, &MtxRotation);
	D3DXVec3Normalize(&forward, &forward);

	return forward;
}

//Get 右
D3DXVECTOR3 CTransform::Get_Right()
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
//	回転関数
//===============================================

//-------------------------------------
//	Rotation
//-------------------------------------
void CTransform::RotationVec3(const D3DXVECTOR3 value)
{
	this->m_Rotation += value;	//加算

	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	return;
}

//-------------------------------------
//	RotationAxis
//-------------------------------------
void CTransform::RotationAxis(const D3DXVECTOR3 Axis, const float Value)
{
	D3DXMATRIX MtxAxis;
	D3DXMatrixRotationAxis(&MtxAxis, &Axis, Value);

	D3DXVECTOR3 VecAxis;
	D3DXVec3TransformNormal(&VecAxis, &VecAxis, &MtxAxis);	//変化値を得る

	this->m_Rotation += VecAxis;	//加算

	D3DXMATRIX MtxRotation;
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->m_Rotation.y, this->m_Rotation.x, this->m_Rotation.z);

	return;
}

//===============================================
//	親子関係
//===============================================

//-------------------------------------
//	親を設定
//-------------------------------------
void CTransform::Set_Parent(CTransform* pParent)
{
	this->m_pParent = pParent;
	pParent->m_pChild.push_back(this);
}

//-------------------------------------
//	取得
//-------------------------------------
CTransform* CTransform::Get_Parent()
{
	return this->m_pParent;
}

//-------------------------------------
//	親と離れる
//-------------------------------------
void CTransform::Release_Parent()
{
	if (this->m_pParent == NULL) return;
	this->m_pParent->Release_Child(this);

	D3DXVECTOR3 position = this->Get_Position();
	D3DXVECTOR3 scale = this->Get_Scale();
	D3DXVECTOR3 rotation = this->Get_Rotation();

	this->m_pParent = NULL;

	this->Set_Position(position);
	this->Set_Scale(scale);
	this->Set_Rotation(rotation);
}

void CTransform::Release_Child(CTransform* pChild)
{
	auto itr = this->m_pChild.begin();
	while(itr != this->m_pChild.end())
	{
		if(*itr == pChild)
		{
			this->m_pChild.erase(itr);
			break;
		}
		itr++;
	}
}

void CTransform::ConvertEnable(bool enable)
{
	this->m_bEnable_Convert = enable;
}

bool CTransform::Have_a_Parent()
{
	if (this->m_pParent != NULL)
	{
		return true;
	}

	return false;
};

void CTransform::LookAt(D3DXVECTOR3 Vector)
{
	D3DXVECTOR3 vec = Vector - this->Get_Position();
	
	/* 不安要因
	D3DXVECTOR3 rot(
		atan2f(vec.y, vec.z),
		atan2f(vec.x, vec.z),
		atan2f(vec.y, vec.x)
	);
	*/

	this->Rotation()->y = atan2f(vec.x,vec.z);
}

/*
//===============================================
//	Transform
//===============================================

//-------------------------------------
//	再変換を可能
//-------------------------------------
void Transform::ConvertReset()
{
	for(int i = 0; i < pIndex.size();i++)
	{
		pIndex.at(i)->bConverted = false;	//Windowでエラーが起きる原因っぽい
	}
}

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Transform::Transform(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, D3DXVECTOR3 Rotation)
{
	this->bConverted = false;
	this->pParent = NULL;

	//ワールド情報
	this->Position = Position;
	this->Scale = Scale;
	this->Rotation = Rotation;

	//ローカル情報
	this->position = Position;
	this->scale = Scale;
	this->rotation = Rotation;

	this->up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	this->forward = D3DXVECTOR3(0.0f, 0.0f, 1.0f);

	D3DXVec3Normalize(&this->forward, &this->forward);
	D3DXVec3Cross(&this->right, &this->forward, &this->up);
	D3DXVec3Normalize(&this->right, &this->right);

	pIndex.push_back(this);
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
Transform::~Transform()
{
	this->pParent = NULL;

	//子を持っているなら
	if (this->pChild.size() > 0)
	{
		for (int i = 0; i < this->pChild.size(); i--)
		{
			//子に親の死亡を伝える
			this->pChild.at(i)->Release_Parent();
		}
	}

	this->pChild.clear();
}

//-------------------------------------
//	親を設定
//-------------------------------------
void Transform::Set_Parent(Transform* pParent)
{
	this->pParent = pParent;
	pParent->pChild.push_back(this);	//親に子を覚えさせる

	this->Position = pParent->Position + this->position;
	this->Scale = pParent->Scale + this->scale;
	this->Rotation = pParent->Rotation + this->rotation;

}

//-------------------------------------
//	情報を更新
//-------------------------------------
Transform* Transform::Set_UpdateTransform()
{
	if (this->pParent != NULL)
	{
		this->Position = pParent->Position + this->position;
		this->Scale = pParent->Scale + this->scale;
		this->Rotation = pParent->Rotation + this->rotation;
	}
	else
	{
		this->Position = this->position;
		this->Rotation = this->rotation;
		this->Scale = this->scale;
	}

	return this;
}

//-------------------------------------
//	親を取得
//-------------------------------------	
Transform* Transform::Get_Parent()
{
	return this->pParent;
}

//-------------------------------------
//	行列変換
//-------------------------------------
D3DXMATRIX Transform::Convert()
{
	this->bConverted = false;
	this->Set_UpdateTransform();
	if (this->bConverted) return this->MtxWorld;	//一度変換されている

	//各行列
	D3DXMATRIX MtxTransform;	//位置
	D3DXMATRIX MtxScale;		//大きさ
	D3DXMATRIX MtxRotation;		//回転

	//行列変換
	D3DXMatrixTranslation(&MtxTransform, this->position.x, this->position.y, this->position.z);
	D3DXMatrixScaling(&MtxScale, this->scale.x, this->scale.y, this->scale.z);
	D3DXMatrixRotationYawPitchRoll(&MtxRotation, this->rotation.y, this->rotation.x, this->rotation.z);

	//上情報
	this->up = D3DXVECTOR3(0.0f,1.0f,0.0f);
	D3DXVec3TransformNormal(&this->up,&this->up,&MtxRotation);
	D3DXVec3Normalize(&this->up, &this->up);

	//前情報
	this->forward = D3DXVECTOR3(0.0f,0.0f,1.0f);
	D3DXVec3TransformNormal(&this->forward,&this->forward,&MtxRotation);
	D3DXVec3Normalize(&this->forward, &this->forward);

	//右情報
	D3DXVec3Cross(&this->right, &this->up, &this->forward);

	//ワールド行列の作成
	D3DXMatrixIdentity(&this->MtxWorld);
	this->MtxWorld = MtxScale * MtxRotation * MtxTransform;

	//親が居る
	if (this->pParent != NULL)
	{
		//親の行列見てくる
		this->MtxWorld *= this->pParent->Convert();
	}

	//変換終了	
	this->bConverted = true;

	return this->MtxWorld;
}

//-------------------------------------
//	親を放す
//-------------------------------------
void Transform::Release_Parent()
{
	this->pParent = NULL;
}
*/

//===============================================
//	Transform2
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Transform2::Transform2(D3DXVECTOR2 Position,D3DXVECTOR2 Scale,float Rotation)
{
	this->m_Position = Position;
	this->m_Scale = Scale;
	this->m_Rotation = Rotation;
}

//-------------------------------------
//	デストラクタ
//-------------------------------------
Transform2::~Transform2()
{

}

//-------------------------------------
//	ポインタ参照
//-------------------------------------
D3DXVECTOR2* Transform2::Position()
{
	return &this->m_Position;
}

D3DXVECTOR2* Transform2::Scale()
{
	return &this->m_Scale;
}

float* Transform2::Rotation()
{
	return &this->m_Rotation;
}

//-------------------------------------
//	Setter
//-------------------------------------
void Transform2::Set_Position(D3DXVECTOR2 position)
{
	this->m_Position = position;
}

void Transform2::Set_Scale(D3DXVECTOR2 Scale)
{
	this->m_Scale = Scale;
}

void Transform2::Set_Rotation(float rotation)
{
	this->m_Rotation = rotation;
}

//-------------------------------------
//	Getter
//-------------------------------------
D3DXVECTOR2 Transform2::Get_Position()
{
	return this->m_Position;
}
D3DXVECTOR2 Transform2::Get_Scale()
{
	return this->m_Scale;
}
float Transform2::Get_Rotation()
{
	return this->m_Rotation;
}
