#include <string>

#include "score.h"

using namespace Tmpl8;
using namespace std;

namespace Accretion {
	Score::Score(int size, Pixel color)
		:
	    UIElement(intvec2{ 10 * size* (CHAR_WIDTH + CHAR_PADDING), size* CHAR_HEIGHT }),
		size(size), color(color)
	{}

	void Score::increaseScore(int value)
	{
		this->value += value;
		dimensions = { (int) getString().length() * size * (CHAR_WIDTH + CHAR_PADDING), size * CHAR_HEIGHT };
	}

	void Score::reset()
	{
		this->value = 0.0f;
	}

	void Score::draw(Surface* screen)
	{
		intvec2 topLeftPosition = getTopLeftPosition();
		screen->PrintScaled(getString().c_str(), topLeftPosition.x, topLeftPosition.y, color, size);
	}

	string Score::getString()
	{
		return "Score: " + to_string(value);
	}
}