//
//	Main.cpp
//		Author:HIROMASA IKEDA		Date:2018/10/22
//================================================
#include"common.h"
#include<time.h>
#include<math.h>
#include"System.h"
#include"input.h"

#include"Lighting.h"
#include"XModel.h"

#include"Billboard.h"
#include"Fade.h"

//Class
#include"CUI.h"
#include"CGameObject.h"
#include"CCamera.h"

#include"CTransform.h"

#include"WinSock.h"
#include"Grid.h"
#include"Animation.h"

#include"MeshField.h"
#include"FbxModel.h"

//Scene
#include"Scene.h"
#include"GameScene.h"
#include"TitleScene.h"
#include"SecondScene.h"

//===============================================
//	グローバル変数
//===============================================

//カメラ
static OperationCamera g_Camera(
	{0,5,5}
);

static NTexture::NameTexture texture(NTexture::Billboard_Burst);
static NTexture::CAnimation animation(18,6,4);

//=============================================================
//	初期化処理
//=============================================================
void Main_Initialize(void)
{
	texture.Clip(0,0,128,128);
	Billboard_Initialize();
	NModel::Initialize();
	Fade_Initialize();

	//g_Camera.Set_Main();
	
	//Grid_Initialize();
	NMeshField::Initialize();
	//fbx::Initialize();
	//fbx::Finalize();

	//最初のシーン読み込み
	NSCENE::LoadScene(Get_TitleScene());

	//初期化
	NSCENE::Initialize();
}

//=============================================================
//	前 更新処理
//=============================================================
void Main_UpdateBegin(void)
{
	Fade_Update();

	if(Fade_IsFade())return;

	//フェードイン無動作//

	NTexture::FrameUpdate();

	ABillboard::g_Update();

	
	//	カメラの向きで移動するやつ
	//----------------------------------------------
	//g_Camera.Update();

	NSCENE::UpdateBegin();
}

//=============================================================
//	描画処理
//=============================================================
void Main_Render(void)
{
	ACamera::Begin();		//描画開始
	ABillboard::g_Render();

	//Grid_Render();
	NSCENE::Render();

	Fade_Render();
}


//=============================================================
//	後 処理
//=============================================================
void Main_UpdateEnd()
{
	NSCENE::Check();
	if (Fade_IsFade())return;
	//NSCENE::Check();
	NSCENE::UpdateEnd();
	

}

//=============================================================
//	終了処理
//=============================================================
void Main_Finalize(void)
{
	NSCENE::Finalize();
	BillBoard_Finalaize();
	NMeshField::Finalize();
	NModel::Finalize();
}
