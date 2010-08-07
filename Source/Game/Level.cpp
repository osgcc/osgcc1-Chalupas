// Level.cpp: implementation of the CLevel class.
//
//////////////////////////////////////////////////////////////////////

#include "Level.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLevel::CLevel()
{
	levelTitle = NULL;
	bgPath = NULL;
	tileMapPath = NULL;
	LevelMatrix = NULL;
	LevelTypes = NULL;

	LevelSpriteCount=0;
	LevelSprites=NULL;
}

CLevel::~CLevel()
{
	if (levelTitle != NULL)
		delete levelTitle;

	if (bgPath != NULL)
		delete bgPath;

	if (tileMapPath != NULL)
		delete tileMapPath;

	if (LevelMatrix != NULL)
		delete LevelMatrix;

	if (LevelTypes != NULL)
		delete LevelTypes;

	if (LevelSprites != NULL)
	{
		LevelSpriteCount = 0;
		//delete LevelSprites;
	}
}

void CLevel::LoadLevel(LPCTSTR appPath, LPCTSTR path)
{
	char ultPath[513];
	ultPath[0] = 0;

	strcpy(ultPath, appPath);

	strcat(ultPath, "Levels\\");
	strcat(ultPath, path);
	
	if (levelTitle != NULL)
		delete levelTitle;

	if (bgPath != NULL)
		delete bgPath;

	if (tileMapPath != NULL)
		delete tileMapPath;

	if (LevelMatrix != NULL)
		delete LevelMatrix;

	if (LevelTypes != NULL)
		delete LevelTypes;

	FILE* f = fopen(ultPath, "rb");

	fread(&LevelWidth, sizeof(short), 1, f);
	fread(&LevelHeight, sizeof(short), 1, f);

	//allocate memory for the level

	maxTileIndex = LevelWidth * LevelHeight;

	LevelMatrix = new int[maxTileIndex];
	LevelTypes = new int[maxTileIndex];

	fread(LevelMatrix, sizeof(int)*maxTileIndex, 1, f);
	fread(LevelTypes, sizeof(int)*maxTileIndex, 1, f);

	short i;

	fread(&i, sizeof(short), 1, f);

	scrollBGVert = i;

	char o;

	fread(&o, 1,1,f);

	levelTitle = new char[o+1];
	fread(levelTitle, sizeof(char) * o, 1, f);
	levelTitle[o] = 0;

	fread(&o, 1,1,f);

	bgPath = new char[o+1];
	fread(bgPath, sizeof(char) * o, 1, f);
	bgPath[o] = 0;

	fread(&o, 1,1,f);

	tileMapPath = new char[o+1];
	fread(tileMapPath, sizeof(char) * o, 1, f);
	tileMapPath[o] = 0;

	fclose(f);

	LevelX = 0;
	LevelY = LevelHeight - 15;

	LevelXOffset = 0;
	LevelYOffset = 0;

	//load tile map

	char path3[512];
	path3[0] = 0;

	strcpy(path3, appPath);
	strcat(path3, "Levels\\");
	strcat(path3, tileMapPath);
	
	gfxTileMap.LoadGraphic("", path3);

	strcpy(path3, appPath);
	strcat(path3, "Levels\\");
	strcat(path3, bgPath);

	gfxBackground.LoadGraphic("", path3);

	LevelPixelWidth = LevelWidth * 32;
	LevelPixelHeight = LevelHeight * 32;

	if (scrollBGVert)
	{
		BackgroundRelX = LevelPixelWidth - 640;
		BackgroundRelY = BackgroundRelX * LevelPixelHeight;
		BackgroundRelY /= LevelPixelWidth;
	}
	else
	{
		BackgroundRelY = LevelPixelHeight - 480;
		BackgroundRelX = BackgroundRelY * LevelPixelWidth;
		BackgroundRelX /= LevelPixelHeight;
	}

	BackgroundMaxX = gfxBackground.graphicRect.right - 640;
	BackgroundMaxY = gfxBackground.graphicRect.bottom - 480;

	PositionBackground();
}

void CLevel::DrawLevel(HDC buffer)
{
	//Draw Background
	BitBlt(buffer, 0,0,640,480,gfxBackground.graphicDC,BackgroundX,BackgroundY,SRCCOPY);

	//Tile?

	if (scrollBGVert)
	{
		if (BackgroundY + 480 > gfxBackground.graphicRect.bottom)
		{
			//tile
			BitBlt(buffer, gfxBackground.graphicRect.bottom - BackgroundY,0,640,480-(gfxBackground.graphicRect.bottom - BackgroundY),gfxBackground.graphicDC,BackgroundX,0,SRCCOPY);
		}
	}
	else
	{
		if (BackgroundX + 640 > gfxBackground.graphicRect.right)
		{
			//tile
			BitBlt(buffer, gfxBackground.graphicRect.right - BackgroundX,0,640-(gfxBackground.graphicRect.right - BackgroundX),480,gfxBackground.graphicDC,0,BackgroundY,SRCCOPY);
		}
	}

	int x;
	int y;

	int tx;
	int ty;

	int dxbase;
	int dx;
	int dy;

	int a, abase;

	dxbase = dx = (int)LevelXOffset;
	dy = (int)LevelYOffset;

	abase = a = LevelX + (LevelY * LevelWidth);

	for (y=LevelY; y<LevelY+16; y++)
	{
		for (x=LevelX; x<LevelX+21; x++)
		{
			if (LevelTypes[a] != 1)
			{
				tx = LevelMatrix[a];
				ty = tx / 18;
				tx = tx % 18;

				tx *= 32;
				ty *= 32;

				TransparentBlt(buffer, dx, dy, 32, 32, gfxTileMap.graphicDC, tx, ty, 32, 32, 0x00FF00);
			}
			dx += 32;

			a++;
		}

		dx = dxbase;
		dy += 32;

		abase = abase + LevelWidth;
		a = abase;
	}

}

void CLevel::PositionBackground()
{
	double BackgroundPercentX, BackgroundPercentY;

	BackgroundPercentX = ((double)(LevelX * 32) - LevelXOffset) / (double)BackgroundRelX;
	BackgroundPercentY = ((double)(LevelY * 32) - LevelYOffset) / (double)BackgroundRelY;

	BackgroundX = (int)(BackgroundPercentX * (double)BackgroundMaxX);
	BackgroundY = (int)(BackgroundPercentY * (double)BackgroundMaxY);
}

//moves the level on the X axis...
//if it cannot move the total distance,
//it will return the amount that it could not move
double CLevel::MoveLevelX(double amt)
{
	LevelXOffset -= amt;

	//amount to change LevelX
	int amtOffset;

	amtOffset = (int)(LevelXOffset / 32);

	LevelX -= amtOffset;

	LevelXOffset -= (amtOffset * 32);

	if (LevelXOffset > 0)
	{
		LevelXOffset -= 32;
		LevelX--;
	}
	
	double nullMovement=0;

	if (LevelX < 0)
	{
		//cannot move the entire way
		nullMovement = (double)(LevelX * 32) - LevelXOffset;
		LevelXOffset = 0;
		LevelX = 0;
	}
	
	if (LevelX > LevelWidth-21)
	{
		nullMovement = ((double)((LevelX + 20) * 32) - LevelXOffset) - (double)LevelPixelWidth;
		LevelX = LevelWidth-20;
		LevelXOffset = 0;
	}
	PositionBackground();

	return nullMovement;
}

double CLevel::MoveLevelY(double amt)
{
	LevelYOffset -= amt;

	//amount to change LevelY
	int amtOffset;

	amtOffset = (int)(LevelYOffset / 32);

	LevelY -= amtOffset;

	LevelYOffset -= (amtOffset * 32);

	if (LevelYOffset > 0)
	{
		LevelYOffset -= 32;
		LevelY--;
	}

	double nullMovement=0;

	if (LevelY < 0)
	{
		nullMovement = (double)(LevelY * 32) - LevelYOffset;
		LevelYOffset = 0;
		LevelY = 0;
	}
	
	if (LevelY > LevelHeight-16)
	{
		nullMovement = ((double)((LevelY + 15) * 32) - LevelYOffset) - (double)LevelPixelHeight;
		LevelY = LevelHeight-15;
		LevelYOffset = 0;
	}
	PositionBackground();

	return nullMovement;
}

void CLevel::DrawLevelForeground(HDC buffer)
{
	int x;
	int y;

	int tx;
	int ty;

	int dxbase;
	int dx;
	int dy;

	int a, abase;

	dxbase = dx = (int)LevelXOffset;
	dy = (int)LevelYOffset;

	abase = a = LevelX + (LevelY * LevelWidth);

	for (y=LevelY; y<LevelY+16; y++)
	{
		for (x=LevelX; x<LevelX+21; x++)
		{
			if (LevelTypes[a] == 1)
			{
				tx = LevelMatrix[a];
				ty = tx / 18;
				tx = tx % 18;

				tx *= 32;
				ty *= 32;

				TransparentBlt(buffer, dx, dy, 32, 32, gfxTileMap.graphicDC, tx, ty, 32, 32, 0x00FF00);
			}

			dx += 32;

			a++;
		}

		dx = dxbase;
		dy += 32;

		abase = abase + LevelWidth;
		a = abase;
	}
}

void CLevel::LoadLevel(LPCTSTR appPath, int levelnum)
{
	switch (levelnum)
	{
	case 0:
		LoadLevel(appPath, "level1.lvl");

		if (LevelSprites != NULL)
		{
			LevelSpriteCount = 0;
			//delete LevelSprites;
		}

		LevelSprites = new CSprite[4];
		LevelSpriteCount = 4;

		LevelSprites[0].LoadSprite(appPath, "chalupa");
		LevelSprites[0].curX = (16*32);
		LevelSprites[0].curY = (19*32);

		LevelSprites[1].LoadSprite(appPath, "chalupa");
		LevelSprites[1].curX = (9*32);
		LevelSprites[1].curY = (17*32);

		LevelSprites[2].LoadSprite(appPath, "redkey");
		LevelSprites[2].curX = (21*32);
		LevelSprites[2].curY = (28*32);

		LevelSprites[3].LoadSprite(appPath, "exit");
		LevelSprites[3].curX = (86*32);
		LevelSprites[3].curY = (23*32);

		break;
	case 1:
		LoadLevel(appPath, "level2.lvl");

		if (LevelSprites != NULL)
		{
			LevelSpriteCount = 0;
			//delete LevelSprites;
		}

		LevelSprites = new CSprite[2];
		LevelSpriteCount = 2;

		LevelSprites[0].LoadSprite(appPath, "chalupa");
		LevelSprites[0].curX = (15*32);
		LevelSprites[0].curY = (91*32);

		LevelSprites[1].LoadSprite(appPath, "exit");
		LevelSprites[1].curX = (9*32);
		LevelSprites[1].curY = (102*32);
		break;
	case 2:
		LoadLevel(appPath, "level3.lvl");

		if (LevelSprites != NULL)
		{
			LevelSpriteCount = 0;
			//delete LevelSprites;
		}

		LevelSprites = new CSprite[1];
		LevelSpriteCount = 1;

		LevelSprites[0].LoadSprite(appPath, "exit");
		LevelSprites[0].curX = (93*32);
		LevelSprites[0].curY = (22*32);
		break;
	case 3:
		LoadLevel(appPath, "level5.lvl");

		if (LevelSprites != NULL)
		{
			LevelSpriteCount = 0;
			//delete LevelSprites;
		}

		LevelSprites = new CSprite[1];
		LevelSpriteCount = 1;

		LevelSprites[0].LoadSprite(appPath, "exit");
		LevelSprites[0].curX = (116*32);
		LevelSprites[0].curY = (25*32);
		break;
	case 4:
		break;
	}		
}
