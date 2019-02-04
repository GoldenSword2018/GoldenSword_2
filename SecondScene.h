//
//	SecondScene.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef IKEDA_TEMPCLASS_H
#define IKEDA_TEMPCLASS_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include"Scene.h"
//================================================
//	クラス		class
//================================================

class SecondScene : public NSCENE::AScene
{
public:
	SecondScene() :AScene("Second") {};
public:
	void Initialize();
	void UpdateBegin();
	void Render();
	void UpdateEnd();
	void Finalize();
};

NSCENE::AScene* Get_SecondScene();

#endif