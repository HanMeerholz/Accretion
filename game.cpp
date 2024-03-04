#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cmath>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		blackHole = new Sprite(new Surface("assets/blackhole.png"), blackHoleNrFrames);


	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// get time in seconds
		deltaTime /= 1000;

		// clear the graphics window
		int black = 0x000000;
		screen->Clear(black);

		// handle input
		if (GetAsyncKeyState(VK_UP))
		{
			blackHolePosition.y -= blackHoleSpeed;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			blackHolePosition.x += blackHoleSpeed;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			blackHolePosition.y += blackHoleSpeed;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			blackHolePosition.x -= blackHoleSpeed;
		}

		// draw the black hole
		curFrame = (float)(curAnimationTime / animationLength) * blackHoleNrFrames;
		blackHole->SetFrame(curFrame);
		blackHole->Draw(screen, blackHolePosition.x, blackHolePosition.y);

		curAnimationTime += deltaTime;
		if (curAnimationTime > animationLength) curAnimationTime = fmod(curAnimationTime, animationLength);
	}
};