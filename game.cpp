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
		blackHoleSprite = new Sprite(new Surface("assets/blackhole.png"), 30);
		blackHole = new BlackHole(blackHoleSprite);
		massBar = new ProgressBar(new Surface("assets/empty_bar.png"), new Surface("assets/mass_bar_1.png"), new Surface("assets/mass_bar_2.png"), new Surface("assets/mass_bar_3.png"), 3);

		int const nrAsteroids = 200;
		asteroidSprite = new Sprite(new Surface("assets/asteroid.png"), 24);

		for (int i = 0; i < nrAsteroids; i++)
		{
			float x = Rand(ScreenWidth);
			float y = Rand(ScreenHeight);
			float mass = Rand(BLACK_HOLE_START_MASS / 1000, BLACK_HOLE_START_MASS / 50);
			float velocityX = Rand(-1.0f, 1.0f);
			float velocityY = Rand(-1.0f, 1.0f);

			asteroids.push_back(new Asteroid(asteroidSprite, {x, y}, mass, {velocityX, velocityY}));
		}
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete blackHole;
		delete blackHoleSprite;
		for (Asteroid* asteroid : asteroids)
			delete asteroid;
		delete asteroidSprite;
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
						blackHole->consumeAsteroid(*asteroid, score);
		}

		for (Asteroid* asteroid : asteroids)
			if (!asteroid->isDestroyed()) {
				asteroid->update(*blackHole);
				asteroid->draw(screen, currentTime);
			}

		intvec2 barPos = { (ScreenWidth / 2) - (massBar->getDimensions().x / 2), ScreenHeight - massBar->getDimensions().y - 25 };
		massBar->draw(screen, barPos, blackHole->getMass() / 25000.0f);
		
		stringstream stream;
		stream << fixed << setprecision(1) << blackHole->getMass();
		string nrEarthMasses = stream.str();

		int charSize = 5, paddingSize = 1;
		string info = nrEarthMasses + " earth masses";
		int infoWidth = info.length() * (charSize + paddingSize);
		screen->Print(info.c_str(), ScreenWidth / 2 - infoWidth / 2, 490, WHITE);

		int scoreScale = 5;
		string scoreString = "Score: " + to_string(score);
		int scoreStringWidth = scoreString.length() * scoreScale * (charSize + paddingSize);
		screen->PrintScaled(scoreString.c_str(), ScreenWidth / 2 - scoreStringWidth / 2, 20, YELLOW, scoreScale);
		
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