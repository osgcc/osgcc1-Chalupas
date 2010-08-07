// Timer.cpp: implementation of the CTimer class.
//
//////////////////////////////////////////////////////////////////////

#include "Timer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTimer::CTimer()
{
	timeAvgCount = 0;
	timeAvgIndex = 0;

	LONGLONG perfFreq;

	QueryPerformanceFrequency((LARGE_INTEGER*)&perfFreq);

	timeFactor = (double)1.0 / (double)perfFreq;

	QueryPerformanceCounter((LARGE_INTEGER*)&timeLast);
}

CTimer::~CTimer()
{

}

double CTimer::GetDeltaTime()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&timeCur);

	double timeSpan = (double)(timeCur - timeLast) * timeFactor;

	timeLast = timeCur;

	timeAverages[timeAvgIndex] = timeSpan;

	timeAvgIndex++;

	if (timeAvgCount != TIMER_RESOLUTION)
	{
		timeAvgCount++;
	}
	

	if (timeAvgIndex == timeAvgCount)
	{
		timeAvgIndex = 0;
	}

	timeSpan = timeAverages[0];

	int i;

	for (i=1; i<timeAvgCount; i++)
	{
		timeSpan += timeAverages[i];
	}

	timeSpan /= timeAvgCount;

	return timeSpan;
}

void CTimer::Reset()
{
	timeAvgCount = 0;
	timeAvgIndex = 0;

	LONGLONG perfFreq;

	QueryPerformanceFrequency((LARGE_INTEGER*)&perfFreq);

	timeFactor = (double)1.0 / (double)perfFreq;

	QueryPerformanceCounter((LARGE_INTEGER*)&timeLast);
}
