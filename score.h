#pragma once

#include <string>

#include "template.h"
#include "surface.h"
#include "uiElement.h"

namespace Accretion {

class Score : public UIElement {
public:
	Score(int scale, Tmpl8::Pixel color);

	void increaseScore(int value);

	void draw(Tmpl8::Surface* screen);

private:
	int value = 0;
	int size;
	Tmpl8::Pixel color;

	std::string getString();
};

}