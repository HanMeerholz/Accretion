#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

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
		blackHole = new BlackHole(new Sprite(new Surface("assets/blackhole.png"), 30));

		int const nrAsteroids = 200;

		for (int i = 0; i < nrAsteroids; i++)
		{
			float x = Rand(ScreenWidth);
			float y = Rand(ScreenHeight);
			float mass = Rand(BLACK_HOLE_START_MASS / 1000, BLACK_HOLE_START_MASS / 50);
			float velocityX = Rand(-1.0f, 1.0f);
			float velocityY = Rand(-1.0f, 1.0f);

			asteroids.push_back(new Asteroid(new Sprite(new Surface("assets/asteroid.png"), 24), {x, y}, mass, {velocityX, velocityY}));
		}
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete blackHole;
		for (Asteroid* asteroid : asteroids)
			delete asteroid;
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

			for (Asteroid* asteroid : asteroids)
				if (!asteroid->isDestroyed())
					if (asteroid->isConsumedBy(*blackHole))
						blackHole->consumeAsteroid(*asteroid);
		}

		for (Asteroid* asteroid : asteroids)
			if (!asteroid->isDestroyed()) {
				asteroid->update(*blackHole);
				asteroid->draw(screen, currentTime);
			}
		
		stringstream stream;
		stream << fixed << setprecision(1) << blackHole->getMass();
		string nrEarthMasses = stream.str();

		string info = nrEarthMasses + " earth masses";
		screen->Print(info.c_str(), 660, 5, WHITE);
		
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