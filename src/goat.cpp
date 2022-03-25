#include "includes/goat.h"
Goat::Goat()
{
	selected = false;
	goat_texture.loadFromFile("content/goat.png");
	goat_s.setTexture(goat_texture);
	goat_s.setOrigin(25, 25);
}
