// #include "includes/board.h"

// Board::Board()
// {

// 	board_t.loadFromFile("content/bg.jpg");
// 	board_s.setTexture(board_t);

// 	grid_t.loadFromFile("content/grid.png");
// 	grid_s.setTexture(grid_t);

// 	sf::FloatRect rect_b = board_s.getGlobalBounds();
// 	// sf::FloatRect rect_g = grid_s.getGlobalBounds();

// 	grid_s.setOrigin(200, 200);
// 	grid_s.setPosition(rect_b.width / 2, rect_b.height / 2);
// }

// sf::FloatRect Board::grid_dimensions()
// {
// 	return grid_s.getGlobalBounds();
// }

#include "includes/Text.h"
Text ::Text(std::string text, int x_pos, int y_pos, sf::Color color, int font_size, std::string font)
{

	if (!text_f.loadFromFile(font))
	{
		std::cout << "Couldn't load font" << std::endl;
	}
	text_t.setCharacterSize((unsigned int)(font_size));
	text_t.setFont(text_f);
	text_t.setString(text);
	text_t.setPosition(x_pos, y_pos);
	text_t.setOutlineColor(sf::Color::Cyan);
	text_t.setOutlineThickness(2);

	text_t.setFillColor(color);
	sf::Rect rect = text_t.getGlobalBounds();
	text_t.setOrigin(rect.width / 2, (rect.height / 2) + 150);
}