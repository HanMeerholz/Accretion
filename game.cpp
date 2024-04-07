#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cmath>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <numeric>

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

		int const nrAsteroids = 120;

		for (int i = 0; i < nrAsteroids; i++)
		{
			asteroids.push_back(move(makeRandomAsteroidOnScreen()));
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
		
		startButton = new Button(new Surface("assets/start_button.png"), new Surface("assets/start_button.png"), new Surface("assets/start_button.png"));
		startButton->setPosition({ ScreenWidth / 2, ScreenHeight / 2 });
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete blackHole;
		delete blackHoleSprite;
		for (auto& asteroid : asteroids)
			asteroid.reset();
		delete asteroidSprite;
		delete massBar;
		delete score;
		delete startButton;
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


		switch (gameMode) {
		case GameMode::GAMEPLAY:
			handleInput();
			updateGameObjects();
			drawGameObjects();
			drawUI();
			break;
		case GameMode::MENU:
			startButton->draw(screen);
			if (currentTime > 3) gameMode = GameMode::GAMEPLAY;
			break;
		}
		
		currentTime += deltaTime;
	}

	void Game::updateGameObjects() {

		cout << "Nr asteroids: " << asteroids.size() << endl;

		if (!blackHole->isDestroyed())
		{
			blackHole->update();

			for (auto& asteroid : asteroids)
				if (!asteroid->isDestroyed())
					if (asteroid->isConsumedBy(*blackHole))
					{
						score->increaseScore((int)asteroid->getMass());
						blackHole->consumeAsteroid(*asteroid);
					}
		}

		for (auto& asteroid : asteroids)
			if (!asteroid->isDestroyed())
				asteroid->update(*blackHole);

		for (auto& asteroid : asteroids)
			if (asteroid->isDestroyed())
				asteroid.reset(nullptr);
		asteroids.erase(remove(asteroids.begin(), asteroids.end(), nullptr), asteroids.end());

		float totalMass = 0.0f;
		totalMass += blackHole->getMass();
		for (auto const& asteroid : asteroids)
		{
			totalMass += asteroid->getMass();
		}

		float remainingMass = BLACK_HOLE_MAX_MASS - totalMass;
		float maxAsteroidMass = blackHole->getMass() / 10;
		if (remainingMass > maxAsteroidMass)
			asteroids.push_back(move(makeRandomAsteroidOffScreen(blackHole->getMass() / 1000, maxAsteroidMass)));
	}

	unique_ptr<Asteroid> Game::makeRandomAsteroidOnScreen() {
		float x = Rand(ScreenWidth);
		float y = Rand(ScreenHeight);
		float mass = getRandomMass(BLACK_HOLE_START_MASS / 1000, BLACK_HOLE_START_MASS / 20);
		float velocityX = Rand(-1.0f, 1.0f);
		float velocityY = Rand(-1.0f, 1.0f);

		unique_ptr<Asteroid> asteroid(new Asteroid(asteroidSprite, { x, y }, mass, { velocityX, velocityY }));
		return asteroid;
	}

	unique_ptr<Asteroid> Game::makeRandomAsteroidOffScreen(float minMass, float maxMass) {
		
		float x = BRand() ? Rand(-ScreenWidth, 0) : Rand(ScreenWidth, 2 * ScreenWidth);
		float y = BRand() ? Rand(-ScreenHeight, 0) : Rand(ScreenHeight, 2 * ScreenHeight);
		float mass = getRandomMass(minMass, maxMass);
		// asteroid always initially floats towards the center
		float velocityX = x < 0 ? Rand(0.0f, 1.0f) : Rand(-1.0f, 0.0f);
		float velocityY = y < 0 ? Rand(0.0f, 1.0f) : Rand(-1.0f, 0.0f);

		unique_ptr<Asteroid> asteroid(new Asteroid(asteroidSprite, { x, y }, mass, { velocityX, velocityY }));
		return asteroid;
	}

	float Game::getRandomMass(float min, float max) {
		float minExp = log2(min);
		float maxExp = log2(max);
		float massExp = Rand(minExp, maxExp);
		return powf(2.0f, massExp);
	}

	void Game::drawGameObjects()
	{
		if (!blackHole->isDestroyed())
			blackHole->draw(screen, currentTime);

		for (auto& asteroid : asteroids)
			if (!asteroid->isDestroyed())
				asteroid->draw(screen, currentTime);
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