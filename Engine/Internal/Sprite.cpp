//
//	Sprite.cpp
//		Author:HIROMASA IKEDA	Date:2018/09/13
//===============================================
#define _USE_MATH_DEFINES
#include<math.h>

#include"Texture.h"
#include"Sprite.h"
#include"CTransform.h"
#include"System.h"

//===============================================
//	グローバル変数
//===============================================
static LPDIRECT3DDEVICE9 g_pD3DDevice	= NULL;

//===============================================
//	デバイス設定
//===============================================
void Sprite_SetDevice(LPDIRECT3DDEVICE9 pD3DDevice)
{
	g_pD3DDevice = pD3DDevice;
	return;
}

/*
//===============================================
//	ポリゴン
//===============================================
void Render2D_Porigon(Transform2* const pTransform2,const D3DCOLOR Color)
{
	float width		= pTransform2->Scale()->x * 0.5f;
	float height	= pTransform2->Scale()->y * 0.5f;

	D3DXVECTOR2* Position = pTransform2->Position();

	Vertex2D Porigon[4] =
	{
		{ D3DXVECTOR4(Position->x - width,Position->y - height,0.0f,1.0f),Color },
		{ D3DXVECTOR4(Position->x + width,Position->y - height,0.0f,1.0f),Color },
		{ D3DXVECTOR4(Position->x - width,Position->y + height,0.0f,1.0f),Color },
		{ D3DXVECTOR4(Position->x + width,Position->y + height,0.0f,1.0f),Color },
	};

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Porigon, sizeof(Porigon[0]));
}

//===============================================
//	ポリゴン回転
//===============================================
void Render2D_Porigon_Rotate(Transform2* const pTransform2,const D3DCOLOR Color)
{
	float width  = pTransform2->Scale()->x * 0.5f;
	float height = pTransform2->Scale()->y * 0.5f;

	float Rotation = pTransform2->Get_Rotation() * (float)M_PI / 180.0f;

	float px[4] = { 0 };
	float py[4] = { 0 };

	px[0] = (-width) * cosf(Rotation) - (-height) * sinf(Rotation);
	py[0] = (-width) * sinf(Rotation) + (-height) * cosf(Rotation);

	px[1] = width * cosf(Rotation) - (-height) * sinf(Rotation);
	py[1] = width * sinf(Rotation) + (-height) * cosf(Rotation);

	px[2] = (-width) * cosf(Rotation) - height * sinf(Rotation);
	py[2] = (-width) * sinf(Rotation) + height * cosf(Rotation);

	px[3] = width * cosf(Rotation) - height * sinf(Rotation);
	py[3] = width * sinf(Rotation) + height * cosf(Rotation);

	D3DXVECTOR2* Position = pTransform2->Position();

	Vertex2D Porigon[4] =
	{
		{ D3DXVECTOR4(px[0] + Position->x - 0.5f, py[0] + Position->y - 0.5f,	0.0f,1.0f),	Color},
		{ D3DXVECTOR4(px[1] + Position->x - 0.5f, py[1] + Position->y - 0.5f,	0.0f,1.0f),	Color},
		{ D3DXVECTOR4(px[2] + Position->x - 0.5f, py[2] + Position->y - 0.5f,	0.0f,1.0f),	Color},
		{ D3DXVECTOR4(px[3] + Position->x - 0.5f, py[3] + Position->y - 0.5f,	0.0f,1.0f),	Color}
	};

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Porigon, sizeof(Porigon[0]));

}

//===============================================
//	画像サイズ描画
//===============================================
void Render2D_Texture_Size(Transform2* const pTransform2,NTexture::Texture* const pTexture,const D3DCOLOR Color)
{
	float width  = pTexture->Width() *0.5f;
	float height = pTexture->Height() *0.5f;

	D3DXVECTOR2* Position = pTransform2->Position();

	TexVertex2D Sprite[4] = 
	{
		{ D3DXVECTOR4(Position->x - width - 0.5f, Position->y - height - 0.5f, 0.0f,1.0f),Color,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(Position->x + width - 0.5f, Position->y - height - 0.5f, 0.0f,1.0f),Color,D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(Position->x - width - 0.5f, Position->y + height - 0.5f, 0.0f,1.0f),Color,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(Position->x + width - 0.5f, Position->y + height - 0.5f, 0.0f,1.0f),Color,D3DXVECTOR2(1.0f,1.0f) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0,pTexture->lpTexture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	ポリゴンサイズに描画
//===============================================
void Render2D_Texture_Fill(Transform2* const pTransform2,NTexture::Texture* const pTexture,const D3DCOLOR Color) 
{
	float width  = pTransform2->Scale()->x *0.5f;
	float height = pTransform2->Scale()->y *0.5f;

	D3DXVECTOR2* Position = pTransform2->Position();

	TexVertex2D Sprite[4] =
	{
		{ D3DXVECTOR4(Position->x - width - 0.5f, Position->y - height - 0.5f, 0.0f,1.0f),Color,D3DXVECTOR2(0.0f,0.0f) },
		{ D3DXVECTOR4(Position->x + width - 0.5f, Position->y - height - 0.5f, 0.0f,1.0f),Color,D3DXVECTOR2(1.0f,0.0f) },
		{ D3DXVECTOR4(Position->x - width - 0.5f, Position->y + height - 0.5f, 0.0f,1.0f),Color,D3DXVECTOR2(0.0f,1.0f) },
		{ D3DXVECTOR4(Position->x + width - 0.5f, Position->y + height - 0.5f, 0.0f,1.0f),Color,D3DXVECTOR2(1.0f,1.0f) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, pTexture->lpTexture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	テクスチャの切り抜きサイズ
//===============================================
void Render2D_Texture_Clip(Transform2* const pTransform2,NTexture::Texture* const pTexture,const D3DCOLOR Color)
{
	float u0 = pTexture->TexCoord().x;
	float v0 = pTexture->TexCoord().y;
	float u1 = u0 + (float)pTexture->TexScale().x;
	float v1 = v0 + (float)pTexture->TexScale().y;

	float width = pTransform2->Scale()->x * 0.5f;
	float height = pTransform2->Scale()->y * 0.5f;

	D3DXVECTOR2* Position = pTransform2->Position();

	TexVertex2D Sprite[4] =
	{
		{ D3DXVECTOR4(Position->x - width - 0.5f, Position->y - height - 0.5f, 0.0f,1.0f), Color, D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(Position->x + width - 0.5f, Position->y - height - 0.5f, 0.0f,1.0f), Color, D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(Position->x - width - 0.5f, Position->y + height - 0.5f, 0.0f,1.0f), Color, D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(Position->x + width - 0.5f, Position->y + height - 0.5f, 0.0f,1.0f), Color, D3DXVECTOR2(u1,v1) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, pTexture->lpTexture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	スプライト描画
//===============================================
void Render2D_Sprite(Transform2* const pTransform2,NTexture::Texture* const pTexture,const D3DCOLOR Color )
{
	float u0 =		(float)pTexture->TexCoord().x; 
	float v0 =		(float)pTexture->TexCoord().y; 
	float u1 = u0 + (float)pTexture->TexScale().x; 
	float v1 = v0 + (float)pTexture->TexScale().y;

	float width  = pTransform2->Scale()->x * 0.5f;
	float height = pTransform2->Scale()->y * 0.5f;

	D3DXVECTOR2* Position = pTransform2->Position();

	TexVertex2D Sprite[4] =
	{
		{ D3DXVECTOR4(Position->x - width - 0.5f, Position->y - height - 0.5f, 0.0f,1.0f), Color, D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(Position->x + width - 0.5f, Position->y - height - 0.5f, 0.0f,1.0f), Color, D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(Position->x - width - 0.5f, Position->y + height - 0.5f, 0.0f,1.0f), Color, D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(Position->x + width - 0.5f, Position->y + height - 0.5f, 0.0f,1.0f), Color, D3DXVECTOR2(u1,v1) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, pTexture->lpTexture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	スプライト描画
//===============================================
void Render2D_Sprite_Rotate(Transform2* const pTransform2,NTexture::Texture* const pTexture,const D3DCOLOR Color)
{
	float u0 = pTexture->TexCoord().x;
	float v0 = pTexture->TexCoord().y;
	float u1 = u0 + pTexture->TexScale().x;
	float v1 = v0 + pTexture->TexScale().y;

	float width  = pTransform2->Scale()->x * 0.5f;
	float height = pTransform2->Scale()->y * 0.5f;

	float Rotation = pTransform2->Get_Rotation() * (float)M_PI / 180.0f;

	float px[4] = { 0 };
	float py[4] = { 0 };

	px[0] = (-width)*cosf(Rotation) - (-height) * sinf(Rotation);
	py[0] = (-width)*sinf(Rotation) + (-height) * cosf(Rotation);

	px[1] = width * cosf(Rotation) - (-height) * sinf(Rotation);
	py[1] = width * sinf(Rotation) + (-height) * cosf(Rotation);

	px[2] = (-width) * cosf(Rotation) - height * sinf(Rotation);
	py[2] = (-width) * sinf(Rotation) + height * cosf(Rotation);

	px[3] = width * cosf(Rotation) - height * sinf(Rotation);
	py[3] = width * sinf(Rotation) + height * cosf(Rotation);

	D3DXVECTOR2* Position = pTransform2->Position();

	TexVertex2D Sprite[4] =
	{
		{ D3DXVECTOR4(px[0] + Position->x - 0.5f, py[0] + Position->y - 0.5f, 0.0f,1.0f),Color,	D3DXVECTOR2(u0,v0) },
		{ D3DXVECTOR4(px[1] + Position->x - 0.5f, py[1] + Position->y - 0.5f, 0.0f,1.0f),Color,	D3DXVECTOR2(u1,v0) },
		{ D3DXVECTOR4(px[2] + Position->x - 0.5f, py[2] + Position->y - 0.5f, 0.0f,1.0f),Color,	D3DXVECTOR2(u0,v1) },
		{ D3DXVECTOR4(px[3] + Position->x - 0.5f, py[3] + Position->y - 0.5f, 0.0f,1.0f),Color,	D3DXVECTOR2(u1,v1) }
	};

	g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
	g_pD3DDevice->SetTexture(0, pTexture->lpTexture());
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));

}

//===============================================
//	円ポリゴン
//===============================================
void Render2D_Porigon_Circle(Transform2* const pTransform2, const float radius,const D3DCOLOR Color)
{
	float angle = 30;
	angle *= (float)M_PI / 180;

	Vertex2D Porigon[14];

	for (int i = 0; i < 14; i++)
	{
		if (i == 0)
		{
			Porigon[i].Position.x = pTransform2->Get_Position().x;
			Porigon[i].Position.y = pTransform2->Get_Position().y;
		}
		else
		{
			Porigon[i].Position.x = cosf((i - 1) * angle) * radius + pTransform2->Get_Position().x;
			Porigon[i].Position.y = sinf((i - 1) * angle) * radius + pTransform2->Get_Position().y;
		}

		Porigon[i].Position.z = 0.0f;
		Porigon[i].Position.w = 1.0f;
		Porigon[i].Color = Color;
	}

	g_pD3DDevice->SetFVF(FVF_VERTEX2D);
	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 12, &Porigon, sizeof(Porigon[0]));
}


//===============================================
//	ライン描画
//===============================================
void Render2D_Line(D3DXVECTOR2 Vector1, D3DXVECTOR2 Vector2)
{
	D3DXVECTOR2 Line[] = { Vector1,Vector2 };

	LPD3DXLINE pLine;
	D3DXCreateLine(g_pD3DDevice, &pLine);
	pLine->SetWidth(10.0f);					//線の太さ
	pLine->Begin();
	pLine->Draw(Line, 2, D3DCOLOR_RGBA(255, 0, 0, 255));
	pLine->End();
}
*/

//===============================================
//	名前空間
//===============================================
namespace NRender2D
{
	void Set_Device(LPDIRECT3DDEVICE9 pD3DDevice)
	{
		g_pD3DDevice = pD3DDevice;
		return;
	}

	//==============================================
	//	Vertex2D
	//==============================================
	void Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color)
	{
		float width = Scale.x * 0.5f - 0.5f;
		float height = Scale.y * 0.5f - 0.5f;

		Vertex2D Porigon[4] =
		{
			{ D3DXVECTOR4(Position.x - width,Position.y - height, 0.0f,1.0f),Color },
			{ D3DXVECTOR4(Position.x + width,Position.y - height, 0.0f,1.0f),Color },
			{ D3DXVECTOR4(Position.x - width,Position.y + height, 0.0f,1.0f),Color },
			{ D3DXVECTOR4(Position.x + width,Position.y + height, 0.0f,1.0f),Color }
		};

		g_pD3DDevice->SetFVF(FVF_VERTEX2D);
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Porigon, sizeof(Porigon[0]));
	}

	//------------------------------------
	//	回転
	//------------------------------------
	void  Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, float Rotate)
	{
		float width = Scale.x * 0.5f;
		float height = Scale.y * 0.5f;

		float Rotation = Rotate * (float)M_PI / 180.0f;

		float px[4] = { 0 };
		float py[4] = { 0 };

		px[0] = (-width)*cosf(Rotation) - (-height) * sinf(Rotation);
		py[0] = (-width)*sinf(Rotation) + (-height) * cosf(Rotation);

		px[1] = width * cosf(Rotation) - (-height) * sinf(Rotation);
		py[1] = width * sinf(Rotation) + (-height) * cosf(Rotation);

		px[2] = (-width) * cosf(Rotation) - height * sinf(Rotation);
		py[2] = (-width) * sinf(Rotation) + height * cosf(Rotation);

		px[3] = width * cosf(Rotation) - height * sinf(Rotation);
		py[3] = width * sinf(Rotation) + height * cosf(Rotation);

		Vertex2D Sprite[4] =
		{
			{ D3DXVECTOR4(px[0] + Position.x - 0.5f, py[0] + Position.y - 0.5f, 0.0f,1.0f), Color },
			{ D3DXVECTOR4(px[1] + Position.x - 0.5f, py[1] + Position.y - 0.5f, 0.0f,1.0f), Color },
			{ D3DXVECTOR4(px[2] + Position.x - 0.5f, py[2] + Position.y - 0.5f, 0.0f,1.0f), Color },
			{ D3DXVECTOR4(px[3] + Position.x - 0.5f, py[3] + Position.y - 0.5f, 0.0f,1.0f), Color }
		};

		g_pD3DDevice->SetFVF(FVF_VERTEX2D);
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));
	}

	//==============================================
	//	TexVertex2D
	//==============================================
	void Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 origin, D3DXVECTOR2 uv)
	{
		float width		= Scale.x * 0.5f -0.5f;
		float height	= Scale.y * 0.5f -0.5f;

		TexVertex2D Sprite[4] =
		{
			{ D3DXVECTOR4(Position.x - width, Position.y - height,0.0f,1.0f),Color,	origin },
			{ D3DXVECTOR4(Position.x + width, Position.y - height,0.0f,1.0f),Color,	D3DXVECTOR2(origin.x + uv.x,origin.y) },
			{ D3DXVECTOR4(Position.x - width, Position.y + height,0.0f,1.0f),Color,	D3DXVECTOR2(origin.x,origin.y + uv.y) },
			{ D3DXVECTOR4(Position.x + width, Position.y + height,0.0f,1.0f),Color,	origin + uv }
		};

		g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
		g_pD3DDevice->SetTexture(0, pTexture);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));
	}

	//------------------------------------
	//	回転させる
	//------------------------------------
	void Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 origin, D3DXVECTOR2 uv, float Rotate)
	{
		float width = Scale.x * 0.5f;
		float height = Scale.y * 0.5f;

		float Rotation = Rotate * (float)M_PI / 180.0f;

		float px[4] = { 0 };
		float py[4] = { 0 };

		px[0] = (-width)*cosf(Rotation) - (-height) * sinf(Rotation);
		py[0] = (-width)*sinf(Rotation) + (-height) * cosf(Rotation);

		px[1] = width * cosf(Rotation) - (-height) * sinf(Rotation);
		py[1] = width * sinf(Rotation) + (-height) * cosf(Rotation);

		px[2] = (-width) * cosf(Rotation) - height * sinf(Rotation);
		py[2] = (-width) * sinf(Rotation) + height * cosf(Rotation);

		px[3] = width * cosf(Rotation) - height * sinf(Rotation);
		py[3] = width * sinf(Rotation) + height * cosf(Rotation);

		TexVertex2D Sprite[4] =
		{
			{ D3DXVECTOR4(px[0] + Position.x - 0.5f, py[0] + Position.y - 0.5f, 0.0f,1.0f), Color,	origin },
			{ D3DXVECTOR4(px[1] + Position.x - 0.5f, py[1] + Position.y - 0.5f, 0.0f,1.0f), Color,	D3DXVECTOR2(origin.x + uv.x,origin.y) },
			{ D3DXVECTOR4(px[2] + Position.x - 0.5f, py[2] + Position.y - 0.5f, 0.0f,1.0f), Color,	D3DXVECTOR2(origin.x,origin.y + uv.y) },
			{ D3DXVECTOR4(px[3] + Position.x - 0.5f, py[3] + Position.y - 0.5f, 0.0f,1.0f), Color,	origin + uv }
		};

		g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
		g_pD3DDevice->SetTexture(0, pTexture);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Sprite, sizeof(Sprite[0]));
	}


	void Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, float Rotate)
	{
		Sprite(Position, Scale, D3DCOLOR_RGBA(255, 255, 255, 255), Rotate);
	}

	//一枚テクスチャ
	void Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, LPDIRECT3DTEXTURE9 pTexture)
	{
		NRender2D::Sprite(Position, Scale, D3DCOLOR_RGBA(255, 255, 255, 255), pTexture, { 0.0f,0.0f }, { 1.0f, 1.0f });
	}

	//一枚テクスチャ
	void Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, LPDIRECT3DTEXTURE9 pTexture)
	{
		NRender2D::Sprite(Position, Scale, Color, pTexture, { 0.0f,0.0f }, { 1.0f, 1.0f });
	}

	void Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale)
	{
		Sprite(Position, Scale, D3DCOLOR_RGBA(255, 255, 255, 255));
	}

	void Sprite(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, LPDIRECT3DTEXTURE9 pTexture, float Rotate)
	{
		Sprite(Position, Scale, Color, pTexture, { 0.0f,0.0f }, { 1.0f,1.0f }, Rotate);
	}

	//===============================================
	//	ポリゴン
	//===============================================
	void Sprite(Transform2* const pTransform2,const D3DCOLOR Color)
	{
		Sprite(pTransform2->Get_Position(),pTransform2->Get_Scale(),Color);
	}

	//===============================================
	//	ポリゴン回転
	//===============================================
	void Sprite_Rotate(Transform2* const pTransform2,const D3DCOLOR Color)
	{
		Sprite(pTransform2->Get_Position(), pTransform2->Get_Scale(), Color,pTransform2->Get_Rotation());
	}

	//===============================================
	//	画像サイズ描画
	//===============================================
	void Sprite_TexSize(Transform2* const pTransform2, NTexture::Texture* const pTexture,const D3DCOLOR Color)
	{
		D3DXVECTOR2 Scale(pTexture->Width() * 0.5f, pTexture->Height() *0.5f);
		Sprite(pTransform2->Get_Position(), Scale, Color);
	}

	//===============================================
	//	ポリゴンサイズに描画
	//===============================================
	void Sprite_TexFill(Transform2* const pTransform2, NTexture::Texture* const pTexture,const D3DCOLOR Color)
	{
		Sprite(pTransform2->Get_Position(), pTransform2->Get_Scale(), Color, pTexture->lpTexture());
	}

	//===============================================
	//	テクスチャの切り抜きサイズ
	//===============================================
	void Sprite(Transform2* const pTransform2, NTexture::Texture* const pTexture,const D3DCOLOR Color)
	{
		NRender2D::Sprite(pTransform2->Get_Position(), pTransform2->Get_Scale(), Color, pTexture->lpTexture(), pTexture->TexCoord(), pTexture->TexScale());
	}

	//===============================================
	//	スプライト描画
	//===============================================
	void Sprite_Rotate(Transform2* const pTransform2, NTexture::Texture* const pTexture,const D3DCOLOR Color)
	{
		int i = 0;
		Sprite(pTransform2->Get_Position(), pTransform2->Get_Scale(), Color, pTexture->lpTexture(), pTexture->TexCoord(), pTexture->TexScale(),pTransform2->Get_Rotation());
	}

	//==============================================
	//	その他
	//==============================================
	void Line(D3DXVECTOR2 Vector1, D3DXVECTOR2 Vector2,D3DCOLOR Color,float Width)
	{
		D3DXVECTOR2 Line[2] = { Vector1,Vector2 };

		LPD3DXLINE pLine;
		D3DXCreateLine(g_pD3DDevice, &pLine);
		pLine->SetWidth(Width);					//線の太さ
		pLine->Begin();
		pLine->Draw(Line, 2, Color);
		pLine->End();
	}

	//------------------------------------
	//	円
	//------------------------------------
	void Circle(D3DXVECTOR2 Position, D3DCOLOR Color, float radius)
	{
		float angle = 30;
		angle *= (float)M_PI / 180;

		Vertex2D Porigon[14];

		for (int i = 0; i < 14; i++)
		{
			if (i == 0)
			{
				Porigon[i].Position.x = Position.x;
				Porigon[i].Position.y = Position.y;
			}
			else
			{
				Porigon[i].Position.x = cosf((i - 1) * angle) * radius + Position.x;
				Porigon[i].Position.y = sinf((i - 1) * angle) * radius + Position.y;
			}

			Porigon[i].Position.z = 0.0f;
			Porigon[i].Position.w = 1.0f;
			Porigon[i].Color = Color;
		}

		g_pD3DDevice->SetFVF(FVF_VERTEX2D);
		g_pD3DDevice->SetTexture(0, NULL);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 12, &Porigon, sizeof(Porigon[0]));
	}

	//------------------------------------
	//	円
	//------------------------------------
	void Circle(D3DXVECTOR2 Position, D3DCOLOR Color, float radius, PDIRECT3DTEXTURE9* pTexture, D3DXVECTOR2 origin, float texRadius)
	{
		float angle = 30;
		angle *= (float)M_PI / 180;

		TexVertex2D Porigon[14];

		for (int i = 0; i < 14; i++)
		{
			if (i == 0)
			{
				Porigon[i].Position.x = Position.x;
				Porigon[i].Position.y = Position.y;
				Porigon[i].TexCoord.x = origin.x;
				Porigon[i].TexCoord.y = origin.y - texRadius;
			}
			else
			{
				Porigon[i].Position.x = cosf((i - 1) * angle) * radius + Position.x;
				Porigon[i].Position.y = sinf((i - 1) * angle) * radius + Position.y;
				Porigon[i].TexCoord.x = cosf((i - 1) * angle) * texRadius + origin.x;
				Porigon[i].TexCoord.y = sinf((i - 1) * angle) * texRadius + origin.y;
			}

			Porigon[i].Position.z = 0.0f;
			Porigon[i].Position.w = 1.0f;
			Porigon[i].Color = Color;
		}

		g_pD3DDevice->SetFVF(FVF_TEXVERTEX2D);
		g_pD3DDevice->SetTexture(0, *pTexture);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLEFAN, 12, &Porigon, sizeof(Porigon[0]));
	}

}