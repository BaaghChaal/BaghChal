#include "includes/text.h"

Text::Text()
{}
Text ::Text(std::string text, int x, int y, sf::Color color, int font_size, std::string font_f)
{
	create(text, x, y, color, font_size, font_f);
}
void Text::create(std::string text, int x, int y, sf::Color color, int font_size, std::string font_f)
{
	text_f.loadFromFile(font_f);
	text_t.setFont(text_f);
	text_t.setOutlineThickness(2.5);
	text_t.setOutlineColor(sf::Color(254, 255, 102));
	sf::Rect rect = text_t.getGlobalBounds();
	text_t.setOrigin(rect.width / 2, rect.height / 2);

	text_t.setCharacterSize(font_size);
	text_t.setFillColor(color);

	text_t.setString(text);
	text_t.setPosition(sf::Vector2f(x, y));
}
void Text::set_text(std::string text)
{
	text_t.setString(text);
}
void Text::hover(sf::Vector2i pos)
{
	if (text_t.getGlobalBounds().contains(pos.x, pos.y))
	{
		text_t.setFillColor(sf::Color::Red);
	}
	else
	{
		text_t.setFillColor(sf::Color(85, 99, 7));
	}
}
bool Text::mouse_clicked(sf::Vector2i pos)
{
	return text_t.getGlobalBounds().contains(pos.x, pos.y);
}