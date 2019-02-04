//
//	Animetion.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#include<d3dx9.h>
#include<math.h>

#include"Texture.h"
#include"CTransform.h"
#include"Animation.h"

//==============================================
//	グローバル変数宣言
//==============================================
static int g_FrameCounter;	//・フレームカウンタ

namespace NTexture
{
	//------------------------------------
	//	Initialize()
	//------------------------------------
	void FrameInit()
	{
		g_FrameCounter = 0;
	}

	//------------------------------------
	//	FrameUpdate()
	//------------------------------------
	void FrameUpdate()
	{
		g_FrameCounter++;
	}

	//------------------------------------
	//	Get_Frame()
	//------------------------------------
	int Get_Frame()
	{
		return g_FrameCounter;
	}

	//------------------------------------
	//	アニメーション
	//------------------------------------
	int Animation(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 origin, D3DXVECTOR2 uv, int MaxPatern, int YMaxPatern, int Waitframe, int Createframe, bool loop)
	{
		int Patern;
		if (loop)
		{
			Patern = (g_FrameCounter - Createframe / Waitframe % MaxPatern);
		}
		else
		{
			Patern = min((g_FrameCounter - Createframe / Waitframe),MaxPatern);
		}
		origin += {uv.x * (Patern % YMaxPatern),uv.y * (Patern / YMaxPatern)};
		NRender2D::Sprite(Position,Scale,Color,pTexture,origin,uv);
		return Patern;
	}

	//------------------------------------
	//	回転アニメーション
	//------------------------------------
	int Animation(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 origin, D3DXVECTOR2 uv, int MaxPatern, int YMaxPatern, int Waitframe, int Createframe,float Rotate ,bool loop)
	{
		int Patern;
		if (loop)
		{
			Patern = (g_FrameCounter - Createframe / Waitframe % MaxPatern);
		}
		else
		{
			Patern = min((g_FrameCounter - Createframe / Waitframe), MaxPatern);
		}
		origin += {uv.x * (Patern % YMaxPatern), uv.y * (Patern / YMaxPatern)};
		NRender2D::Sprite(Position, Scale, Color, pTexture, origin, uv,Rotate);
		return Patern;
	}

}

/*
//===============================================
//	アニメーション NOLOOP
//===============================================
bool Animation_NoLoop(Transform2* pTransform,NTexture::CTexture* pTexture,NTexture::CAnimation* pAnimetion)
{
	float width  = (float)pTexture->Get_Width();
	float height = (float)pTexture->Get_Height();

	pAnimetion->AnimaPatern  = min((g_FrameCounter / pAnimetion->Waitframe),pAnimetion->MaxPatern);

	NTexture::CTexture Tex = *pTexture;
	Tex.Coord = { pTexture->Scale.x * (pAnimetion->AnimaPatern % pAnimetion->YMaxPatern),pTexture->Scale.y * (pAnimetion->AnimaPatern / pAnimetion->YMaxPatern) };
	Render2D_Texture_Clip(pTransform,&Tex);

	return pAnimetion->AnimaPatern >= pAnimetion->MaxPatern;
}

//===============================================
//	アニメーション LOOP
//===============================================
void Animation_Loop(Transform2* pTransform,NTexture::CTexture* pTexture,NTexture::CAnimation* pAnimetion)
{
	float width  = (float)pTexture->Get_Width();
	float height = (float)pTexture->Get_Height();

	pAnimetion->AnimaPatern = (g_FrameCounter / pAnimetion->Waitframe) % pAnimetion->MaxPatern;

	NTexture::CTexture Tex = *pTexture;
	Tex.Coord = { pTexture->Scale.x * (pAnimetion->AnimaPatern % pAnimetion->YMaxPatern),pTexture->Scale.y * (pAnimetion->AnimaPatern / pAnimetion->YMaxPatern) };
	Render2D_Texture_Clip(pTransform,&Tex);
}

//===============================================
//	回転アニメーション
//===============================================
void Animation_Loop_Rotate(Transform2* pTransform,NTexture::CTexture* pTexture,NTexture::CAnimation* pAnimetion)
{
	float width  = (float)pTexture->Get_Width();
	float height = (float)pTexture->Get_Height();

	pAnimetion->AnimaPatern = (g_FrameCounter / pAnimetion->Waitframe) % pAnimetion->MaxPatern;

	NTexture::CTexture Tex = *pTexture;
	Tex.Coord = { pTexture->Scale.x * (pAnimetion->AnimaPatern % pAnimetion->YMaxPatern),pTexture->Scale.y * (pAnimetion->AnimaPatern / pAnimetion->YMaxPatern) };
	Render2D_Sprite_Rotate(pTransform,&Tex);
}


//===============================================
//	スコアアニメーション
//===============================================
*/

void Animation_Score(Transform2* pTransform,NTexture::NameTexture* pTexture,NTexture::CAnimation* pAnimetion, int Score, bool bLeft, bool bZero, int digitNum)
{
	int digit = 0, MaxScore = 1;
	D3DXVECTOR2 AnimaTex = {};

	//桁取得
	for (digit = 0; digit < digitNum; digit++)
	{
		MaxScore *= 10;
	}

	//カウントオーバー
	if (Score >= MaxScore)
	{
		Score = MaxScore - 1;
	}

	//左詰め
	if (bLeft)
	{
		//桁数取得
		digit = 0;
		for (int score = Score; score > 0; digit++)
		{
			score /= 10;
		}

		//左詰め
		D3DXVECTOR2 position = { pTransform->Position()->x + (pTransform->Scale()->x * 0.5f) * digit,pTransform->Position()->y };
		while (digit > 0)
		{
			Transform2 transform2 = *pTransform;
			NTexture::NameTexture AnimaTex = *pTexture;
			int AnimePatern = Score % 10;
			AnimaTex.Coord = { pTexture->Scale.x * (AnimePatern % pAnimetion->YMaxPatern), pTexture->Scale.y *(AnimePatern / pAnimetion->YMaxPatern) };
			transform2.Set_Position({ position.x + (pTransform->Get_Scale().x) * digit,position.y });
			NRender2D::Sprite(&transform2,&AnimaTex,D3DCOLOR_RGBA(255,255,255,255));
			Score /= 10;
			digit--;
		}
	}
	//右詰め
	else
	{
		//位置決め
		D3DXVECTOR2 position( (pTransform->Scale()->x * 0.7f) * digit,pTransform->Position()->y );

		//0埋め
		if (!bZero)
		{
			digit = 0;
			int score = Score;
			do
			{
				score /= 10;
				digit++;
			} while (score > 0);
		}
		//右詰め
		while (digit > 0)
		{
			Transform2 transform2 = *pTransform;
			NTexture::NameTexture AnimaTex = *pTexture;
			
			int AnimaPatern = Score % 10;
			AnimaTex.Coord = { pTexture->Scale.x * (AnimaPatern % pAnimetion->YMaxPatern),pTexture->Scale.y *(AnimaPatern / pAnimetion->YMaxPatern) };
			transform2.Set_Position({ position.x - (pTransform->Get_Scale().x * 0.75f),position.y });
			NRender2D::Sprite(&transform2, &AnimaTex, D3DCOLOR_RGBA(255, 255, 255, 255));
			Score /= 10;
			digit--;
		}
	}
}


