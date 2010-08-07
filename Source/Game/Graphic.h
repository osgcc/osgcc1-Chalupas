// Graphic.h: interface for the CGraphic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHIC_H__AB6F2815_9751_408A_ACB7_DB96DD86D217__INCLUDED_)
#define AFX_GRAPHIC_H__AB6F2815_9751_408A_ACB7_DB96DD86D217__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdio.h>

class CGraphic  
{
public:
	RECT graphicRect;
	HDC graphicDC;
	void LoadGraphic(LPCTSTR appPath, LPCTSTR path);
	CGraphic();
	virtual ~CGraphic();

};

#endif // !defined(AFX_GRAPHIC_H__AB6F2815_9751_408A_ACB7_DB96DD86D217__INCLUDED_)
