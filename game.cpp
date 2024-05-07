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
#define DEBUG_MODE (defined DEBUG || defined _DEBUG)

#include <windows.h>
#include <SDL.h>


using namespace std;
using namespace Accretion;

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		background = new Surface("assets/starry_background.png");
		initGameObjects();
		initUI();
	}

	void Game::initGameObjects()
	{
		blackHoleSprite = new Sprite(new Surface("assets/blackhole.png"), 30);
		blackHoleDeathSprite = new Sprite(new Surface("assets/implosion.png"), 60);
		blackHole = new BlackHole(blackHoleSprite, blackHoleDeathSprite);
		asteroidSprite = new Sprite(new Surface("assets/asteroid.png"), 24);
	}

	void Game::initUI()
	{
		massBar = new ProgressBar(new Surface("assets/empty_bar.png"), new Surface("assets/mass_bar_1.png"), new Surface("assets/mass_bar_2.png"), new Surface("assets/mass_bar_3.png"), 3);
		int barBotPadding = 25;
		massBar->setPosition({ (ScreenWidth / 2), ScreenHeight - massBar->getHeight() / 2 - barBotPadding });

		int scoreTopPadding = 20;
		score = new Score(5, YELLOW);
		score->setPosition({ ScreenWidth / 2,  score->getHeight() / 2 + scoreTopPadding });

		initMainMenu();
		initGameOverMenu();
	}

	void Game::initMainMenu()
	{
		vector<unique_ptr<Button>> mainMenuButtons;

		unique_ptr<Button> startButton(new Button(new Surface("assets/start_button.png"), new Surface("assets/start_button_hover.png"), new Surface("assets/start_button_pressed.png"),
			[&] {
				reset();
				gameMode = GameMode::GAMEPLAY;
			}));
		mainMenuButtons.push_back(move(startButton));
		mainMenuButtons.push_back(move(createExitButton()));

		mainMenu = new Menu(move(mainMenuButtons), { ScreenWidth / 2, ScreenHeight / 2 });
	}

	void Game::initGameOverMenu()
	{
		vector<unique_ptr<Button>> gameOverButtons;

		unique_ptr<Button> restartButton(new Button(new Surface("assets/restart_button.png"), new Surface("assets/restart_button_hover.png"), new Surface("assets/restart_button_pressed.png"),
			[&] {
				reset();
				gameMode = GameMode::GAMEPLAY;
			}));
		gameOverButtons.push_back(move(restartButton));
		gameOverButtons.push_back(move(createExitButton()));

		gameOverMenu = new Menu(move(gameOverButtons), { ScreenWidth / 2, ScreenHeight / 2 });
	}

	unique_ptr<Button> Game::createExitButton()
	{
		unique_ptr<Button> exitButton(new Button(new Surface("assets/exit_button.png"), new Surface("assets/exit_button_hover.png"), new Surface("assets/exit_button_pressed.png"),
			[&] {
				SDL_Event sdlevent = {};
				sdlevent.type = SDL_KEYDOWN;
				sdlevent.key.keysym.sym = SDLK_ESCAPE;
				SDL_PushEvent(&sdlevent);
			}));
		return exitButton;
	}

	void Game::reset()
	{
		blackHole->reset();

		for (auto& asteroid : asteroids)
			asteroid.reset(nullptr);
		asteroids.erase(remove(asteroids.begin(), asteroids.end(), nullptr), asteroids.end());

		initAsteroids();

		score->reset();
	}

	void Game::initAsteroids()
	{
		int const nrAsteroids = 120;

		for (int i = 0; i < nrAsteroids; i++)
			asteroids.push_back(move(makeRandomAsteroidOnScreen()));
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete background;

		// delete black hole
		delete blackHole;
		delete blackHoleSprite;
		delete blackHoleDeathSprite;

		// delete asteroids
		for (auto& asteroid : asteroids)
			asteroid.reset();
		delete asteroidSprite;

		// delete ui
		delete massBar;
		delete score;
		delete mainMenu;
		delete gameOverMenu;
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// get time in seconds
		deltaTime /= 1000;
		// set the background
		background->CopyTo(screen, (ScreenWidth - background->GetWidth()) / 2, (ScreenHeight - background->GetHeight()) / 2);

		switch (gameMode) {
		case GameMode::GAMEPLAY:
			handleInput();
			updateGameObjects(deltaTime);
			drawGameObjects();
			drawUI();
			break;
		case GameMode::MENU:
			mainMenu->update(mousePos, GetAsyncKeyState(VK_LBUTTON));
			mainMenu->draw(screen);
			break;
		case GameMode::DEATH:
			updateGameObjects(deltaTime);
			gameOverMenu->update(mousePos, GetAsyncKeyState(VK_LBUTTON));
			drawGameObjects();
			drawUI();
			gameOverMenu->draw(screen);
			break;
		}
		
		currentTime += deltaTime;
	}

	void Game::handleInput()
	{
		vec2 direction = { 0.0f, 0.0f };
		if (upPressed) direction.y -= 1;
		if (downPressed) direction.y += 1;
		if (leftPressed) direction.x -= 1;
		if (rightPressed) direction.x += 1;

		if (direction.length() >= 0.1f) direction.normalize();
		blackHole->setDirection(direction);
	}

	void Game::updateGameObjects(float deltaTime) {
		blackHole->update(deltaTime);

		if (!blackHole->isDestroyed())
			for (auto& asteroid : asteroids)
				if (!asteroid->isDestroyed())
					if (asteroid->isConsumedBy(*blackHole))
					{
						score->increaseScore((int)asteroid->getMass());
						blackHole->consumeAsteroid(*asteroid);
					}

		for (auto& asteroid : asteroids)
			if (!asteroid->isDestroyed())
				asteroid->update(*blackHole, deltaTime);

		for (auto& asteroid : asteroids)
			if (asteroid->isDestroyed())
				asteroid.reset(nullptr);
		asteroids.erase(remove(asteroids.begin(), asteroids.end(), nullptr), asteroids.end());

		if (!blackHole->isDestroyed())
		{
			float totalMass = 0.0f;
			totalMass += blackHole->getMass();
			for (auto const& asteroid : asteroids)
				totalMass += asteroid->getMass();

			float remainingMass = BlackHole::MAX_MASS - totalMass;
			float maxAsteroidMass = blackHole->getMass() / 10;
			if (remainingMass > maxAsteroidMass)
				asteroids.push_back(move(makeRandomAsteroidOffScreen(blackHole->getMass() / 1000, maxAsteroidMass)));
		}

		if (blackHole->getPhase() == BlackHole::EXPLODED)
			gameMode = GameMode::DEATH;
	}

	unique_ptr<Asteroid> Game::makeRandomAsteroidOnScreen() {
		float x = Rand(ScreenWidth);
		float y = Rand(ScreenHeight);
		float mass = getRandomMass(BlackHole::START_MASS / 1000, BlackHole::START_MASS / 20);
		float velocityX = Rand(-100.0f, 100.0f);
		float velocityY = Rand(-100.0f, 100.0f);

		unique_ptr<Asteroid> asteroid(new Asteroid(asteroidSprite, { x, y }, mass, { velocityX, velocityY }));
		return asteroid;
	}

	unique_ptr<Asteroid> Game::makeRandomAsteroidOffScreen(float minMass, float maxMass) {
		float x = BRand() ? Rand(-ScreenWidth, 0) : Rand(ScreenWidth, 2 * ScreenWidth);
		float y = BRand() ? Rand(-ScreenHeight, 0) : Rand(ScreenHeight, 2 * ScreenHeight);
		float mass = getRandomMass(minMass, maxMass);
		// asteroid always initially floats towards the center
		float velocityX = x < 0 ? Rand(0.0f, 100.0f) : Rand(-100.0f, 0.0f);
		float velocityY = y < 0 ? Rand(0.0f, 100.0f) : Rand(-100.0f, 0.0f);

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
		for (auto& asteroid : asteroids)
			if (!asteroid->isDestroyed())
				asteroid->draw(screen);

		blackHole->draw(screen);
	}

	void Game::drawUI()
	{
		bool isDestroyed = blackHole->isDestroyed();

		massBar->setProgress(blackHole->getMass() / BlackHole::MAX_MASS);
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

	void Game::KeyDown(int key)
	{
		switch (key) {
		case SDL_SCANCODE_UP:
			if (!upPressed) upPressed = true;
			break;
		case SDL_SCANCODE_DOWN:
			if (!downPressed) downPressed = true;
			break;
		case SDL_SCANCODE_LEFT:
			if (!leftPressed) leftPressed = true;
			break;
		case SDL_SCANCODE_RIGHT:
			if (!rightPressed) rightPressed = true;
			break;
#if DEBUG_MODE
		case SDL_SCANCODE_K:
			blackHole->setPhase(BlackHole::IMPLODING);
			break;
#endif
		}
	}

	void Game::KeyUp(int key)
	{
		switch (key) {
		case SDL_SCANCODE_UP:
			if (upPressed) upPressed = false;
			break;
		case SDL_SCANCODE_DOWN:
			if (downPressed) downPressed = false;
			break;
		case SDL_SCANCODE_LEFT:
			if (leftPressed) leftPressed = false;
			break;
		case SDL_SCANCODE_RIGHT:
			if (rightPressed) rightPressed = false;
			break;
		}
	}
};