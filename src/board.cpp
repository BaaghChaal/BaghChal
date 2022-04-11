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

	goats_ate_t.loadFromFile("content/text4.png");
	turn_t.loadFromFile("content/text2.png");
	goats_ate_s.setTexture(goats_ate_t);
	turn_s.setTexture(turn_t);
	goats_ate_s.setPosition(-20, 0);
	turn_s.setPosition(780, 320);
}

sf::FloatRect Board::grid_dimensions()
{
	return grid_s.getGlobalBounds();
}