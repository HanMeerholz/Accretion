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
		initGameObjects();
		initUI();
	}

	void Game::initGameObjects()
	{
		blackHoleSprite = new Sprite(new Surface("assets/blackhole.png"), 30);
		blackHole = new BlackHole(blackHoleSprite);
		asteroidSprite = new Sprite(new Surface("assets/asteroid.png"), 24);

		int const nrAsteroids = 200;

		for (int i = 0; i < nrAsteroids; i++)
		{
			float x = Rand(ScreenWidth);
			float y = Rand(ScreenHeight);
			float mass = Rand(BLACK_HOLE_START_MASS / 1000, BLACK_HOLE_START_MASS / 50);
			float velocityX = Rand(-1.0f, 1.0f);
			float velocityY = Rand(-1.0f, 1.0f);

			asteroids.push_back(new Asteroid(asteroidSprite, { x, y }, mass, { velocityX, velocityY }));
		}
	}

	void Game::initUI()
	{
		massBar = new ProgressBar(new Surface("assets/empty_bar.png"), new Surface("assets/mass_bar_1.png"), new Surface("assets/mass_bar_2.png"), new Surface("assets/mass_bar_3.png"), 3);
		int barBotPadding = 25;
		massBar->setPosition({ (ScreenWidth / 2), ScreenHeight - massBar->getHeight() / 2 - barBotPadding });

		int scoreTopPadding = 20;
		score = new Score(5, YELLOW);
		score->setPosition({ ScreenWidth / 2,  score->getHeight() / 2 + scoreTopPadding });
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
		delete massBar;
		delete score;
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

		drawGameObjects();
		drawUI();
		
		currentTime += deltaTime;
	}

	void Game::drawGameObjects()
	{
		handleInput();
		if (!blackHole->isDestroyed())
		{
			blackHole->update();
			blackHole->draw(screen, currentTime);

			for (Asteroid* asteroid : asteroids)
				if (!asteroid->isDestroyed())
					if (asteroid->isConsumedBy(*blackHole))
					{
						score->increaseScore((int)asteroid->getMass());
						blackHole->consumeAsteroid(*asteroid);
					}
		}

		for (Asteroid* asteroid : asteroids)
			if (!asteroid->isDestroyed()) {
				asteroid->update(*blackHole);
				asteroid->draw(screen, currentTime);
			}
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

	void Game::drawUI()
	{
		massBar->setProgress(blackHole->getMass() / BLACK_HOLE_MAX_MASS);
		massBar->draw(screen);

		stringstream stream;
		stream << fixed << setprecision(1) << blackHole->getMass();
		string nrEarthMasses = stream.str();
		string info = nrEarthMasses + " earth masses";
		int infoWidth = (int)info.length() * (CHAR_WIDTH + CHAR_PADDING);
		int barBotPadding = 25;
		int infoBotPadding = barBotPadding + massBar->getHeight() + CHAR_HEIGHT + 2;
		screen->Print(info.c_str(), ScreenWidth / 2 - infoWidth / 2, ScreenHeight - infoBotPadding, WHITE);

		score->draw(screen);
	}
};