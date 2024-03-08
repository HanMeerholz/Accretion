#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cmath>
#include <string>

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

		int const nrAsteroids = 20;

		for (int i = 0; i < nrAsteroids; i++)
		{
			float x = Rand(ScreenWidth);
			float y = Rand(ScreenHeight);
			float radius = Rand(5.0f, 50.0f);

			asteroids.push_back(Asteroid(vec2(x, y), radius));
		}
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete blackHole;
	}

	bool circle1IsInCircle2(float c1x, float c1y, float c1r, float c2x, float c2y, float c2r)
	{
		float distance = sqrt(pow(c1x - c2x, 2) + pow(c1y - c2y, 2));
		return distance + c1r < c2r;
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
		}
		
		for (Asteroid& asteroid : asteroids)
		{
			if (!asteroid.isDestroyed())
			{
				if (circle1IsInCircle2(asteroid.getPosition().x, asteroid.getPosition().y, asteroid.getRadius(), blackHole->getPosition().x, blackHole->getPosition().y, blackHole->getRadius()))
				{
					asteroid.setDestroyed();
					blackHole->addMass(0.0001f * asteroid.getRadius());
				}
				asteroid.draw(screen);
			}
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