//
//	Score.cpp
//		Author:	ハンコウ DATE:2019/02/5
//===============================================
//	変更者 Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	インクルード	include
//===============================================
#include"Score.h"
#include"Texture.h"
#include"Sprite.h"

//===============================================
//	マクロ定義		define
//===============================================


//===============================================
//	グローバル変数	global
//===============================================


//------------------------------------
//	初期化
//------------------------------------
void Score_Initialize(void)
{
	g_score = 0;
}

//------------------------------------
//	描画
//------------------------------------
void Score_Render(void)
{
	int score = g_score;
	for (int i = 0; i < FIG; i++)
	{
		int number = score % 10;
		score /= 10;
		Number_Render({SCORE_X + (NTexture::Get_Width(NTexture::ScoreTex)*0.1f) * (FIG - (i + 1)), SCORE_Y}, number);
	}
}

//------------------------------------
//	スコア加算
//------------------------------------
void Score_Plus(int Item)
{
	g_score += Item; //スコアにバラバラしたブロック数を加算
}

//------------------------------------
//	数字描画
//------------------------------------
void Number_Render(D3DXVECTOR2 Position, int Number)
{
	float tx;
	tx = (float)Number / 10;
	NRender2D::Sprite(Position, D3DXVECTOR2(100.0f,100.0f),D3DCOLOR_RGBA(255,255,255,255), NTexture::Get_Texture(NTexture::ScoreTex), D3DXVECTOR2(tx,0), D3DXVECTOR2(0.1,1));
}

//------------------------------------
//	スコアリターン
//------------------------------------
int Return_Score(void)
{
	return g_score;
}