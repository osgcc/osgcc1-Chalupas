// SoundEngine.h: interface for the CSoundEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SOUNDENGINE_H__828D3998_0B6E_4A4F_A15C_D18C6F7E8A88__INCLUDED_)
#define AFX_SOUNDENGINE_H__828D3998_0B6E_4A4F_A15C_D18C6F7E8A88__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <windows.h>

class CSoundEngine  
{
public:
	void Notify(unsigned long devID);
	void UnloadAll();
	void UnloadSound(long index);
	void PlaySound(long index, bool Loop);
	long LoadSound(LPCTSTR appPath, LPCTSTR path, HWND hWnd);
	CSoundEngine();
	virtual ~CSoundEngine();

	MCI_OPEN_PARMS** loadedSounds;
	int soundCount;
	int soundCapacity;
};

#endif // !defined(AFX_SOUNDENGINE_H__828D3998_0B6E_4A4F_A15C_D18C6F7E8A88__INCLUDED_)
