// Sprite.cpp: implementation of the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "Sprite.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSprite::CSprite()
{
	curX = 0;
	curY = 0;
	curFrame = 1;

	spriteFrames = NULL;
}

CSprite::~CSprite()
{

}

void CSprite::LoadSprite(LPCTSTR appPath, LPCTSTR path)
{
	//load sprite bitmap
	char* path2;

	path2 = new char[strlen(path) + 6];

	path2[0] = 0;

	strcpy(path2, path);

	strcat(path2, ".bmp");

	char ultPath[513];

	ultPath[0] = 0;

	strcpy(ultPath, appPath);
	strcat(ultPath, "Sprites\\");
	strcat(ultPath, path2);

	gfxSpriteMap.LoadGraphic("", ultPath);

	path2[0] = 0;
	
	strcpy(path2, path);
	strcat(path2, ".spr");

	ultPath[0] = 0;

	strcpy(ultPath, appPath);
	strcat(ultPath, "Sprites\\");
	strcat(ultPath, path2);

	FILE * f = fopen(ultPath, "rb");

	fread(&spriteType, sizeof(int), 1, f);

	fread(&spriteCount, sizeof(int), 1, f);

	int i;
	if (spriteFrames != NULL)
	{
		for (i=0; i<spriteCount; i++)
		{
			if (spriteFrames[i].rectArray != NULL)
			{
				delete spriteFrames[i].rectArray;
			}
		}

		delete spriteFrames;
	}

	if (spriteCount == 0)
	{
		spriteFrames = NULL;
	}
	else
	{
		spriteFrames = new spriteInfo[spriteCount];

		for (i=0; i<spriteCount; i++)
		{
			fread(&spriteFrames[i].spriteBottomEdgeX, sizeof(int), 1, f);
			fread(&spriteFrames[i].spriteBottomEdgeWidth, sizeof(int), 1, f);

			fread(&spriteFrames[i].spriteRect, sizeof(RECT), 1, f);

			fread(&spriteFrames[i].rectCount, sizeof(int), 1, f);

			//read in all sprite frame collision rectangles

			spriteFrames[i].rectArray = new RECT[spriteFrames[i].rectCount];

			fread(spriteFrames[i].rectArray, sizeof(RECT) * spriteFrames[i].rectCount, 1, f);
		}
	}

	fclose(f);

	curFrame = 0;

	delete path2;
}

void CSprite::Draw(HDC buffer)
{
	int cF = (int)curFrame;

	TransparentBlt(buffer, (int)curX, (int)curY, spriteFrames[cF].spriteRect.right, spriteFrames[cF].spriteRect.bottom,
					gfxSpriteMap.graphicDC, 
					spriteFrames[cF].spriteRect.left,
					spriteFrames[cF].spriteRect.top,
					spriteFrames[cF].spriteRect.right, spriteFrames[cF].spriteRect.bottom,
					0x00FF00);
					
}

void CSprite::Draw(HDC buffer, double levelEdgeX, double levelEdgeY)
{
	int cF = (int)curFrame;

	if ((curX + spriteFrames[cF].spriteRect.right) > levelEdgeX ||
		(curX < (levelEdgeX + 640)) || (curY + spriteFrames[cF].spriteRect.bottom) > levelEdgeY ||
		(curY < (levelEdgeY + 480)))
	{

		TransparentBlt(buffer, (int)(curX - levelEdgeX), (int)(curY - levelEdgeY), spriteFrames[cF].spriteRect.right, spriteFrames[cF].spriteRect.bottom,
					gfxSpriteMap.graphicDC, 
					spriteFrames[cF].spriteRect.left,
					spriteFrames[cF].spriteRect.top,
					spriteFrames[cF].spriteRect.right, spriteFrames[cF].spriteRect.bottom,
					0x00FF00);
	}
}
