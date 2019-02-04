//
//	TitleScene.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef TITLESCENE_H
#define TITLESCENE_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include"Scene.h"


//================================================
//	クラス		class
//================================================
class TitleScene : public NSCENE::AScene
{
public:
	TitleScene() :AScene("title") {};
public:
	void Initialize();
	void UpdateBegin();
	void Render();
	void UpdateEnd();
	void Finalize();
};

NSCENE::AScene* Get_TitleScene();

#endif