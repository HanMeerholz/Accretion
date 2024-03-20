#pragma once

#include <vector>
#include "template.h"
#include "blackhole.h"
#include "asteroid.h"
#include "progressBar.h"

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
	std::vector<Accretion::Asteroid*> asteroids;

	Accretion::ProgressBar* massBar;
	
	float currentTime = 0;
	int score = 0;

	void handleInput();
};

}; // namespace Tmpl8