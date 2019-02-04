//
//	UI.cpp
//		Author:HIROMASA IKEDA		DATE:2018/08/28
//===============================================
#include<d3dx9.h>
#define _USE_MATH_DEFINES
#include<math.h>
#include"CUI.h"
#include"input.h"

static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;

namespace NRender2D
{
	namespace UI
	{
		void BarIndicator(D3DXVECTOR2 Position, D3DXVECTOR2 Scale, D3DCOLOR BackColor, D3DCOLOR LineColor, float Score, float MaxScore)
		{
			float width = Scale.x * 0.5f;
			float height = Scale.y * 0.5f;

			float Line = min(Score / MaxScore, 1.0f);
			Line = max(0.0f, Line);
			Line = Line * Scale.x;

			Vertex2D Bar[10] =
			{
				//Line
				{ D3DXVECTOR4(Position.x - width,			Position.y - height, 0.0f,1.0f),LineColor },
				{ D3DXVECTOR4(Position.x - width + Line,	Position.y - height, 0.0f,1.0f),LineColor },
				{ D3DXVECTOR4(Position.x - width,			Position.y + height, 0.0f,1.0f),LineColor },
				{ D3DXVECTOR4(Position.x - width + Line,	Position.y + height, 0.0f,1.0f),LineColor },

				//Back
				{ D3DXVECTOR4(Position.x - width + Line,	Position.y + height, 0.0f,1.0f),BackColor },
				{ D3DXVECTOR4(Position.x - width + Line,	Position.y - height, 0.0f,1.0f),BackColor },
				{ D3DXVECTOR4(Position.x - width + Line,	Position.y - height, 0.0f,1.0f),BackColor },
				{ D3DXVECTOR4(Position.x + width,			Position.y - height, 0.0f,1.0f),BackColor },
				{ D3DXVECTOR4(Position.x - width + Line,	Position.y + height, 0.0f,1.0f),BackColor },
				{ D3DXVECTOR4(Position.x + width,			Position.y + height, 0.0f,1.0f),BackColor }

			};

			g_pD3DDevice = System_GetDevice();
			g_pD3DDevice->SetFVF(FVF_VERTEX2D);
			g_pD3DDevice->SetTexture(0, NULL);
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 10, &Bar, sizeof(Bar[0]));
		}

		void CircleIndicator(D3DXVECTOR2 Position,D3DCOLOR BackColor,D3DCOLOR LineColor,float radius,float width,float Score,float MaxScore)
		{
			const UINT CircleSprit = 180;							//円分割数
			const float radian = (360/CircleSprit)*((float)M_PI / 180);	//１メモリ分の角度
			const UINT CircleVertex = CircleSprit + 1;		//円の頂点、重複で始点終点
			const UINT VertexNum = CircleVertex * 2 + 2;	//総頂点数(+縮退ポリゴン)

			float outRadius = radius + width;				//外周円半径
			float Line = min(Score / MaxScore,1.0f);
			Line = max(Line,0.0f);

			Line *= 360;
			Line = Line * ((float)M_PI / 180);
			
			float angle = 0;

			Vertex2D Bar[VertexNum];
			bool bOver = false;

			for(int i = 0; i < VertexNum; i += 2)
			{
				//内円
				Bar[i].Position.x = Position.x + (sinf(angle) * radius);
				Bar[i].Position.y = Position.y - (cosf(angle) * radius);
				Bar[i].Position.z = 0.0f;
				Bar[i].Position.w = 1.0f;

				//外円
				Bar[i + 1].Position.x = Position.x + (sinf(angle) * outRadius);
				Bar[i + 1].Position.y = Position.y - (cosf(angle) * outRadius);
				Bar[i + 1].Position.z = 0.0f;
				Bar[i + 1].Position.w = 1.0f;
				
				if (Line <= angle)
				{
					if(bOver == false)
					{
						//縮退ポリゴン
						Bar[i].Color = LineColor;
						Bar[i + 1].Color = LineColor;
						Bar[i + 2] = Bar[i];
						Bar[i + 3] = Bar[i + 1];
						Bar[i + 2].Color = BackColor;
						Bar[i + 3].Color = BackColor;
						i += 2;
						bOver = true;
					}
					else
					{
						Bar[i].Color = BackColor;
						Bar[i + 1].Color = BackColor;
					}
				}
				else
				{
					Bar[i].Color = LineColor;
					Bar[i + 1].Color = LineColor;
				}
				
				angle += radian;
				
			}
			
			g_pD3DDevice = System_GetDevice();
			g_pD3DDevice->SetFVF(FVF_VERTEX2D);
			g_pD3DDevice->SetTexture(0, NULL);
			g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, VertexNum -2, &Bar, sizeof(Bar[0]));
		}

		//===============================================
		//	UI クラス
		//===============================================

		//------------------------------------
		//	コンストラクタ
		//------------------------------------
		MouseUI::MouseUI(Transform2* transform, NTexture::Texture* texture, D3DCOLOR Color)
			:
			CSprite(transform, texture, Color)
		{

		}

		//------------------------------------
		//	クリック
		//------------------------------------
		bool MouseUI::Click()
		{
			if (Hover() && Mouse_IsLeftDown())
			{
				return true;
			}
			return false;
		}

		//------------------------------------
		//	ホバー
		//------------------------------------
		bool MouseUI::Hover()
		{
			if (this->Transform()->Position()->x - this->Transform()->Scale()->x * 0.5f <= Mouse_IsMouseX() && Mouse_IsMouseX() <= this->Transform()->Position()->x + this->Transform()->Scale()->x * 0.5f)
			{
				if (this->Transform()->Position()->y - this->Transform()->Scale()->y * 0.5f <= Mouse_IsMouseY() && Mouse_IsMouseY() <= this->Transform()->Position()->y + this->Transform()->Scale()->x * 0.5f)
				{
					return true;
				}
			}

			return false;
		}
	}
}
/*
//===============================================
//	UI クラス
//===============================================

//-------------------------------------
//	コンストラクタ
//-------------------------------------
UI::UI(Transform2* pTransform2, NTexture::CTexture* pTexture):Sprite(pTransform2, pTexture)
{
}

UI::UI(Transform2* pTransform2, NTexture::CTexture* pTexture, NTexture::CAnimation* pAnimation): Sprite(pTransform2, pTexture, pAnimation)
{
	
}

//-------------------------------------
//	Set()
//-------------------------------------
void UI::Set(Transform2* pTransform2)
{
	this->render.pTransform = pTransform2;
}

//-------------------------------------
//	Click()
//-------------------------------------
bool UI::Click()
{
	if (Hover() && Mouse_IsLeftDown())
	{
		return true;
	}
	return false;
}

//-------------------------------------
//	Hover
//-------------------------------------
bool UI::Hover()
{

	if (this->transform.Position.x - this->transform.Scale.x * 0.5f <= Mouse_IsMouseX() && Mouse_IsMouseX() <= this->transform.Position.x + this->transform.Scale.x * 0.5f)
	{
		if (this->transform.Position.y - this->transform.Scale.y * 0.5f <= Mouse_IsMouseY() && Mouse_IsMouseY() <= this->transform.Position.y + this->transform.Scale.x * 0.5f)
		{
			return true;
		}
	}

	return false;
}
*/