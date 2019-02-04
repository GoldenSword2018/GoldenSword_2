//
//	Title.cpp
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

#include"TitleScene.h"

//class
#include"CRender.h"
#include"CMesh.h"
#include"CCamera.h"
#include"Input.h"

#include"Fade.h"

#include"Debug_font.h"
#include"CGameObject.h"
#include"CCamera.h"
#include"CUI.h"

//Scene
#include"GameScene.h"

//===============================================
//	マクロ定義		define
//===============================================
class Object
{
public:
	CXModelMesh model;
	CTransform transform;
};

//===============================================
//	グローバル変数	global
//===============================================
static TitleScene g_Title;	//タイトルScene
static Camera MainCamera;

//Assets
static NRender2D::UI::MouseUI* GameStart;
static NRender2D::CSprite* TitleImage;

//===============================================
//	関数
//===============================================
void TitleScene::Initialize()
{
	MainCamera.Set_Main();
	//Assets
	GameStart = new NRender2D::UI::MouseUI(
		new Transform2({ 150.0f,450.0f }, { 200.0f,100.0f }, 0.0f),
		new NTexture::PathTexture("GameStart.png"),
		D3DCOLOR_RGBA(255,255,255,255)
	);

	TitleImage = new NRender2D::CSprite(
		new Transform2({ WINDOWSCREEN_WIDTH_2,WINDOWSCREEN_HEIGHT_2 }, { WINDOWSCREEN_WIDTH,WINDOWSCREEN_HEIGHT }, 0),
		new NTexture::PathTexture("Title.png"),
		D3DCOLOR_RGBA(255,255,255,255)
	);

	Fade_Triger(false, 10, D3DCOLOR_RGBA(0, 0, 0, 255));
}

void TitleScene::UpdateBegin()
{

	MainCamera.Update();
	if(GameStart->Click())
	{
		NSCENE::LoadScene(Get_GameScene());
		Fade_Triger(true,10,D3DCOLOR_RGBA(255,255,255,255));
	}
}

void TitleScene::Render()
{
	TitleImage->Render();
	GameStart->Render();
}

void TitleScene::UpdateEnd()
{

}

void TitleScene::Finalize()
{
	delete GameStart;
}

NSCENE::AScene* Get_TitleScene()
{
	return &g_Title;
}
