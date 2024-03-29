#pragma once

#include <vector>
#include <memory>
#include "template.h"
#include "blackhole.h"
#include "asteroid.h"
#include "progressBar.h"
#include "score.h"

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
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
	Sprite* blackHoleSprite;
	Accretion::BlackHole* blackHole;
	Sprite* asteroidSprite;
	std::vector<std::unique_ptr<Accretion::Asteroid>> asteroids;

	Accretion::ProgressBar* massBar;
	Accretion::Score* score;
	
	float currentTime = 0;

	void initGameObjects();
	std::unique_ptr<Accretion::Asteroid> makeRandomAsteroid();
	std::unique_ptr<Accretion::Asteroid> makeRandomAsteroidOffScreen();
	void initUI();

	void handleInput();
	void updateGameObjects();
	void drawGameObjects();
	void drawUI();
};

}; // namespace Tmpl8