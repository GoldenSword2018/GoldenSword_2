//
//	CGameUI.cpp
//		Author:	DATE:
//===============================================
//	�ύX�� Changed By
//		Name:	DATE:
//
//-----------------------------------------------

//===============================================
//	�C���N���[�h	include
//===============================================
#include"common.h"
#include"CGameUI.h"
#include"Score.h"
#include"CTimer.h"
#include"Texture.h"
#include"Sprite.h"

//class

//===============================================
//	�}�N����`		define
//===============================================
#define FIG_SCORE			(6)
#define FIG_TIME			(2)


//===============================================
//	�O���[�o���ϐ�	global
//===============================================


//===============================================
//	�N���X��		class
//===============================================

//-------------------------------------
//	�`��
//-------------------------------------
void GameUI::Render()
{
	// �X�R�A�`��
	ScoreRender(Return_Score());
	// �c�莞�ԕ`��
	TimeRender(Timer::GetTime());
}

//-------------------------------------
//	�X�R�A�`��
//-------------------------------------
void GameUI::ScoreRender(int Score)
{
	// �X�R�A�w�i�`��
	D3DXVECTOR2 BackPos = D3DXVECTOR2(180.0f, 50.0f);
	NRender2D::Sprite(new Transform2(BackPos, D3DXVECTOR2(360.0f, 100.0f), 0.0f),
		new NTexture::NameTexture(NTexture::ScoreBackTex,{ 0.0f,0.0f }, { 1.0f,1.0f }), D3DCOLOR_RGBA(255, 255, 255, 255));

	// �X�R�A�����`��
	D3DXVECTOR2 LetterPos = D3DXVECTOR2(90.0f, 50.0f);
	NRender2D::Sprite(new Transform2(LetterPos, D3DXVECTOR2(130.0f, 50.0f), 0.0f),
		new NTexture::NameTexture(NTexture::ScoreLetterTex, { 0.0f,0.0f }, { 1.0f,1.0f }), D3DCOLOR_RGBA(255, 255, 255, 255));


	// �X�R�A�����`��
	D3DXVECTOR2 NumberPos = D3DXVECTOR2(265.0f, 50.0f);
	int score = Score;
	for (int i = 0; i < FIG_SCORE; i++)
	{
		unsigned int number = score % 10;
		score /= 10;
		float tx;
		tx = (float)number / 10;
		NRender2D::Sprite({ NumberPos.x + (NTexture::Get_Width(NTexture::ScoreTex) * 0.05f) * (FIG - (i + 1)), NumberPos.y }, D3DXVECTOR2(30.0f, 45.0f), D3DCOLOR_RGBA(255, 255, 255, 255), NTexture::Get_Texture(NTexture::ScoreTex), D3DXVECTOR2(tx, 0), D3DXVECTOR2(0.1, 1));
	}
}

//-------------------------------------
//	�c�莞�ԕ`��
//-------------------------------------
void GameUI::TimeRender(int Time)
{
	// �^�C���w�i�`��
	D3DXVECTOR2 BackPos = D3DXVECTOR2(WINDOWSCREEN_WIDTH_2, 55.0f);
	NRender2D::Sprite(new Transform2(BackPos, D3DXVECTOR2(120.0f, 120.0f), 0.0f),
		new NTexture::NameTexture(NTexture::TimeBackTex,{ 0.0f,0.0f }, { 1.0f,1.0f }), D3DCOLOR_RGBA(255, 255, 255, 255));

	// �^�C�������`��
	D3DXVECTOR2 NumberPos = D3DXVECTOR2(WINDOWSCREEN_WIDTH_2 - 50.0f, 50.0f);
	int time = Time;
	for (int i = 0; i < FIG_TIME; i++)
	{
		unsigned int number = time % 10;
		time /= 10;
		float tx;
		tx = (float)number / 10;
		NRender2D::Sprite({ NumberPos.x + (NTexture::Get_Width(NTexture::TimeNumberTex) * 0.06f) * (FIG - (i + 1)), NumberPos.y }, D3DXVECTOR2(40.0f, 60.0f), D3DCOLOR_RGBA(255, 255, 255, 255), NTexture::Get_Texture(NTexture::ScoreTex), D3DXVECTOR2(tx, 0), D3DXVECTOR2(0.1, 1));
	}

}