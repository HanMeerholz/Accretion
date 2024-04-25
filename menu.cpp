#include <numeric>
#include "menu.h"

using namespace std;
using namespace Tmpl8;

namespace Accretion {

Menu::Menu(vector<unique_ptr<Button>>& buttons, intvec2 position) :
	UIElement(determineDimensions(buttons), position), buttons(move(buttons))
{ 
	if (this->buttons.size() == 0) return;

	intvec2 curRelativePosition = { 0, - (getHeight() - this->buttons[0]->getHeight()) / 2};

	for (auto& button : this->buttons)
	{
		curRelativePosition.x = (getWidth() - button->getWidth()) / 2;

		button->setPosition(position + curRelativePosition);

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
	// one padding too many, since padding is only *between* buttons
	height -= padding;
	return { width, height };
}

}