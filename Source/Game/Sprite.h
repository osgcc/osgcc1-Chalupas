// Sprite.h: interface for the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPRITE_H__6BC5BBA1_0721_4BEF_9012_B9B3C353E7FD__INCLUDED_)
#define AFX_SPRITE_H__6BC5BBA1_0721_4BEF_9012_B9B3C353E7FD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graphic.h"

class CSprite  
{
public:
	void Draw(HDC buffer, double offsetX, double offsetY);
	int spriteBottomEdgeWidth;
	int spriteBottomEdgeX;
	void Draw(HDC buffer);
	double curY;
	double curX;
	double curFrame;

	struct spriteInfo
	{
		int spriteBottomEdgeX;
		int spriteBottomEdgeWidth;
		RECT spriteRect;
		int rectCount;
		RECT* rectArray;
	};

	spriteInfo* spriteFrames;
	int spriteCount;
	int spriteType;

	CGraphic gfxSpriteMap;

	void LoadSprite(LPCTSTR appPath, LPCTSTR path);
	CSprite();
	virtual ~CSprite();

};

#endif // !defined(AFX_SPRITE_H__6BC5BBA1_0721_4BEF_9012_B9B3C353E7FD__INCLUDED_)
