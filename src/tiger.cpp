#include "includes/tiger.h"
Tiger::Tiger()
{
	selected = false;
	tiger_texture.loadFromFile("content/tiger.png");
	tiger_s.setTexture(tiger_texture);
	tiger_s.setOrigin(30, 30);
}
