#pragma once

#include <vector>
#include "template.h"
#include "blackhole.h"
#include "asteroid.h"

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
	Accretion::BlackHole* blackHole;
	std::vector<Accretion::Asteroid*> asteroids;

	Surface* bar;
	Surface* massLeft;
	Surface* massCenter;
	Surface* massRight;
	
	float currentTime = 0;
	int score = 0;

	void handleInput();
};

}; // namespace Tmpl8