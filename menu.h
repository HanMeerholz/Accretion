#pragma once

#include <vector>
#include <memory>
#include "uiElement.h"
#include "button.h"

namespace Accretion {
class Menu : public UIElement {
public:
	Menu() = delete;
	Menu(std::vector<std::unique_ptr<Accretion::Button>>& buttons, Tmpl8::intvec2 position);
	~Menu();

	void update(Tmpl8::intvec2 mousePos, bool mousePressed);
	void draw(Tmpl8::Surface* screen);
private:
	static int constexpr BUTTON_PADDING = 50;

	std::vector<std::unique_ptr<Accretion::Button>> buttons;

	static Tmpl8::intvec2 determineDimensions(std::vector<std::unique_ptr<Accretion::Button>>& buttons);
};
}