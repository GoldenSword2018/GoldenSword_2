//
//	ResultScene.cpp
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
#include"ResultScene.h"
#include"TitleScene.h"

//class
#include"MeshField.h"
#include"CCamera.h"
#include"Fade.h"
#include"CUI.h"
#include"Debug_font.h"
#include"GameScene.h"
#include"Animation.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================
static ResultScene g_ResultScene;
static Camera MainCamera;
static NRender2D::UI::MouseUI* Result;
static NRender2D::CSprite* TexScore;
static NTexture::CAnimation AnimaScore(10,10,1);
static NTexture::NameTexture* ScoreTex;
//===============================================
//	クラス名		class
//===============================================

void ResultScene::Initialize()
{
	MainCamera.Set_Main();
	Result = new NRender2D::UI::MouseUI(
		new Transform2({ 500.0f,500.0f }, {400.0f,100.0f},0),
		new NTexture::PathTexture("ClickToTitle.png"),
		D3DCOLOR_RGBA(255,255,255,255)
	);
	TexScore = new NRender2D::CSprite(
		new Transform2({ WINDOWSCREEN_WIDTH_2,WINDOWSCREEN_HEIGHT_2 }, { 50,50 }, 0),
		new NTexture::NameTexture(NTexture::NumberTex, { 0.0f,0.0f }, {0.1f,1.0f}),
		D3DCOLOR_RGBA(255,255,255,255)
	);
	ScoreTex = new NTexture::NameTexture(NTexture::NumberTex, { 0.0f,0.0f }, { 0.1f,1.0f });

	Fade_Triger(false, 100.0f, D3DCOLOR_RGBA(255, 255, 255, 255));
}

void ResultScene::UpdateBegin()
{
	MainCamera.Update();

	if(Result->Click())
	{
		Fade_Triger(true,100.0f,D3DCOLOR_RGBA(0,0,0,255));
		NSCENE::LoadScene(Get_TitleScene());
	}
}

void ResultScene::Render()
{
	char text[100];
	sprintf(text,"TIME:%d", Get_GameTime());
	Animation_Score(TexScore->Transform(), ScoreTex,&AnimaScore,Get_GameTime(),true,false,4);
	DebugFont_Draw(WINDOWSCREEN_WIDTH_2,WINDOWSCREEN_HEIGHT_2,text);
	NMeshField::Render_Ground({0.0f,0.0f,0.0f}, NTexture::MeshFieldTex);
	Result->Render();
}

void ResultScene::UpdateEnd()
{

}

void ResultScene::Finalize()
{

}

NSCENE::AScene* Get_ResultScene()
{
	return &g_ResultScene;
}