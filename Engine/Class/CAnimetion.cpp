//
//	CAnimetion.cpp
//		Author:HIROMASA IKEDA	DATE:2018/09/28
//===============================================
#include<d3dx9.h>
#include"CTransform.h"
#include"Animetion.h"
#include"CAnimetion.h"

//===============================================
//	Animetion クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
Animetion::Animetion()
{
	AnimePatern = 0;
	MaxPatern = 0;
	YMaxPatern = 0;
	Waitframe = 0;
	Createframe = Animetion_GetFrame();
}

Animetion::Animetion(int MaxPatern, int YMaxPatern, int Waitframe)
{
	AnimePatern = 0;
	this->MaxPatern = MaxPatern;
	this->YMaxPatern = YMaxPatern;
	this->Waitframe = Waitframe;
	Createframe = Animetion_GetFrame();
}