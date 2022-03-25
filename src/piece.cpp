#include "includes/piece.h"

void Piece::set_color(sf::Sprite& piece_s, sf::Uint8 x, sf::Uint8 y, sf::Uint8 z, sf::Uint8 a)
{
	sf::Color color { x, y, z, a };
	piece_s.setColor(color);
}
void Piece::reset_color(sf::Sprite& piece_s)
{
	piece_s.setColor(sf::Color::White);
}

void Piece::set_position(sf::Sprite& piece_s, int x, int y)
{
	piece_s.setPosition(x, y);
}
sf::Vector2f Piece::get_position(sf::Sprite& piece_s)
{
	return piece_s.getPosition();
}
bool Piece::contains_point(sf::Sprite& piece_s, int x, int y)
{

	sf::FloatRect boundaryBox = piece_s.getGlobalBounds();
	if (boundaryBox.contains(x, y))
		return true;
	return false;
}
