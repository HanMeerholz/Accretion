#pragma once

namespace Tmpl8 {

class Surface;
class Sprite;
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
	Sprite* blackHole;
	int const blackHoleNrFrames = 30;
	float const blackHoleSpeed = 0.8f;
	float blackHoleX = 100, blackHoleY = 100;
	int curFrame = 0;

	// animation speed in frames per second
	float const animationSpeed = 10.0f;
	float const animationLength = blackHoleNrFrames / animationSpeed;
	float curAnimationTime = 0;
};

}; // namespace Tmpl8