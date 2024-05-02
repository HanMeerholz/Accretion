#pragma once

#include <vector>
#include <memory>
#include "template.h"
#include "blackhole.h"
#include "asteroid.h"
#include "progressBar.h"
#include "score.h"
#include "menu.h"
#include "gamemode.h"

namespace Tmpl8 {

class Surface;
class Game
{

public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y) { mousePos.x = x; mousePos.y = y; }
	void KeyUp(int key);
	void KeyDown(int key);
private:
	Surface* screen;
	Sprite* blackHoleSprite;
	Sprite* blackHoleDeathSprite;
	Accretion::BlackHole* blackHole;
	Sprite* asteroidSprite;
	std::vector<std::unique_ptr<Accretion::Asteroid>> asteroids;

	Accretion::GameMode gameMode = Accretion::GameMode::MENU;
	Accretion::ProgressBar* massBar;
	Accretion::Score* score;

	Accretion::Menu* mainMenu;

	bool upPressed = false, downPressed = false, leftPressed = false, rightPressed = false;

	Tmpl8::intvec2 mousePos = { 0, 0 };
	
	float currentTime = 0;

	void initGameObjects();
	std::unique_ptr<Accretion::Asteroid> makeRandomAsteroidOnScreen();
	std::unique_ptr<Accretion::Asteroid> makeRandomAsteroidOffScreen(float minMass, float maxMass);
	float getRandomMass(float min, float max);
	void initUI();

	void handleInput();
	void updateGameObjects(float deltaTime);
	void drawGameObjects();
	void drawUI();
};

}; // namespace Tmpl8