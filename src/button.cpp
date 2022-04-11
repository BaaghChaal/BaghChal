#include "includes/button.h"

Button::Button(std::string path, sf::Vector2f pos)
{
	button_t.loadFromFile(path);
	button_s.setTexture(button_t);
	sf::Rect rect = button_s.getGlobalBounds();
	button_s.setOrigin(rect.width / 2, rect.height / 2);
	button_s.setPosition(pos);
}

bool Button::clicked(sf::Vector2i pos)
{
	return button_s.getGlobalBounds().contains(sf::Vector2f(pos.x, pos.y));
}
void Button::produce_sound()
{
}