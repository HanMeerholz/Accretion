#pragma once

#include <vector>
#include <memory>
#include "uiElement.h"
#include "button.h"

namespace Accretion {
class Menu : public UIElement {
public:
	Menu() = delete;
	Menu(std::vector<std::unique_ptr<Accretion::Button>>&& buttons);
	~Menu();

	void draw(Tmpl8::Surface* screen);
	void update(Tmpl8::intvec2 mousePos, bool mousePressed);
private:
	static int const padding = 5;

	std::vector<std::unique_ptr<Accretion::Button>> buttons;

	static Tmpl8::intvec2 determineDimensions(std::vector<std::unique_ptr<Accretion::Button>>& buttons);
};
}