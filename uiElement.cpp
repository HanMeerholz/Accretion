#include "uiElement.h"

using namespace Tmpl8;

namespace Accretion {
UIElement::UIElement(intvec2 dimensions):
	UIElement(dimensions, {0, 0})
{}

UIElement::UIElement(intvec2 dimensions, intvec2 position):
	dimensions(dimensions), position(position)
{}

intvec2 UIElement::getDimensions()
{
	return dimensions;
}

int UIElement::getWidth()
{
	return dimensions.x;
}

int UIElement::getHeight()
{
	return dimensions.y;
}

void UIElement::setPosition(Tmpl8::intvec2 position)
{
	this->position = position;
}

Tmpl8::intvec2 UIElement::getTopLeftPosition()
{
	return { position.x - dimensions.x / 2, position.y - dimensions.y / 2 };
}

}