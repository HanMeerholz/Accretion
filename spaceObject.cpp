#include "spaceObject.h"
using namespace Tmpl8;

namespace Accretion
{
SpaceObject::SpaceObject(Sprite* sprite, Tmpl8::vec2 position, float mass)
	: GameObject(sprite, position, vec2{calculateRadius(mass) / 2, calculateRadius(mass) / 2}), mass(mass), radius(calculateRadius(mass))
{ }


}
