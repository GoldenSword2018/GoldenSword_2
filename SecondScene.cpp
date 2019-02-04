//
//	Second.cpp
//		Author:	DATE:
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"common.h"

//class
#include"SecondScene.h"
#include"TitleScene.h"

#include"CCamera.h"
#include"Input.h"

#include"Sprite.h"
#include"CUI.h"
#include"Debug_font.h"
#include"system_timer.h"
#include"Lighting.h"

#include"Fade.h"

//===============================================
//	マクロ定義		define
//===============================================

//===============================================
//	Class
//===============================================

//===============================================
//	グローバル変数	global
//===============================================
static SecondScene			Second;
static OperationCamera		MainCamera;
static NTexture::Texture*	texture;
static Transform2*			transform;
static NRender2D::CSprite*	sprite;
static NRender2D::UI::MouseUI*	Clicks;
float rotate;
float State;

enum eTexture
{
	TEX_NONE = 0,
	INDEX_END
};

static NTexture::Data Index[INDEX_END]
{
	{TEX_NONE,"none.png"}
};

//===============================================
//	関数
//===============================================
void SecondScene::Initialize()
{
	State = 100.0f;
	SystemTimer_Start();

	NTexture::Load_Index(Index,INDEX_END);

	texture		= new NTexture::PathTexture("none.png");
	transform	= new Transform2
	(
		{ 200.0f,100.0f }, {50.0f,50.0f},0
	);

	sprite = new NRender2D::CSprite
	(
		new Transform2({ 300.0f,100.0f }, { 100.0f,100.0f }, 0),
		new NTexture::CTexture(&Index[TEX_NONE], 0,0,256,256),
		D3DCOLOR_RGBA(255, 255, 255, 255)
	);

	Clicks = new NRender2D::UI::MouseUI(
		new Transform2({ 400.0f,100.0f }, { 100.0f,100.0f }, 0),
		new NTexture::CTexture(&Index[TEX_NONE], 0, 0, 256, 256),
		D3DCOLOR_RGBA(255, 255, 255, 255)
	);

	MainCamera.Set_Main();
	rotate = 0.0f;
}

void SecondScene::UpdateBegin()
{
	MainCamera.Update();
	
	State -= 0.1f;

	rotate += 0.1f;
	*sprite->Transform()->Rotation() += 0.5f;

	if (Clicks->Click())
	{
		Fade_Triger(true,100.0f,D3DCOLOR_RGBA(255,255,255,0));
		NSCENE::LoadScene(Get_TitleScene());
	}
}

void SecondScene::Render()
{
	NRender2D::Sprite({100.0f,100.0f}, {50.0f,50.0f},rotate);
	NRender2D::Sprite(transform, texture,D3DCOLOR_RGBA(255,255,255,255));
	//NRender2D::Sprite(sprite.Transform(),sprite.Texture(),sprite.Get_Color());
	sprite->Render();
	Clicks->Render();
	NRender2D::UI::BarIndicator({ 300.0f,200.0f }, {300.0f,50.0f},D3DCOLOR_RGBA(255,255,255,255),D3DCOLOR_RGBA(255,0,0,255),State,100.0f);
	NRender2D::UI::CircleIndicator({ 300.0f,400.0f }, D3DCOLOR_RGBA(255, 255, 255, 255), D3DCOLOR_RGBA(255, 0, 0, 100), 50.0f, 50.0f, State, 100.0f);
	
	char text[256];
	sprintf(text,"タイム:%f",SystemTimer_GetTime());
	DebugFont_Draw(500,500,text);
}

void SecondScene::UpdateEnd()
{

}

void SecondScene::Finalize()
{
	SystemTimer_Reset();
	delete texture;
	delete sprite;
}

NSCENE::AScene* Get_SecondScene()
{
	return &Second;
}