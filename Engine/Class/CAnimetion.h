//
//	CAnimetion.h
//		Author:HIROMASA IKEDA		DATE:2018/09/28
//===============================================
#pragma once
#ifndef ANIMETIONCLASS_H
#define ANIMETIONCLASS_H

#include"common.h"
#include"Texture.h"
#include"CTransform.h"

//===============================================
//	Animetion : 2D専用　クラス	
//===============================================
class Animetion
{
private:

public:
	int AnimePatern;			//アニメーション
	int MaxPatern;				//最大アニメーション
	int YMaxPatern;				//横最大アニメーション
	int Waitframe;				//アニメーション速度
	int Createframe;			//生成された時のフレーム

	//コンストラクタ
	Animetion();
	Animetion(int MaxPatern,int YMaxPatern,int Waitframe);
};

#endif // !ANIMETIONCLASS_H

