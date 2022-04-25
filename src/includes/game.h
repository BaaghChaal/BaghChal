#ifndef BAAGCHAAL_GAME
#define BAAGCHAAL_GAME
#include "includes/Audio.h"
#include "includes/board.h"
#include "includes/goat.h"
#include "includes/text.h"
#include "includes/tiger.h"
#include <array>
#include <iterator>
#include <vector>

class Game : public sf::Drawable
{
private:
	Board board;
	bool piece_selected;

	//info texts
	Text goats_ate_text, turn_text, turn_header_text, goats_in_hand_text;
	Audio tiger_audio, goat_audio;
	std::array<Tiger, 4> tigers;
	Tiger* tiger_pointer;

	std::vector<Goat*> goats;
	unsigned int GOATS;
	int goat_no;

	Goat* goat_pointer;
	bool goat_eating_move;
	std::vector<std::vector<sf::Vector2i>> goat_eating_moves;

	//circles
	std::vector<sf::CircleShape> circles;
	std::vector<std::vector<int>> possible_moves;
	int width, lowx, lowy, highx, highy; //grid
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(board, states);
		target.draw(goats_ate_text, states);
		target.draw(goats_in_hand_text, states);
		target.draw(turn_text, states);
		target.draw(turn_header_text, states);
		for (unsigned int i = 0; i < tigers.size(); i++)
		{
			target.draw(tigers[i], states);
		}

		for (Goat* g : goats) //dynamic goat drawing
		{
			target.draw(*g, states);
		}

		for (sf::CircleShape circle : circles) //dynamic goat drawing
		{
			target.draw(circle, states);
		}
	}

public:
	int winner; //1 tiger 0 goat -1 none
	int goats_in_hand;
	std::array<Tiger, 4>* tigers_ptr;
	sf::Vector2i goat_pos4_ai;
	sf::Vector2f goat_pos4_ai_delete_goat_pos;
	void move_tiger_from_ai(sf::Vector2f tiger_pos, sf::Vector2f new_pos);
	int turn; //0-goat, 1-tiger
	int GOATS_KILLED;
	Game();
	void calc_possible_moves(sf::Vector2f point);
	void select_tiger(int x, int y);
	void select_goat(int x, int y);
	void create_circles();
	void move_piece(int x, int y);
	sf::Vector2i nearest_point(int x, int y);
	bool tiger_there(int x, int y);
	bool goat_there(int x, int y);
	bool valid_click(int x, int y);
	void eat_goat_check(int x1, int y1, int x2, int y2);
	void possible_moves_utility(int x, int y);
	void goat_eat_check_utility(int x, int y, int x2, int y2);
	void change_goat_red(int x, int y);
	void delete_goat(sf::Vector2i goat_pos);
	void win();
	int get_turn();
	void update_info_board();
	void play_movement_audio();
	void stop_movement_audio();
	void reset_color_goats();
	bool get_piece_selected();
	void reset();
};

#endif