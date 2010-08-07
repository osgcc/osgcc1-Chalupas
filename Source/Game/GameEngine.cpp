// GameEngine.cpp: implementation of the CGameEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "GameEngine.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define GAMESTATE_INIT 0
#define GAMESTATE_GAME 2
#define GAMESTATE_PAUSED 3
#define GAMESTATE_EXIT 4

#define JUMP_DISTANCE 96

#define SPEED_GRAVITY 450.0
#define SPEED_PLAYER 400.0
#define SPEED_JUMP 450.0

#define SPRITE_EXIT 0
#define SPRITE_CHALUPA 1
#define SPRITE_REDKEY 2
#define SPRITE_BLUEKEY 3
#define SPRITE_GREENKEY 4
#define SPRITE_YELLOWKEY 5
#define SPRITE_REDGATE 6
#define SPRITE_BLUEGATE 7
#define SPRITE_GREENGATE 8
#define SPRITE_YELLOWGATE 9
#define SPRITE_ENEMY1 10
#define SPRITE_ENEMY2 11
#define SPRITE_ENEMY3 12
#define SPRITE_ENEMY4 13
#define SPRITE_INSTADEATH 14
#define SPRITE_BARREL 15

CGameEngine::CGameEngine()
{
	testVar=0;

	GetCurrentDirectory(512, appPath);

	if (appPath[strlen(appPath) - 1] != '\\')
	{
		strcat(appPath, "\\");
	}


}

CGameEngine::~CGameEngine()
{
	
}

//starts engine
void CGameEngine::CreateBuffer(int gameWidth, int gameHeight, HWND wind_hWnd)
{
	int i;
	for (i=0; i<256; i++)
	{
		gameKeys[i] = 0;
	}

	windhWnd = wind_hWnd;

	HDC dcz;

	dcz = GetDC(wind_hWnd);

	bufferDC = CreateCompatibleDC(dcz);

	HBITMAP hbmp;

	hbmp = CreateCompatibleBitmap(dcz, gameWidth, gameHeight);

	bufferRect.left = 0;
	bufferRect.top = 0;
	bufferRect.right = gameWidth;
	bufferRect.bottom = gameHeight;

	SelectObject(bufferDC, hbmp);

	DeleteObject(hbmp);

	ReleaseDC(wind_hWnd, dcz);

	gameState = GAMESTATE_INIT;
	InitState();
}

int CGameEngine::GameLoop()
{
	MSG msg;

	for ( ; ; )
	{
		if ( PeekMessage(&msg, NULL,0,0,PM_NOREMOVE) )
		{
			if (GetMessage(&msg, NULL, 0, 0) == 0)
			{
				//WM_QUIT
				return (int)msg.wParam;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		UpdateFrame(tmr.GetDeltaTime());

		DrawFrame();

		UpdateScreen();

		Sleep(1);
	}
}

void CGameEngine::UpdateFrame(double secPassed)
{
	secPassed = 0.005;
	switch (gameState)
	{
	case GAMESTATE_INIT:
		break;
	case GAMESTATE_GAME:

		double spriteMovement;

		if (gameKeys[VK_LEFT])
		{
			spriteMovement = -(SPEED_PLAYER * secPassed);
			MoveSpriteLeft(&spritePlayer, true, spriteMovement, true);

			if (playerStats.curDirection == 0)
			{
				//switching direction
				playerStats.curDirection = 1;
				spritePlayer.curFrame = 4;
			}
			else
			{
				spritePlayer.curFrame += (0.5 * secPassed);

				if (spritePlayer.curFrame > 8)
				{
					spritePlayer.curFrame -= 4.0;
				}
			}
		}

		if (gameKeys[VK_RIGHT])
		{
			spriteMovement = (SPEED_PLAYER * secPassed);
			MoveSpriteRight(&spritePlayer, true, spriteMovement, true);

			if (playerStats.curDirection == 1)
			{
				//switching direction
				playerStats.curDirection = 0;
				spritePlayer.curFrame = 0;
			}
			else
			{
				spritePlayer.curFrame += (0.5 * secPassed);

				if (spritePlayer.curFrame > 4)
				{
					spritePlayer.curFrame -= 4.0;
				}
			}
		}

		if (gameKeys[17] && spritePlayerJumpDistanceRemaining > 0)
		{
			spriteMovement = -(SPEED_JUMP * secPassed);

			spritePlayerJumpDistanceRemaining += spriteMovement;

			if (spritePlayerJumpDistanceRemaining < 0)
			{
				spritePlayerJumpDistanceRemaining = 0;
				spriteMovement += spritePlayerJumpDistanceRemaining;
			}

			MoveSpriteUp(&spritePlayer, true, spriteMovement, true);
		}
		else
		{
			spritePlayerJumpDistanceRemaining = -1;

			// gravity for player (uses the sprite's bottom edge property)
			spriteMovement = (SPEED_GRAVITY * secPassed);
			MoveSpriteDown(&spritePlayer, true, spriteMovement, true);
		}

		// sprite movement (platforms, ect)
		int i;
		
		for (i=0;i<curLevel.LevelSpriteCount;i++)
		{
			//gravity
			spriteMovement = (SPEED_GRAVITY * secPassed);
			MoveSpriteDown(&curLevel.LevelSprites[i], false, spriteMovement, true);
		}

		// collision detection (between player and sprites)
		PlayerCollisionDetection();

		// AI

		//eh...i'm tired

		break;
	case GAMESTATE_PAUSED:
		break;
	case GAMESTATE_EXIT:
		break;
	}
}

void CGameEngine::DrawFrame()
{
	HBRUSH brsh = CreateSolidBrush(testVar);

	FillRect(bufferDC, &bufferRect, brsh);

	//Draw Background Tiles
	curLevel.DrawLevel(bufferDC);

	//Draw Player
	spritePlayer.Draw(bufferDC);

	//Draw Sprites
	int i;

	for (i=0; i<curLevel.LevelSpriteCount; i++)
	{
		curLevel.LevelSprites[i].Draw(bufferDC, (curLevel.LevelX * 32) - curLevel.LevelXOffset, (curLevel.LevelY * 32) - curLevel.LevelYOffset);
	}

	//Draw Foreground Tiles
	curLevel.DrawLevelForeground(bufferDC);

	DeleteObject(brsh);
}

void CGameEngine::UpdateScreen()
{
	HDC dc;

	dc = GetDC(windhWnd);

	BitBlt(dc, 0, 0, bufferRect.right, bufferRect.bottom, bufferDC, 0, 0, SRCCOPY);

	ReleaseDC(windhWnd, dc);
}

void CGameEngine::ProcessKeyUp(int keyCode)
{
	if (keyCode < 256) { gameKeys[keyCode] = false; }

	switch (keyCode)
	{

		case VK_ESCAPE:
			SendMessage(windhWnd, WM_CLOSE, 0, 0);
			break;

		case VK_RETURN:
			if (spritePlayer.curFrame == 0)
			{
				spritePlayer.curFrame = 1;
			}
			else
			{
				spritePlayer.curFrame = 0;
			}
			break;
	}
}

void CGameEngine::ProcessKeyDown(int keyCode)
{	
	if (keyCode == 17 && gameKeys[17] == false && spritePlayerJumpDistanceRemaining == 0)
	{
		spritePlayerJumpDistanceRemaining = JUMP_DISTANCE;
	}

	if (keyCode < 256) { gameKeys[keyCode] = true; }
}

void CGameEngine::InitState()
{
	switch (gameState)
	{
	case GAMESTATE_INIT:
		curLevel.LoadLevel(appPath, 0);
		spritePlayer.LoadSprite(appPath, "sprite");
		//soundBackground = soundengine.LoadSound(appPath, "11 Bad Idea.mp3", windhWnd);
		//soundDoorOpen = soundengine.LoadSound(appPath, "door_open.mp3", windhWnd);

		spritePlayer.curX = 0;
		spritePlayer.curY = 480 - 250;

		spritePlayerJumpDistanceRemaining = JUMP_DISTANCE;

		playerStats.playerScore = 0;
		playerStats.playerHealth = 3;
		playerStats.curDirection = 0; //right .. 1 is left
		playerStats.hasBlueKey = false;
		playerStats.hasRedKey = false;
		playerStats.curLevel = 0;

		ChangeState(GAMESTATE_GAME);
		break;
	case GAMESTATE_GAME:
		//soundengine.PlaySound(soundBackground, true);
		break;
	case GAMESTATE_PAUSED:
		break;
	case GAMESTATE_EXIT:
		break;
	}
}

void CGameEngine::UnInitState()
{
}

void CGameEngine::ChangeState(int newState)
{
	UnInitState();

	gameState = newState;

	InitState();
}

void CGameEngine::MoveSpriteLeft(CSprite *sprite_in, bool player, double spriteMovement, bool doCollision)
{
	if (player)
	{
		//move player left
		spritePlayerX = (640 - sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteRect.bottom) / 2;

		if ((int)sprite_in->curX == spritePlayerX)
		{
			//move level left...
			
			spriteMovement = curLevel.MoveLevelX(spriteMovement);

			if (spriteMovement != 0)
			{
				sprite_in->curX += spriteMovement;
			}
		}
		else if ((int)sprite_in->curX > spritePlayerX)
		{
			//move player left, from right edge of level

			sprite_in->curX += spriteMovement;
			if ((int)sprite_in->curX < spritePlayerX)
			{
				//we can move the level, reset sprite
				//we move the level the difference

				spriteMovement = (double)spritePlayerX - sprite_in->curX;

				sprite_in->curX = (double)spritePlayerX;

				curLevel.MoveLevelX(spriteMovement);
			}
		}
		else
		{
			//move player left, toward left edge of level

			sprite_in->curX += spriteMovement;
			if ((int)sprite_in->curX > spritePlayerX)
			{
				//we can move the level, reset sprite
				//we move the level the difference

				spriteMovement = sprite_in->curX - (double)spritePlayerX;

				sprite_in->curX = (double)spritePlayerX;

				curLevel.MoveLevelX(spriteMovement);
			}				
		}

		if (doCollision)
		{
			//check collision rects for the left
			double newY;
			int subY, subYPrime;

			//the tile index on the level map that
			//the sprite is sitting on
			int tileIndex,y;

			//FOR EVERY COLLISION RECT OF THE FRAME

			int i;

			RECT* curRect;

			double tmpX;
			double setX = 0;

			for (i=0; i<sprite_in->spriteFrames[(int)sprite_in->curFrame].rectCount; i++)
			{
				curRect = &sprite_in->spriteFrames[(int)sprite_in->curFrame].rectArray[i];

				//get the tile at the top-left corner of collision rectangle
				newY = sprite_in->curY + curRect->top - curLevel.LevelYOffset;
				subY = (int)newY;

				//this is now the Y coordinate of the tile
				subY /= 32;
				subYPrime = subY + curLevel.LevelY;

				//now it is the index of the left most tile in the level map
				subYPrime *= curLevel.LevelWidth;
				
				//now tileindex is the first tile underneith the sprite
				int subX;
				subX = (int)(((int)sprite_in->curX + curRect->left - curLevel.LevelXOffset) / 32);

				tileIndex = subYPrime + subX + curLevel.LevelX;

				//init y, which keeps track of our movement down the side of the rectangle
				y = 0;

				//go along the left most edge...and look for collisions in the collision rects
				while (y < (curRect->bottom - curRect->top))
				{
					//is it resting on a Passable or Solid block?	
					if (curLevel.LevelTypes[tileIndex] > 1)
					{
						//Yes, realign the sprite
						//onto the tile

						tmpX = ((subX+1) * 32) + curLevel.LevelXOffset;
						tmpX -= (curRect->left + sprite_in->curX); 

						if (setX == 0 || tmpX > setX) 
						{ 
							setX = tmpX; 
						}
					}

					y += 32;
					tileIndex+=curLevel.LevelWidth;
				}
			}

			if (setX != 0)
			{
				MoveSpriteRight(sprite_in, true, setX, false);
			}
		}
	}
	else
	{
		//move sprite left
		sprite_in->curX += spriteMovement;

		if (doCollision)
		{
			//check collision rects for the left
			double newY;
			int subY, subYPrime;

			//the tile index on the level map that
			//the sprite is sitting on
			int tileIndex,y;

			//FOR EVERY COLLISION RECT OF THE FRAME

			int i;

			RECT* curRect;

			double tmpX;
			double setX = 0;

			for (i=0; i<sprite_in->spriteFrames[(int)sprite_in->curFrame].rectCount; i++)
			{
				curRect = &sprite_in->spriteFrames[(int)sprite_in->curFrame].rectArray[i];

				//get the tile at the top-left corner of collision rectangle
				newY = sprite_in->curY + curRect->top;
				subY = (int)newY;

				//this is now the Y coordinate of the tile
				subY /= 32;
				subYPrime = subY + curLevel.LevelY;

				//now it is the index of the left most tile in the level map
				subYPrime *= curLevel.LevelWidth;
				
				//now tileindex is the first tile underneith the sprite
				int subX;
				subX = (int)(((int)sprite_in->curX + curRect->left) / 32);

				tileIndex = subYPrime + subX + curLevel.LevelX;

				//init y, which keeps track of our movement down the side of the rectangle
				y = 0;

				//go along the left most edge...and look for collisions in the collision rects
				while (y < (curRect->bottom - curRect->top))
				{
					//is it resting on a Passable or Solid block?	
					if (curLevel.LevelTypes[tileIndex] > 1)
					{
						//Yes, realign the sprite
						//onto the tile

						tmpX = ((subX+1) * 32);
						tmpX -= (curRect->left + sprite_in->curX); 

						if (setX == 0 || tmpX > setX) 
						{ 
							setX = tmpX; 
						}
					}

					y += 32;
					tileIndex+=curLevel.LevelWidth;
				}
			}

			if (setX != 0)
			{
				MoveSpriteRight(sprite_in, true, setX, false);
			}
		}
	}
}

void CGameEngine::MoveSpriteRight(CSprite *sprite_in, bool player, double spriteMovement, bool doCollision)
{
	if (player)
	{
		//move player right
		spritePlayerX = (640 - sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteRect.bottom) / 2;


		//check collision rects

		if ((int)sprite_in->curX == spritePlayerX)
		{
			//move level right...
			
			spriteMovement = curLevel.MoveLevelX(spriteMovement);

			if (spriteMovement != 0)
			{
				sprite_in->curX += spriteMovement;
			}
		}
		else if ((int)spritePlayer.curX > spritePlayerX)
		{
			//move player right, from left edge of level

			sprite_in->curX += spriteMovement;
			if ((int)sprite_in->curX < spritePlayerX)
			{
				//we can move the level, reset sprite
				//we move the level the difference

				spriteMovement = (double)spritePlayerX - sprite_in->curX;

				sprite_in->curX = (double)spritePlayerX;

				curLevel.MoveLevelX(spriteMovement);
			}
		}
		else
		{
			//move player right, toward right edge of level

			sprite_in->curX += spriteMovement;
			if ((int)sprite_in->curX > spritePlayerX)
			{
				//we can move the level, reset sprite
				//we move the level the difference

				spriteMovement = sprite_in->curX - (double)spritePlayerX;

				sprite_in->curX = (double)spritePlayerX;

				curLevel.MoveLevelX(spriteMovement);
			}				
		}

		if (doCollision)
		{
			//check collision rects for the left
			double newY;
			int subY, subYPrime;

			//the tile index on the level map that
			//the sprite is sitting on
			int tileIndex,y;

			//FOR EVERY COLLISION RECT OF THE FRAME

			int i;

			RECT* curRect;

			double tmpX;
			double setX = 0;

			for (i=0; i<sprite_in->spriteFrames[(int)sprite_in->curFrame].rectCount; i++)
			{
				curRect = &sprite_in->spriteFrames[(int)sprite_in->curFrame].rectArray[i];

				//get the tile at the top-left corner of collision rectangle
				newY = sprite_in->curY + curRect->top - curLevel.LevelYOffset;
				subY = (int)newY;

				//this is now the Y coordinate of the tile
				subY /= 32;
				subYPrime = subY + curLevel.LevelY;

				//now it is the index of the left most tile in the level map
				subYPrime *= curLevel.LevelWidth;
				
				//now tileindex is the first tile underneith the sprite
				int subX;
				subX = (int)(((int)sprite_in->curX + curRect->right - curLevel.LevelXOffset) / 32);

				tileIndex = subYPrime + subX + curLevel.LevelX;

				//init y, which keeps track of our movement down the side of the rectangle
				y = 0;

				//go along the left most edge...and look for collisions in the collision rects
				for ( ; ; )
				{
					if (y >= curRect->bottom) { break; }

					//is it resting on a Passable or Solid block?	
					if (curLevel.LevelTypes[tileIndex] > 1)
					{
						//Yes, realign the sprite
						//onto the tile

						tmpX = ((subX) * 32) + curLevel.LevelXOffset;
						tmpX -= (curRect->right + sprite_in->curX); 

						if (setX == 0 || tmpX > setX) 
						{ 
							setX = tmpX; 
						}
					}

					y += 32;
					tileIndex+=curLevel.LevelWidth;
				}
			}

			if (setX != 0)
			{
				MoveSpriteLeft(sprite_in, true, setX, false);
			}
		}
	}
	else
	{
		//move sprite right
		sprite_in->curX += spriteMovement;

		if (doCollision)
		{
			//check collision rects for the left
			double newY;
			int subY, subYPrime;

			//the tile index on the level map that
			//the sprite is sitting on
			int tileIndex,y;

			//FOR EVERY COLLISION RECT OF THE FRAME

			int i;

			RECT* curRect;

			double tmpX;
			double setX = 0;

			for (i=0; i<sprite_in->spriteFrames[(int)sprite_in->curFrame].rectCount; i++)
			{
				curRect = &sprite_in->spriteFrames[(int)sprite_in->curFrame].rectArray[i];

				//get the tile at the top-left corner of collision rectangle
				newY = sprite_in->curY + curRect->top;
				subY = (int)newY;

				//this is now the Y coordinate of the tile
				subY /= 32;
				subYPrime = subY + curLevel.LevelY;

				//now it is the index of the left most tile in the level map
				subYPrime *= curLevel.LevelWidth;
				
				//now tileindex is the first tile underneith the sprite
				int subX;
				subX = (int)(((int)sprite_in->curX + curRect->right) / 32);

				tileIndex = subYPrime + subX + curLevel.LevelX;

				//init y, which keeps track of our movement down the side of the rectangle
				y = 0;

				//go along the left most edge...and look for collisions in the collision rects
				for ( ; ; )
				{
					if (y >= curRect->bottom) { break; }

					//is it resting on a Passable or Solid block?	
					if (curLevel.LevelTypes[tileIndex] > 1)
					{
						//Yes, realign the sprite
						//onto the tile

						tmpX = ((subX) * 32);
						tmpX -= (curRect->right + sprite_in->curX); 

						if (setX == 0 || tmpX > setX) 
						{ 
							setX = tmpX; 
						}
					}

					y += 32;
					tileIndex+=curLevel.LevelWidth;
				}
			}

			if (setX != 0)
			{
				MoveSpriteLeft(sprite_in, true, setX, false);
			}
		}
	}
}

void CGameEngine::MoveSpriteUp(CSprite *sprite_in, bool player, double spriteMovement, bool doCollision)
{	
	if (player)
	{
		//move player left
		spritePlayerY = (480 - sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteRect.bottom) / 2;

		if ((int)sprite_in->curY == spritePlayerY)
		{
			//move level up...
			
			spriteMovement = curLevel.MoveLevelY(spriteMovement);

			if (spriteMovement != 0)
			{
				sprite_in->curY += spriteMovement;
			}
		}
		else if ((int)sprite_in->curY > spritePlayerY)
		{
			//move player up, from bottom edge of level

			sprite_in->curY += spriteMovement;
			if ((int)sprite_in->curY < spritePlayerY)
			{
				//we can move the level, reset sprite
				//we move the level the difference

				spriteMovement = (double)spritePlayerY - sprite_in->curY;

				sprite_in->curY = (double)spritePlayerY;

				curLevel.MoveLevelY(spriteMovement);
			}
		}
		else
		{
			//move player up, toward top edge of level

			sprite_in->curY += spriteMovement;
			if ((int)sprite_in->curY > spritePlayerX)
			{
				//we can move the level, reset sprite
				//we move the level the difference

				spriteMovement = sprite_in->curY - (double)spritePlayerY;

				sprite_in->curY = (double)spritePlayerY;

				curLevel.MoveLevelY(spriteMovement);
			}				
		}

		if (doCollision)
		{
			//check collision rects for the left
			double newY;
			int subY, subYPrime;

			//the tile index on the level map that
			//the sprite is sitting on
			int tileIndex,x;

			//FOR EVERY COLLISION RECT OF THE FRAME

			int i;

			RECT* curRect;

			double tmpY;
			double setY = 0;

			for (i=0; i<sprite_in->spriteFrames[(int)sprite_in->curFrame].rectCount; i++)
			{
				curRect = &sprite_in->spriteFrames[(int)sprite_in->curFrame].rectArray[i];

				//get the tile at the top-left corner of collision rectangle
				newY = sprite_in->curY + curRect->top - curLevel.LevelYOffset;
				subY = (int)newY;

				//this is now the Y coordinate of the tile
				subY /= 32;
				subYPrime = subY + curLevel.LevelY;

				//now it is the index of the left most tile in the level map
				subYPrime *= curLevel.LevelWidth;
				
				//now tileindex is the first tile underneith the sprite
				int subX;
				subX = (int)(((int)sprite_in->curX + curRect->left - curLevel.LevelXOffset) / 32);

				tileIndex = subYPrime + subX + curLevel.LevelX;

				//init y, which keeps track of our movement down the side of the rectangle
				x = 0;

				//go along the left most edge...and look for collisions in the collision rects
				while (x < (curRect->right - curRect->left)) 
				{
					//is it resting on a Solid block?	
					if (curLevel.LevelTypes[tileIndex] > 2)
					{
						//Yes, realign the sprite
						//onto the tile

						tmpY = ((subY+1) * 32) + curLevel.LevelYOffset;
						tmpY -= (curRect->top + sprite_in->curY); 

						if (setY == 0 || tmpY > setY) 
						{ 
							setY = tmpY; 
						}
					}

					x += 32;
					tileIndex++;
				}
			}

			if (setY != 0)
			{
				MoveSpriteDown(sprite_in, true, setY, false);
			}
		}
	}
	else
	{
		//move sprite up
		sprite_in->curY += spriteMovement;

		if (doCollision)
		{
			//check collision rects for the left
			double newY;
			int subY, subYPrime;

			//the tile index on the level map that
			//the sprite is sitting on
			int tileIndex,x;

			//FOR EVERY COLLISION RECT OF THE FRAME

			int i;

			RECT* curRect;

			double tmpY;
			double setY = 0;

			for (i=0; i<sprite_in->spriteFrames[(int)sprite_in->curFrame].rectCount; i++)
			{
				curRect = &sprite_in->spriteFrames[(int)sprite_in->curFrame].rectArray[i];

				//get the tile at the top-left corner of collision rectangle
				newY = sprite_in->curY + curRect->top;
				subY = (int)newY;

				//this is now the Y coordinate of the tile
				subY /= 32;
				subYPrime = subY + curLevel.LevelY;

				//now it is the index of the left most tile in the level map
				subYPrime *= curLevel.LevelWidth;
				
				//now tileindex is the first tile underneith the sprite
				int subX;
				subX = (int)(((int)sprite_in->curX + curRect->left) / 32);

				tileIndex = subYPrime + subX + curLevel.LevelX;

				//init y, which keeps track of our movement down the side of the rectangle
				x = 0;

				//go along the left most edge...and look for collisions in the collision rects
				while (x < (curRect->right - curRect->left)) 
				{
					//is it resting on a Solid block?	
					if (curLevel.LevelTypes[tileIndex] > 2)
					{
						//Yes, realign the sprite
						//onto the tile

						tmpY = ((subY+1) * 32);
						tmpY -= (curRect->top + sprite_in->curY); 

						if (setY == 0 || tmpY > setY) 
						{ 
							setY = tmpY; 
						}
					}

					x += 32;
					tileIndex++;
				}
			}

			if (setY != 0)
			{
				MoveSpriteDown(sprite_in, true, setY, false);
			}
		}
	}
}

void CGameEngine::MoveSpriteDown(CSprite *sprite_in, bool player, double spriteMovement, bool doCollision)
{
	if (player)
	{
		//move player down
		spritePlayerY = (480 - sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteRect.bottom) / 2;

		//check collision rects

		if ((int)sprite_in->curY == spritePlayerY)
		{
			//move level down...
			
			spriteMovement = curLevel.MoveLevelY(spriteMovement);

			if (spriteMovement != 0)
			{
				sprite_in->curY += spriteMovement;
			}
		}
		else if ((int)spritePlayer.curY > spritePlayerY)
		{
			//move player down, from top edge of level

			sprite_in->curY += spriteMovement;
			if ((int)sprite_in->curY < spritePlayerY)
			{
				//we can move the level, reset sprite
				//we move the level the difference

				spriteMovement = (double)spritePlayerY - sprite_in->curY;

				sprite_in->curY = (double)spritePlayerY;

				curLevel.MoveLevelY(spriteMovement);
			}
		}
		else
		{
			//move player down, toward bottom edge of level

			sprite_in->curY += spriteMovement;
			if ((int)sprite_in->curY > spritePlayerY)
			{
				//we can move the level, reset sprite
				//we move the level the difference

				spriteMovement = sprite_in->curY - (double)spritePlayerY;

				sprite_in->curY = (double)spritePlayerY;

				curLevel.MoveLevelY(spriteMovement);
			}				
		}

		if (doCollision)
		{
			//check collision rects for the left
			double newY;
			int subY, subYPrime;

			int tileIndex;

			//get the tile at the top-left corner of collision rectangle
			newY = sprite_in->curY + sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteRect.bottom - curLevel.LevelYOffset;
			subY = (int)newY;

			//this is now the Y coordinate of the tile
			subY /= 32;
			subYPrime = subY + curLevel.LevelY;

			//now it is the index of the left most tile in the level map
			subYPrime *= curLevel.LevelWidth;

			//init x, which keeps track of our movement down the side of the rectangle
			int x = 1;

			double setY;

			bool shouldFall;
			shouldFall = true;

			for ( ; ; )
			{
				//now tileindex is the first tile underneith the sprite
				int subX;
				subX = (int)((((int)sprite_in->curX + sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteBottomEdgeX + x) - curLevel.LevelXOffset) / 32);

				tileIndex = subYPrime + subX + curLevel.LevelX;

				if (tileIndex >= curLevel.maxTileIndex) { return; }
				if (curLevel.LevelTypes[tileIndex] > 1)
				{
					if (curLevel.LevelTypes[tileIndex] == 4)
					{
						//you are dead
						ChangeState(GAMESTATE_PAUSED);

						if (playerStats.curLevel == 4) { SendMessage(windhWnd, WM_CLOSE, 0,0); return; }

						curLevel.LoadLevel(appPath, playerStats.curLevel);

						playerStats.playerScore = 0;
						playerStats.playerHealth = 3;
						playerStats.curDirection = 0; //right .. 1 is left
						playerStats.hasBlueKey = false;
						playerStats.hasRedKey = false;

						spritePlayer.curX = 0;
						spritePlayer.curY = 480-250;

						ChangeState(GAMESTATE_GAME);

						return;
					}
					shouldFall = false;
				}

				if (x == sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteBottomEdgeWidth-1)
				{
					break;
				}

				x += 32;

				if (x > (sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteBottomEdgeWidth-1))
				{
					x = sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteBottomEdgeWidth-1;
				}
				
				tileIndex++;
			}

			if (!shouldFall) 
			{			
				spritePlayerJumpDistanceRemaining = 0;
				//stop falling
				setY = (double)((subY * 32) + curLevel.LevelYOffset);
				setY -= sprite_in->curY + sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteRect.bottom;

				MoveSpriteUp(sprite_in, true, setY, false);
				return;
			}
		}
	}
	else
	{
		//move sprite down
		//check collision rects

		sprite_in->curY += spriteMovement;

		if (doCollision)
		{
			//check collision rects for the left
			double newY;
			int subY, subYPrime;

			int tileIndex;

			//get the tile at the top-left corner of collision rectangle
			newY = sprite_in->curY + sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteRect.bottom;
			subY = (int)newY;

			//this is now the Y coordinate of the tile
			subY /= 32;
			subYPrime = subY;

			//now it is the index of the left most tile in the level map
			subYPrime *= curLevel.LevelWidth;

			//init x, which keeps track of our movement down the side of the rectangle
			int x = 1;

			double setY;

			bool shouldFall;
			shouldFall = true;

			for ( ; ; )
			{
				//now tileindex is the first tile underneith the sprite
				int subX;
				subX = (int)((((int)sprite_in->curX + sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteBottomEdgeX + x)) / 32);

				tileIndex = subYPrime + subX;

				if (curLevel.LevelTypes[tileIndex] > 1)
				{
					shouldFall = false;
				}

				if (x == sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteBottomEdgeWidth-1)
				{
					break;
				}

				x += 32;

				if (x > (sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteBottomEdgeWidth-1))
				{
					x = sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteBottomEdgeWidth-1;
				}
				
				tileIndex++;
			}

			if (!shouldFall) 
			{			
				//stop falling
				setY = (double)((subY * 32));
				setY -= sprite_in->curY + sprite_in->spriteFrames[(int)sprite_in->curFrame].spriteRect.bottom;

				MoveSpriteUp(sprite_in, false, setY, false);
				return;
			}
		}
	}
}

void CGameEngine::PlayerCollisionDetection()
{
	//look at every sprite currently on the screen

	//see if they are having sexual relations with one another
	//aka, the rects are in union

	int i;

	double levelEdgeX, levelEdgeY;

	levelEdgeX = (curLevel.LevelX * 32)	- curLevel.LevelXOffset;
	levelEdgeY = (curLevel.LevelY * 32) - curLevel.LevelYOffset; 

	levelEdgeX += spritePlayer.curX;
	levelEdgeY += spritePlayer.curY;

	//the player's frame
	int sF = (int)spritePlayer.curFrame;

	double levelEdgeX2 = levelEdgeX + spritePlayer.spriteFrames[sF].spriteRect.right;

	double levelEdgeY2 = levelEdgeY + spritePlayer.spriteFrames[sF].spriteRect.bottom;

	int j, k;

	//current rect
	RECT* curRect;
	
	//current player collision rect
	RECT* curPRect;

	double playerX, playerY, playerX2, playerY2;

	RECT unionRect;

	for (i=0; i<curLevel.LevelSpriteCount; i++)
	{
		int cF = (int)curLevel.LevelSprites[i].curFrame;

		//look at every collision rect,
		//if any is in union with any player rect, then
		//we have collided
		
		for (j=0; j<spritePlayer.spriteFrames[sF].rectCount; j++)
		{
			curPRect = &spritePlayer.spriteFrames[sF].rectArray[j];

			playerX = levelEdgeX + curPRect->left;
			playerY = levelEdgeY + curPRect->top;

			playerX2 = levelEdgeX + curPRect->right;
			playerY2 = levelEdgeY + curPRect->bottom;

			double spriteX;
			double spriteY;
			double spriteX2;
			double spriteY2;

			RECT playerRect = {(int)playerX, (int)playerY, (int)playerX2, (int)playerY2};

			//check for union

			if (gameState == GAMESTATE_PAUSED) { return; }

			for (k=0; i<curLevel.LevelSpriteCount, k<curLevel.LevelSprites[i].spriteFrames[cF].rectCount; k++)
			{
				curRect = &curLevel.LevelSprites[i].spriteFrames[cF].rectArray[k];
			
				if (gameState == GAMESTATE_PAUSED) { return; }

				spriteX = curLevel.LevelSprites[i].curX + curRect->left;
				spriteX2 = curLevel.LevelSprites[i].curX + curRect->right;
				
				if (gameState == GAMESTATE_PAUSED) { return; }
				
				spriteY = curLevel.LevelSprites[i].curY + curRect->top;
				spriteY2 = curLevel.LevelSprites[i].curY + curRect->bottom;
				
				if (gameState == GAMESTATE_PAUSED) { return; }

				RECT spriteRect = {(int)spriteX, (int)spriteY, (int)spriteX2, (int)spriteY2};

				//do we collide?
				if (gameState == GAMESTATE_PAUSED) { return; }

				if (IntersectRect(&unionRect, &spriteRect, &playerRect))
				{
					if (PlayerCollidedWith(&curLevel.LevelSprites[i]))
					{
						return;
					}
				}
			}
		}
	}
}

int CGameEngine::PlayerCollidedWith(CSprite *sprite_in)
{
	switch (sprite_in->spriteType)
	{
		case SPRITE_CHALUPA:
			sprite_in->curFrame = 1.0;
			break;
		case SPRITE_REDGATE:
			break;
		case SPRITE_EXIT:
			
			ChangeState(GAMESTATE_PAUSED);

			playerStats.curLevel++;

			if (playerStats.curLevel == 4) { SendMessage(windhWnd, WM_CLOSE, 0,0); return true; }

			curLevel.LoadLevel(appPath, playerStats.curLevel);

			playerStats.playerScore = 0;
			playerStats.playerHealth = 3;
			playerStats.curDirection = 0; //right .. 1 is left
			playerStats.hasBlueKey = false;
			playerStats.hasRedKey = false;

			spritePlayer.curX = 0;
			spritePlayer.curY = 480-250;

			ChangeState(GAMESTATE_GAME);

			return true;
			break;
	}

	return false;
}
