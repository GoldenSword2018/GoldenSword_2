//
//	CRender.h
//		Author:HIROMASA IKEDA	DATE:2018/09/29
//===============================================
#pragma once
#ifndef CRENDER_H
#define CRENDER_H

#include<d3dx9.h>
#include<vector>

//Class
#include"CTransform.h"

#include"XModel.h"
#include"CMesh.h"	
#include"Texture.h"

//NRender2D
#include"Sprite.h"
#include"CSprite.h"
#include"CUI.h"

//===============================================
//	óÒãì
//===============================================

//===============================================
//	ç\ë¢ëÃ
//===============================================

//===============================================
//	ñºëOãÛä‘
//===============================================
namespace NRender3D
{
	void Render(AMesh* pModel, CTransform* pTransform);
	void Render(AMesh* pModel, D3DXMATRIX* MtxWorld);
}

namespace NRender2D
{

}

#endif // !CRENDER_H
