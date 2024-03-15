#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cmath>
#include <string>
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

using namespace std;
using namespace Accretion;

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		blackHole = new BlackHole(new Sprite(new Tmpl8::Surface("assets/blackhole.png"), 30));

		int const nrAsteroids = 1;

		for (int i = 0; i < nrAsteroids; i++)
		{
			float x = Rand(ScreenWidth);
			float y = Rand(ScreenHeight);
			float radius = Rand(2.0f, 50.0f);
			float velocityX = Rand(-1.0f, 1.0f);
			float velocityY = Rand(-1.0f, 1.0f);

			asteroids.push_back(Asteroid(new Sprite(new Tmpl8::Surface("assets/asteroid.png"), 24), {x, y}, radius, {velocityX, velocityY}));
		}
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
		screen->Clear(BLACK);

		handleInput();
		if (!blackHole->isDestroyed())
		{
			blackHole->update();
			blackHole->draw(screen, currentTime);
			screen->Circle(blackHole->getPosition().x, blackHole->getPosition().y, blackHole->getRadius(), YELLOW);

			for (Asteroid& asteroid : asteroids)
				if (!asteroid.isDestroyed())
				{
					if (asteroid.isConsumedBy(*blackHole))
						blackHole->consumeAsteroid(asteroid);
					asteroid.draw(screen);
				}
		}

		for (Asteroid& asteroid : asteroids)
			if (!asteroid.isDestroyed()) {
				asteroid.update(*blackHole);
				asteroid.draw(screen);
			}
		
		string info = to_string(blackHole->getMass()) + " solar masses";
		screen->Print(info.c_str(), 665, 5, WHITE);
		
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