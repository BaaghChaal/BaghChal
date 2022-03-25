#ifndef BAAGCHAAL_GOAT_PIECE
	#define BAAGCHAL_GOAT_PIECE
	#include "piece.h"

class Goat : public Piece, public sf::Drawable
{
private:
	sf::Texture goat_texture;
	sf::Sprite goat_s;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(goat_s, states);
	}

public:
	Goat();
	~Goat(){};
	void set_color(sf::Uint8 x, sf::Uint8 y, sf::Uint8 z, sf::Uint8 a)
	{
		Piece::set_color(goat_s, x, y, z, a);
	}
	void reset_color()
	{
		Piece::reset_color(goat_s);
	}
	void set_position(int x, int y)
	{
		Piece::set_position(goat_s, x, y);
	}
	sf::Vector2f get_position()
	{
		return Piece::get_position(goat_s);
	}
	bool contains_point(int x, int y)
	{
		return Piece::contains_point(goat_s, x, y);
	}
	sf::Color get_color()
	{
		return goat_s.getColor();
	}
};

#endif