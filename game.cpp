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
		bar = new Surface("assets/empty_bar.png");
		massLeft = new Surface("assets/mass_bar_1.png");
		massCenter = new Surface("assets/mass_bar_2.png");
		massRight = new Surface("assets/mass_bar_3.png");

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
		delete bar;
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

		float scale = blackHole->getMass() / 25000.0f;

		int barPosX = (ScreenWidth / 2) - (bar->GetWidth() / 2);
		int barPosY = ScreenHeight - bar->GetHeight() - 25;
		bar->CopyTo(screen, barPosX, barPosY);
		massLeft->CopyTo(screen, barPosX + 3, barPosY + 3);
		massCenter->DrawScaled(screen, barPosX + 3 + massLeft->GetWidth(), barPosY + 3, massCenter->GetWidth() * scale, massCenter->GetHeight());
		massRight->CopyTo(screen, barPosX + 3 + massLeft->GetWidth() + massCenter->GetWidth() * scale, barPosY + 3);
		
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