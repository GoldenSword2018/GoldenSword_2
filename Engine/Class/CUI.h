//
//	UI.h
//		Author:HIROMASA IKEDA	DATE:2018/08/28
//===============================================
#pragma once

#ifndef UI_H
#define UI_H

#include<d3dx9.h>
#include"CTransform.h"
#include"Sprite.h"
#include"CSprite.h"

namespace NRender2D
{
	namespace UI
	{
		//=============================================
		//	関数
		//=============================================
		void BarIndicator(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR BackColor, D3DCOLOR LineColor, float Score, float MaxScore);
		void CircleIndicator(D3DXVECTOR2 Position, D3DCOLOR BackColor, D3DCOLOR LineColor, float radius, float width, float Score, float MaxScore);

		//=============================================
		//	MouseUI
		//=============================================
		class  MouseUI:public virtual CSprite
		{
		public:
			MouseUI(Transform2* transform, NTexture::Texture* texture, D3DCOLOR Color);
		public:
			bool Click();
			bool Hover();
		};
	}
}

/*
//===============================================
//	UI クラス
//===============================================
class UI : public Sprite
{
private:
	
public:

	//コンストラクタ
	UI(Transform2* pTransform2, NTexture::CTexture* pTexture);
	UI(Transform2* pTransform2, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation);

	void Set(Transform2* pTransform2);
	bool Click();	//クリック時
	bool Hover();	//ホバー時
};
*/
#endif // !UI_H
