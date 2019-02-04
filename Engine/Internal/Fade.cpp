//
//	Fade.cpp
//		USER:HIROMASA IKEDA		DATE:2018/07/11
//===============================================
#include<d3dx9.h>
#include"common.h"
#include"Fade.h"
#include"System.h"
#include"Sprite.h"

typedef struct DebugVertex_tag
{
	D3DXVECTOR4 Position;
	D3DCOLOR	Color;

}FadeVertex;

typedef struct Vertex2D_tag		FadeVertex2D;
typedef struct TexVertex2D_tag	FadeTexVertex2D;

#define FVF_FADE_VERTEX (D3DFVF_XYZRHW | D3DFVF_DIFFUSE)

static D3DXCOLOR g_FadeColor(1.0f, 1.0f, 1.0f, 1.0f);
static float	g_Alpha = 1.0f;
static float	g_AddAlpha = 0.0f;		
static bool		g_bOut = false;			//false フェードアウト　ture フェードイン
static bool		g_bIsFade = false;

void Fade_Initialize() 
{
	g_bOut = false;
	g_bIsFade = false;
	g_AddAlpha = 0;
	g_Alpha = 0;
	g_FadeColor.a = g_Alpha;
}

void Fade_Update() 
{
	if (!g_bIsFade) return;

	g_Alpha += g_AddAlpha;


	if (g_bOut)
	//フェードイン
	{
		if (g_Alpha >= 1.0f) 
		{
			g_bIsFade = false;
			g_Alpha = 1.0f;

		}
	}
	//フェードアウト
	else
	{
		if (g_Alpha <= 0.0f) 
		{
			g_bIsFade = false;
			g_Alpha = 0.0f;
		}
	}
}

void Fade_Render() 
{
	
	if (g_Alpha <= 0.0f) 
	{
		return;
	}

	g_FadeColor.a = g_Alpha;

	FadeVertex Vertex[4] =
	{
		{ D3DXVECTOR4(0.0f,					0.0f,					0.0f,1.0f), g_FadeColor },
		{ D3DXVECTOR4(WINDOWSCREEN_WIDTH,	0.0f,					0.0f,1.0f), g_FadeColor },
		{ D3DXVECTOR4(0.0f,					WINDOWSCREEN_HEIGHT,	0.0f,1.0f), g_FadeColor },
		{ D3DXVECTOR4(WINDOWSCREEN_WIDTH,	WINDOWSCREEN_HEIGHT,	0.0f,1.0f), g_FadeColor }
	};

	System_GetDevice()->SetFVF(FVF_FADE_VERTEX);
	System_GetDevice()->SetTexture(0, NULL);
	System_GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,&Vertex,sizeof(Vertex[0]));

}

void Fade_Triger(bool bOut,int frame,D3DCOLOR Color) 
{
	g_bOut = bOut;

	g_AddAlpha = 1.0f / frame;
	g_FadeColor = Color;
	g_bIsFade = true;

	//フェードイン
	if (g_bOut)	
	{
		g_Alpha = 0.0f;
	}
	//フェードアウト
	else 
	{
		g_Alpha = 1.0f;
		g_AddAlpha = -g_AddAlpha;
	}
}

bool Fade_IsFade() 
{
	return g_bIsFade;
}

//フェードインしているか
bool Fade_Alpha()
{
	return (g_Alpha >= 1.0f) ? true : false;
}
