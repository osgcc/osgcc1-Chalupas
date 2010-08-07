// Timer.h: interface for the CTimer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TIMER_H__1F40CB6C_51C3_482F_BD1E_3A3EDD78C58D__INCLUDED_)
#define AFX_TIMER_H__1F40CB6C_51C3_482F_BD1E_3A3EDD78C58D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

#define TIMER_RESOLUTION 16

class CTimer  
{
public:
	void Reset();
	double GetDeltaTime();
	CTimer();
	virtual ~CTimer();

	LONGLONG timeLast;
	LONGLONG timeCur;

	double timeFactor;

	double timeAverages[TIMER_RESOLUTION];
	int timeAvgCount;
	int timeAvgIndex;
};

#endif // !defined(AFX_TIMER_H__1F40CB6C_51C3_482F_BD1E_3A3EDD78C58D__INCLUDED_)
