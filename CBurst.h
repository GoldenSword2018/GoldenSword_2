//
//	CBurst.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef CBURST_H
#define CBURST_H

//================================================
//	インクルード	include
//================================================
#include"common.h"
#include<d3dx9.h>

//Class
#include"Texture.h"
#include"Animation.h"
#include"Billboard.h"

//================================================
//	マクロ定義	define
//================================================


//================================================
//	列挙型		enum
//================================================


//================================================
//	構造体		struct/typedef
//================================================


//================================================
//	グローバル変数　global
//================================================


//================================================
//	クラス		class
//================================================

//-------------------------------------
//	CBurst
//-------------------------------------
class CBurst:public ABillboard
{
private:
	bool bDepthTest;
public:
	NTexture::Texture* texture;
	NTexture::CAnimation* animation;
public:
	CBurst(D3DXVECTOR3 Position,D3DXVECTOR3 Scale, bool bDepthTest);
	CBurst(D3DXVECTOR3 Position, D3DXVECTOR3 Scale, NTexture::Texture* texture, NTexture::CAnimation* animation, bool bDepthTest);
	~CBurst();
public:
	//メンバ
	void Update() override;
	void Render() override;
};



#endif