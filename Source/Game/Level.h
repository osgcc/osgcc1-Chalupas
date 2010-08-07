// Level.h: interface for the CLevel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LEVEL_H__D7A04F02_5665_445B_A78E_54AE000B8AD9__INCLUDED_)
#define AFX_LEVEL_H__D7A04F02_5665_445B_A78E_54AE000B8AD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graphic.h"
#include "Sprite.h"


#define SPRITE_COUNT 16

class CLevel  
{
public:
	void LoadLevel(LPCTSTR appPath, int levelnum);

	struct spriteInfo
	{
		int id;
		int tx;
		int ty;
	};

	void DrawLevelForeground(HDC buffer);

	//For calculating the background layer
	
	//background x, y
	int BackgroundX;
	int BackgroundY;

	int BackgroundRelX;
	int BackgroundRelY;

	int BackgroundMaxX;
	int BackgroundMaxY;

	//width, height in pixels of level
	int LevelPixelWidth;
	int LevelPixelHeight;

	double MoveLevelY(double amt);
	double MoveLevelX(double amt);

	void PositionBackground();
	int maxTileIndex;
	int scrollBGVert;
	CGraphic gfxTileMap;
	CGraphic gfxBackground;

	void DrawLevel(HDC buffer);
	void LoadLevel(LPCTSTR appPath, LPCTSTR path);
	CLevel();
	virtual ~CLevel();

	int* LevelMatrix;
	int* LevelTypes;

	short LevelWidth;
	short LevelHeight;

	int LevelX;
	int LevelY;

	double LevelXOffset;
	double LevelYOffset;

	char * bgPath;
	char * tileMapPath;
	char * levelTitle;

	CSprite* LevelSprites;

	spriteInfo spriteArray[256];
	int LevelSpriteCount;
};

#endif // !defined(AFX_LEVEL_H__D7A04F02_5665_445B_A78E_54AE000B8AD9__INCLUDED_)
