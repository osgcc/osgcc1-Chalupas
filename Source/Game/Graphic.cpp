// Graphic.cpp: implementation of the CGraphic class.
//
//////////////////////////////////////////////////////////////////////

#include "Graphic.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraphic::CGraphic()
{
	graphicDC = NULL;
}

CGraphic::~CGraphic()
{
	if (graphicDC != NULL)
		DeleteDC(graphicDC);
}

void CGraphic::LoadGraphic(LPCTSTR appPath, LPCTSTR path)
{
	BITMAPINFOHEADER bih;
	BITMAPFILEHEADER bfh;

	char ultPath[513];

	ultPath[0] = 0;
	strcpy(ultPath, appPath);
	strcat(ultPath, path);

	FILE * f = fopen(ultPath, "rb");

	fread(&bfh, sizeof(BITMAPFILEHEADER), 1, f);
	fread(&bih, sizeof(BITMAPINFOHEADER), 1, f);

	fclose(f);

	HDC dcz;

	dcz = GetDC(0);

	if (graphicDC != NULL)
	{
		DeleteDC(graphicDC);
	}

	graphicDC = CreateCompatibleDC(dcz);

	graphicRect.left = 0;
	graphicRect.top = 0;
	graphicRect.bottom = bih.biHeight;
	graphicRect.right = bih.biWidth;

	HBITMAP hbmp; 

	hbmp = (HBITMAP)LoadImage(NULL, ultPath, 0,0,0,16);

	SelectObject(graphicDC, hbmp);
	DeleteObject(hbmp);

	ReleaseDC(0, dcz);
}
