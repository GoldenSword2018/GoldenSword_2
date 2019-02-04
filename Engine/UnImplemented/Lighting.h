//
//	Lighting.h
//		Author:HIROMASA IKEDA	DATE:2018/10/04
//===============================================
#pragma once
#ifndef LIGHTING_H
#define LIGHTING_H

#include<d3dx9.h>

namespace NLighting
{
	void Initialize();
	void Set_Light(BOOL bSet);
	void Set_MaterialDisEnable();
	void Set_MaterialEnable();
	void Set_AlphaTest(BOOL enable, int alpha);
	void Set_DepthTest(BOOL set);
}

#endif // !LIGHTING_H

