//
//	TimeRender.cpp
//		Author:�n���R�E	DATE:2019/02/05
//===============================================

//===============================================
//	�C���N���[�h	include
//===============================================

#include"Score.h"
#include"Texture.h"
#include"Sprite.h"
#include"TimeRender.h"

#include"CTimer.h"//�c�莞�Ԃ̃w�b�_�[�t�@�C��

//===============================================
//	�}�N����`		define
//===============================================


//===============================================
//	�O���[�o���ϐ�	global
//===============================================

//------------------------------------
//	�`��
//------------------------------------
void Time_Render(D3DXVECTOR2 pos)
{
	int Timeremain;
	Timeremain = Timer::GetTime()/*�^�C�����^�[��*/;
	for (int i = 0; i < TIME_FIG; i++)
	{
		int number = Timeremain % 10;
		Timeremain /= 10;
		Number_Render({ pos.x + NTexture::Get_Width(NTexture::ScoreTex) * 0.15f * (TIME_FIG - (i + 1)), pos.y }, number);
	}
}