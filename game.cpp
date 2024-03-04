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
			blackHoleY -= blackHoleSpeed;
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			blackHoleX += blackHoleSpeed;
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			blackHoleY += blackHoleSpeed;
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			blackHoleX -= blackHoleSpeed;
		}

		// draw the black hole
		curFrame = (float)(curAnimationTime / animationLength) * blackHoleNrFrames;
		blackHole->SetFrame(curFrame);
		blackHole->Draw(screen, blackHoleX, blackHoleY);

		curAnimationTime += deltaTime;
		if (curAnimationTime > animationLength) curAnimationTime = fmod(curAnimationTime, animationLength);
	}
};