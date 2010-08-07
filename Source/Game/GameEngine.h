// GameEngine.h: interface for the CGameEngine class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAMEENGINE_H__EC5318CE_A07C_4437_AF4C_80F07CDDE6A7__INCLUDED_)
#define AFX_GAMEENGINE_H__EC5318CE_A07C_4437_AF4C_80F07CDDE6A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

#include "Timer.h"
#include "Graphic.h"
#include "Level.h"
#include "Sprite.h"
#include "SoundEngine.h"

class CGameEngine  
{
public:
	int PlayerCollidedWith(CSprite* sprite_in);
	void PlayerCollisionDetection();

	char appPath[513];

	int tileSub;

	void MoveSpriteDown(CSprite* sprite_in, bool player, double spriteMovement, bool doCollision);
	void MoveSpriteUp(CSprite* sprite_in, bool player, double spriteMovement, bool doCollision);

	void MoveSpriteLeft(CSprite* sprite_in, bool isPlayer, double movement, bool doCollision);
	void MoveSpriteRight(CSprite* sprite_in, bool isPlayer, double movement, bool doCollision);
	CLevel curLevel;
	CTimer tmr;
	CSoundEngine soundengine;

	long soundBackground;
	long soundDoorOpen;

	CSprite spritePlayer;
	int spritePlayerX;
	int spritePlayerY;
	int spritePlayerWidth;
	int spritePlayerHeight;
	
	struct playerInfo
	{
		int playerScore;
		int playerHealth;

		int curDirection;

		int hasRedKey;
		int hasBlueKey;

		int curLevel;
	};

	playerInfo playerStats;

	double spritePlayerJumpDistanceRemaining;

	int gameKeys[256];
	int gameState;
	void ChangeState(int newState);
	void UnInitState();
	void InitState();

	void ProcessKeyDown(int keyCode);
	void ProcessKeyUp(int keyCode);
	HWND windhWnd;
	void UpdateScreen();
	void DrawFrame();
	void UpdateFrame(double secPassed);
	int GameLoop();
	void CreateBuffer(int gameWidth, int gameHeight, HWND wind_hWnd);
	CGameEngine();
	virtual ~CGameEngine();

	HDC bufferDC;
	RECT bufferRect;

	int testVar;
};

#endif // !defined(AFX_GAMEENGINE_H__EC5318CE_A07C_4437_AF4C_80F07CDDE6A7__INCLUDED_)
