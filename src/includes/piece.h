#ifndef BAAGCHAAL_PIECE
#define BAAGCHAAL_PIECE

class Piece
{
private:
public:
	bool selected;
	void set_color(sf::Sprite& piece_s, sf::Uint8 x, sf::Uint8 y, sf::Uint8 z, sf::Uint8 a = 255);
	void reset_color(sf::Sprite& piece_s);
	void set_position(sf::Sprite& piece_s, int x, int y);
	sf::Vector2f get_position(sf::Sprite& piece_s);
	bool contains_point(sf::Sprite& piece_s, int x, int y);
};

#endif