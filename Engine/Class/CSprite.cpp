//
//	CSprite.cpp
//		Author:HIROMASA IKEDA	DATE:2018/10/01
//===============================================
#include<d3dx9.h>
#include"CSprite.h"
#include"Sprite.h"

namespace NRender2D
{
	//===========================================
	//	CSprite
	//===========================================

	//------------------------------------
	//	コンストラクタ
	//------------------------------------
	CSprite::CSprite()
	{
		this->m_transform = new Transform2();
		this->m_texture = new NTexture::Texture();
		this->m_Color = D3DCOLOR_RGBA(255,255,255,255);
	}

	CSprite::CSprite(Transform2* transform, NTexture::Texture* texture,D3DCOLOR Color)
	{
		this->m_transform = transform;
		this->m_texture = texture;
		this->m_Color = Color;
	}

	//------------------------------------
	//	デストラクタ
	//------------------------------------
	CSprite::~CSprite()
	{
		delete m_texture;
	}
	


	//------------------------------------
	//	Getter
	//------------------------------------
	Transform2 CSprite::Get_Transform()
	{
		return *this->m_transform;
	}

	NTexture::Texture CSprite::Get_Texture()
	{
		return *this->m_texture;
	}

	D3DCOLOR CSprite::Get_Color()
	{
		return this->m_Color;
	}

	//------------------------------------
	//	Setter
	//------------------------------------
	void CSprite::Set_Transform(Transform2* transform)
	{
		this->m_transform = transform;
	}

	void CSprite::Set_Texture(NTexture::Texture* texture)
	{
		this->m_texture = texture;
	}

	void CSprite::Set_Color(D3DCOLOR color)
	{
		this->m_Color = color;
	}

	//------------------------------------
	//	render
	//------------------------------------
	void CSprite::Render()
	{
		Sprite_Rotate(this->m_transform,this->m_texture,this->m_Color);
	}

}
