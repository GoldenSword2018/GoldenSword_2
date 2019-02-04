//
//	GameScene.h
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

#pragma once
#ifndef GAMESCENE_H
#define GAMESCENE_H

//================================================
//	インクルード	include
//================================================
#include"common.h"

//Class
#include"Scene.h"

//================================================
//	クラス		class
//================================================

class GameScene : public NSCENE::AScene
{
public:
	GameScene() :AScene("Game") {};
public:
	void Initialize();
	void UpdateBegin();
	void Render();
	void UpdateEnd();
	void Finalize();
};

NSCENE::AScene* Get_GameScene();
int Get_GameTime();
#endif