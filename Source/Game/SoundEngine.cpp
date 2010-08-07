// It is the sound engine of the freaking future
//
// Dave Wilkinson
// April 7, 2007
//
//////////////////////////////////////////////////////////////////////

#include "SoundEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSoundEngine::CSoundEngine()
{
	soundCapacity = 10;
	soundCount = 0;

	loadedSounds = new MCI_OPEN_PARMS*[soundCapacity];
}

CSoundEngine::~CSoundEngine()
{
	UnloadAll();

	delete loadedSounds;
}

long CSoundEngine::LoadSound(LPCTSTR appPath, LPCTSTR path, HWND hWnd)
{
	char ultPath[513];
	ultPath[0] = 0;

	strcpy(ultPath, appPath);
	strcat(ultPath, "Sounds\\");
	strcat(ultPath, path);

	if (soundCount == soundCapacity)
	{
		soundCapacity *= 2;
		MCI_OPEN_PARMS** tmp = loadedSounds;
		loadedSounds = new MCI_OPEN_PARMS*[soundCapacity];
		memcpy(loadedSounds, tmp, sizeof(MCI_OPEN_PARMS*) * soundCount);
		delete tmp;
	}
	
	MCI_OPEN_PARMS* newParms = new MCI_OPEN_PARMS;

	newParms->dwCallback = (unsigned long)hWnd;
	newParms->lpstrAlias = (char*)soundCount;
	newParms->lpstrDeviceType = "MPEGVideo"; 
	newParms->lpstrElementName = new char[strlen(ultPath) + 1];
	strcpy((char*)newParms->lpstrElementName, (char*)ultPath);

	newParms->wDeviceID = 0;

	mciSendCommand(0, MCI_OPEN, MCI_OPEN_SHAREABLE | MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD) (LPMCI_OPEN_PARMS)newParms);

	loadedSounds[soundCount] = newParms;

	soundCount++;

	return (long)newParms;
} 

void CSoundEngine::PlaySound(long index, bool Loop)
{
	MCI_OPEN_PARMS* openParms;

	openParms = (MCI_OPEN_PARMS*)index;

	MCI_PLAY_PARMS playParms = {openParms->dwCallback, 0, 0};

	if (Loop)
	{
		mciSendCommand(openParms->wDeviceID, MCI_PLAY, MCI_NOTIFY | MCI_FROM, (DWORD) (LPMCI_PLAY_PARMS)&playParms);
	}
	else
	{
		mciSendCommand(openParms->wDeviceID, MCI_PLAY, MCI_FROM, (DWORD) (LPMCI_PLAY_PARMS)&playParms);
	}
}

void CSoundEngine::UnloadSound(long index)
{
	//stop it
	//and close it

	//murder sound index

	MCI_OPEN_PARMS* openParms;

	openParms = (MCI_OPEN_PARMS*)index;

	MCI_GENERIC_PARMS gParms = {0};

	mciSendCommand(openParms->wDeviceID, MCI_CLOSE, 0, (DWORD) (LPMCI_GENERIC_PARMS)&gParms);
	
	int i;

	soundCount--;
	for (i=(int)openParms->lpstrAlias; i<soundCount; i++)
	{
		loadedSounds[i] = loadedSounds[i+1];
	}

	delete (char*)openParms->lpstrElementName;
	delete openParms;
}

void CSoundEngine::UnloadAll()
{
	int i;

	MCI_GENERIC_PARMS gParms = {0};

	for (i=0; i<soundCount; i++)
	{
		mciSendCommand(loadedSounds[i]->wDeviceID, MCI_CLOSE, 0, (DWORD) (LPMCI_GENERIC_PARMS)&gParms);

		delete (char*)loadedSounds[i]->lpstrElementName ;
		delete loadedSounds[i];
	}

	delete loadedSounds;

	soundCapacity = 10;
	soundCount = 0;

	loadedSounds = new MCI_OPEN_PARMS*[soundCapacity];
}

void CSoundEngine::Notify(unsigned long devID)
{
	//find it

	int i;

	for (i=0; i<soundCount; i++)
	{
		if (loadedSounds[i]->wDeviceID == devID)
		{
			PlaySound((long)loadedSounds[i], true);
			break;
		}
	}
}
