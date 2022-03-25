#ifndef BAAGCHAAL_TIGER_PIECE
	#define BAAGCHAL_TIGER_PIECE
	#include "piece.h"

class Tiger : public Piece, public sf::Drawable
{
private:
	sf::Texture tiger_texture;
	sf::Sprite tiger_s;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(tiger_s, states);
	}

public:
	Tiger();
	void set_color(sf::Uint8 x, sf::Uint8 y, sf::Uint8 z, sf::Uint8 a)
	{
		Piece::set_color(tiger_s, x, y, z, a);
	}
	void reset_color()
	{
		Piece::reset_color(tiger_s);
	}
	void set_position(int x, int y)
	{
		Piece::set_position(tiger_s, x, y);
	}
	sf::Vector2f get_position()
	{
		return Piece::get_position(tiger_s);
	}
	bool contains_point(int x, int y)
	{
		return Piece::contains_point(tiger_s, x, y);
	}
};

#endif