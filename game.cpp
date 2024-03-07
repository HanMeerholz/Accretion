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
		blackHole = new Accretion::BlackHole(new Sprite(new Tmpl8::Surface("assets/blackhole.png"), 30));
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete blackHole;
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// get time in seconds
		deltaTime /= 1000;

		// clear the graphics window
		screen->Clear(black);

		handleInput();
		if (!blackHole->isDestroyed())
		{
			blackHole->update();
			blackHole->draw(screen, currentTime);
		}

		currentTime += deltaTime;
	}

	void Game::handleInput()
	{
		if (GetAsyncKeyState(VK_UP))
		{
			blackHole->moveUp();
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			blackHole->moveDown();
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			blackHole->moveLeft();
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			blackHole->moveRight();
		}
	}
};