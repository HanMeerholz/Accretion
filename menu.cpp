#include <numeric>
#include "menu.h"

using namespace std;
using namespace Tmpl8;

namespace Accretion {

Menu::Menu(vector<unique_ptr<Button>>&& buttons) :
	UIElement(determineDimensions(buttons)), buttons(move(buttons))
{ 
	intvec2 curRelativePosition = { 0, 0 };

	for (auto& button : this->buttons)
	{
		curRelativePosition.x = (getWidth() - button->getWidth()) / 2;

		button->setPosition(getTopLeftPosition() + curRelativePosition);

		curRelativePosition.y += button->getHeight() + padding;
	}
}

Menu::~Menu()
{
	for (auto& button : buttons)
		button.reset();
}

void Menu::draw(Surface* screen)
{
	for (auto& button : buttons) {
		button->draw(screen);
	}
}

void Menu::update(Tmpl8::intvec2 mousePos, bool mousePressed)
{
	for (auto& button : buttons) {
		button->update(mousePos, mousePressed);
	}
}

intvec2 Menu::determineDimensions(vector<unique_ptr<Button>>& buttons)
{
	int height = 0;
	int width = 0;
	for (auto& button : buttons)
	{
		height += button->getHeight() + padding;
		int buttonWidth = button->getWidth();
		if (buttonWidth > width) width = buttonWidth;
	}
	return { height, width };
}

}