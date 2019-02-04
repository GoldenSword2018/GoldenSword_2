//
//	Animetion.h
//		USER:HIROMASA IKEDA		DATE:2018/09/28
//===============================================
#pragma once
#ifndef ANIMETION_H
#define ANIMETION_H

#include<d3dx9.h>

#include"common.h"
#include"CTransform.h"
#include"Texture.h"
#include"Sprite.h"

//===============================================
//	–¼‘O‹óŠÔ
//===============================================	
namespace NTexture
{
	void FrameInit();
	void FrameUpdate();
	int Get_Frame();

	int Animation(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 origin, D3DXVECTOR2 uv, int MaxPatern, int YMaxPatern, int Waitframe, int Createframe, bool loop);
	int Animation(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR Color, LPDIRECT3DTEXTURE9 pTexture, D3DXVECTOR2 origin, D3DXVECTOR2 uv, int MaxPatern, int YMaxPatern, int Waitframe, int Createframe, float Rotate, bool loop);
}

void Animation_Score(Transform2* pTransform, NTexture::NameTexture* pTexture, NTexture::CAnimation* pAnimetion, int Score, bool bLeft, bool bZero, int digitNum);
#endif

