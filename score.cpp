#include <string>

#include "score.h"

using namespace Tmpl8;
using namespace std;

namespace Accretion {
	Score::Score(int size, Pixel color)
		:
		size(size), color(color)
	{
		dimensions = { (int)getString().length() * size * (CHAR_WIDTH + CHAR_PADDING), size * CHAR_HEIGHT };
	}

	void Score::increaseScore(int value)
	{
		this->value += value;
		dimensions = { (int) getString().length() * size * (CHAR_WIDTH + CHAR_PADDING), size * CHAR_HEIGHT };
	}

	void Score::draw(Surface* screen)
	{
		intvec2 topLeftPosition = getTopLeftPosition();
		screen->PrintScaled(getString().c_str(), topLeftPosition.x, topLeftPosition.y, color, size);
	}

	std::string Score::getString()
	{
		return "Score: " + to_string(value);
	}
}