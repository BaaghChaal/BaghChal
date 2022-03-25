#include "includes/board.h"

Board::Board()
{

	board_t.loadFromFile("content/bg.jpg");
	board_s.setTexture(board_t);

	grid_t.loadFromFile("content/grid.png");
	grid_s.setTexture(grid_t);

	sf::FloatRect rect_b = board_s.getGlobalBounds();
	// sf::FloatRect rect_g = grid_s.getGlobalBounds();

	grid_s.setOrigin(200, 200);
	grid_s.setPosition(rect_b.width / 2, rect_b.height / 2);
}

sf::FloatRect Board::grid_dimensions()
{
	return grid_s.getGlobalBounds();
}