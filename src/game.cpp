#include "includes/game.h"

Game::Game() :
	piece_selected(false),
	GOATS(20),
	goat_eating_move(false),
	winner(-1),
	GOATS_KILLED(0)

{
	goat_no = 0;
	goats_in_hand = 20;
	turn = 0;
	sf::FloatRect grid = board.grid_dimensions();
	width = 100;
	std::cout << grid.left << ',' << grid.top << ',' << grid.width << ',' << grid.height << '\n';
	lowx = grid.left;
	lowy = grid.top;
	highx = grid.left + grid.width;
	highy = grid.top + grid.height;

	tigers[0].set_position(lowx, lowy);
	tigers[1].set_position(highx, lowy);
	tigers[2].set_position(lowx, highy);
	tigers[3].set_position(highx, highy);

	tigers_ptr = &tigers;

	//info text
	goats_ate_text.create("GOATS KILLED: 0", 45, 145, sf::Color::Red, 30, "content/home_font.ttf");
	goats_in_hand_text.create("GOATS IN HAND: 20", 35, 230, sf::Color::Red, 30, "content/home_font.ttf");
	turn_text.create("GOAT", 910, 510, sf::Color::Green, 40, "content/home_font.ttf");
	turn_header_text.create("Turn", 890, 400, sf::Color::Red, 70, "content/home_font.ttf");
	//audio
	tiger_audio.create("content/Tiger_game_voice.wav", 40);
	goat_audio.create("content/Goat_game_voice.wav", 40);
}

void Game::calc_possible_moves(sf::Vector2f point)
{
	int px = point.x, py = point.y, w = width, p = 1, q = 1;
	int bitx = ((px - lowx) / w) % 2 == 0 ? 0 : 1;
	int bity = ((py - lowy) / w) % 2 == 0 ? 0 : 1;

	// using XOR as same bit gives 0 and different bits gives 1
	if (bitx ^ bity)
	{
		int p = 1, q = 0;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				int x1 = px + p * ((int)pow(-1, j) * w);
				int y1 = py + q * ((int)pow(-1, j) * w);
				if (x1 >= lowx and y1 >= lowy and x1 <= highx and y1 <= highy)
				{
					// fill the possible_moves vector
					possible_moves_utility(x1, y1);
				}
			}
			p = 0;
			q = 1;
		}
	}

	else
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				int x1 = px + p * ((int)pow(-1, i) * w);
				int y1 = py - q * ((int)pow(-1, i) * w);

				if (x1 >= lowx and y1 >= lowy and x1 <= highx and y1 <= highy)
				{
					// fill the possible_moves vector
					possible_moves_utility(x1, y1);
				}
				if (p && q)
				{
					p = 0;
				}
				else
				{
					p = 1;
					q = q == 1 ? 0 : -1;
				}
			}
			p = 1;
			q = 1;
		}
	}
}

void Game::possible_moves_utility(int x, int y) //x,y is point of goat on possible moves of tiger
{
	if (turn and !tiger_there(x, y) and !goat_there(x, y))
	{
		possible_moves.push_back({ x, y });
	}
	if (turn == 0 and !goat_there(x, y) and !tiger_there(x, y))
	{
		possible_moves.push_back({ x, y });
	}
	if (turn and goat_there(x, y))
	{
		sf::Vector2f tiger_pos = tiger_pointer->get_position();
		eat_goat_check(tiger_pos.x, tiger_pos.y, x, y); //push the goat eating point to possible_moves
	}
}

void Game::select_tiger(int x, int y)
{
	for (int i = 0; i < 4; i++)
	{
		if (tigers[i].contains_point(x, y))
		{
			piece_selected = true;
			tiger_pointer = &tigers[i];
			tiger_pointer->set_color(154, 205, 50, 255);
			calc_possible_moves(tiger_pointer->get_position());
			create_circles();
			break;
		}
	}
}

void Game::select_goat(int x, int y)
{
	//goat placement for initial moves
	if ((unsigned)goat_no < GOATS)
	{

		sf::Vector2i point = nearest_point(x, y);
		if (!tiger_there(point.x, point.y) and !goat_there(point.x, point.y) and point != sf::Vector2i(0, 0))
		{
			goat_no++;
			Goat* goat = new Goat;
			goats.push_back(goat);
			//new line
			goat_pointer = goat;
			goats_in_hand--;
			possible_moves.push_back({ point.x, point.y }); //inorder to make valid_click  while placing goat
			move_piece(x, y);
		}
	}

	//select goat
	else
	{
		for (Goat* goat : goats)
		{
			if (goat->contains_point(x, y))
			{
				piece_selected = true;
				goat_pointer = goat;
				goat->set_color(154, 205, 50, 255);
				calc_possible_moves(goat->get_position());
				create_circles();
				break;
			}
		}
	}
}

void Game::eat_goat_check(int x1, int y1, int x2, int y2)
{
	int w = width;
	int slope, px, py;

	slope = std::isinf((y2 - y1) / (float)(x2 - x1)) ? 2 : (y2 - y1) / (x2 - x1);
	if (slope == 0 and x2 > x1)
	{
		px = x2 + w;
		py = y2;
		goat_eat_check_utility(px, py, x2, y2);
	}
	else if (slope == 0 and x2 < x1)
	{
		px = x2 - w;
		py = y2;
		std::cout << "new move at" << px << ',' << py << '\n';
		goat_eat_check_utility(px, py, x2, y2);
	}
	else if (slope == -1 and x2 > x1)
	{
		px = x2 + w;
		py = y2 - w;
		goat_eat_check_utility(px, py, x2, y2);
	}
	else if (slope == -1 and x1 > x2)
	{
		px = x2 - w;
		py = y2 + w;
		goat_eat_check_utility(px, py, x2, y2);
	}

	else if (slope == 1 and x2 > x1)
	{
		px = x2 + w;
		py = y2 + w;
		goat_eat_check_utility(px, py, x2, y2);
	}
	else if (slope == 1 and x1 > x2)
	{
		px = x2 - w;
		py = y2 - w;
		goat_eat_check_utility(px, py, x2, y2);
	}
	else if (slope == 2 and y2 > y1)
	{
		px = x2;
		py = y2 + w;
		goat_eat_check_utility(px, py, x2, y2);
	}
	else if (slope == 2 and y1 > y2)
	{
		px = x2;
		py = y2 - w;
		goat_eat_check_utility(px, py, x2, y2);
	}
}

void Game::goat_eat_check_utility(int x, int y, int x2, int y2)
{
	if (!goat_there(x, y) and !tiger_there(x, y) and x >= lowx and y >= lowy and x <= highx and y <= highy)
	{

		change_goat_red(x2, y2); //change color of goat to red
		possible_moves.push_back({ x, y });
		sf::Vector2i next_pos(x, y);
		sf::Vector2i goat_pos(x2, y2);

		goat_eating_moves.push_back({ next_pos, goat_pos });
		goat_eating_move = true;
	}
}

void Game::create_circles()
{
	for (std::vector<int> x : possible_moves)
	{
		sf::CircleShape* circle = new sf::CircleShape(10);
		circle->setOrigin(10, 10);
		circle->setPosition(x[0], x[1]);
		circle->setOutlineThickness(2);
		circle->setOutlineColor(sf::Color(139, 59, 19));
		circles.push_back(*circle);
	}
}

void Game::move_piece(int x, int y)
{
	sf::Vector2i point = nearest_point(x, y);
	if (get_turn() == 1 and valid_click(point.x, point.y) and point != sf::Vector2i(0, 0))
	{
		if (goat_eating_move)
		{
			for (auto data : goat_eating_moves)
			{
				sf::Vector2i next_pos = data[0];
				sf::Vector2i goat_pos = data[1];
				if (point == next_pos)
				{
					delete_goat(goat_pos);
				}
			}
			goat_eating_move = false;
			goat_eating_moves.clear(); //to clear the goat eating moves if the tiger chooses to not eat the goat
		}
		tiger_pointer->set_position(point.x, point.y);
		tiger_pointer->reset_color();
		piece_selected = false;
		play_movement_audio();
		turn = 0;
		possible_moves.clear();
		circles.clear();
		reset_color_goats(); //to reset red from goats
	}
	else if (get_turn() and !valid_click(point.x, point.y))
	{
		tiger_pointer->reset_color();
		piece_selected = false;
		possible_moves.clear();
		reset_color_goats();
		circles.clear();
	}
	else if (get_turn() == 0 and valid_click(point.x, point.y))
	{
		goat_pos4_ai_delete_goat_pos = goat_pointer->get_position();
		goat_pointer->set_position(point.x, point.y);
		goat_pointer->reset_color();
		piece_selected = false;
		play_movement_audio();
		turn = 1;
		goat_pos4_ai = (sf::Vector2i(point.x, point.y));
		possible_moves.clear();
		circles.clear();
	}
	else if (get_turn() == 0 and !valid_click(point.x, point.y))
	{
		std::cout << "invalid\n";
		goat_pointer->reset_color();
		piece_selected = false;
		possible_moves.clear();
		circles.clear();
	}
	std::cout << "turn= " << turn << '\n';

	// check win
	win();
	update_info_board();
}

bool Game::valid_click(int x, int y)
{
	for (std::vector<int> point : possible_moves)
	{
		if (point[0] == x and point[1] == y)
		{
			return true;
		}
	}
	return false;
}

sf::Vector2i Game::nearest_point(int x, int y)
{
	sf::Vector2i point;
	int w1 = (int)(0.25 * width);
	int w2 = (int)(0.75 * width);
	int modx = (x - lowx) % width;
	int mody = (y - lowy) % width;
	if ((lowx - 15 <= x and x <= highx) && (lowy - 15 <= y and y <= highy))
	{
		if ((modx <= w1 or modx >= w2) and (mody <= w1 or mody >= w2))
		{
			int posx = round((float)(x - lowx) / width) * width + lowx;
			int posy = round((float)(y - lowy) / width) * width + lowy;
			point.x = posx;
			point.y = posy;
		}
	}
	return point;
}

bool Game::tiger_there(int x, int y)
{

	for (Tiger tiger : tigers)
	{
		if (&tiger != tiger_pointer and tiger.get_position() == sf::Vector2f(x, y))
		{
			return true;
		}
	}
	return false;
}

bool Game::goat_there(int x, int y)
{

	for (Goat* goat : goats)
	{
		if (goat->get_position() == sf::Vector2f(x, y))
		{
			return true;
		}
	}
	return false;
}

void Game::change_goat_red(int x, int y)
{
	for (Goat* goat : goats)
	{
		if (goat->get_position() == sf::Vector2f(x, y))
		{
			goat->set_color(255, 0, 0, 255);
		}
	}
}

void Game::delete_goat(sf::Vector2i goat_pos)
{
	std::vector<Goat*>::iterator it;
	for (it = goats.begin(); it != goats.end();)
	{
		if ((*it)->get_position() == (sf::Vector2f)(goat_pos))
		{
			std::cout << "deleting goat at " << (*it)->get_position().x << ',' << (*it)->get_position().y << '\n';
			delete *it;
			it = goats.erase(it);
			GOATS_KILLED += 1;
			goat_eating_move = false;
		}
		else
		{
			++it;
		}
	}
}

int Game::get_turn()
{
	return turn;
}

void Game::update_info_board()
{
	//to convert numbers to string;
	std::ostringstream text;

	text << GOATS_KILLED;
	std::string head = "GOATS KILLED: ";
	goats_ate_text.set_text(head + text.str());
	std::ostringstream text2;
	text2 << goats_in_hand;
	head = "GOATS IN HAND: ";
	goats_in_hand_text.set_text(head + text2.str());

	std::string t = turn == 1 ? "TIGER" : "GOAT";
	turn_text.set_text(t);
}

void Game::play_movement_audio()
{
	if (turn)
	{
		tiger_audio.play();
	}
	else
	{
		goat_audio.play();
	}
}

void Game::stop_movement_audio()
{
	sf::Time t = sf::seconds(1.5);
	sf::sleep(t);
	tiger_audio.stop();
	goat_audio.stop();
}

void Game::win()
{
	//tiger win check
	if (GOATS_KILLED == 5)
	{
		std::cout << "TIGERS WON\n";
		winner = 1;
		turn = -1;
	}

	//goat win check
	int temp_turn = turn;
	turn = 1;

	for (unsigned int i = 0; i < tigers.size(); i++)
	{
		tiger_pointer = &tigers[i];
		calc_possible_moves(tigers[i].get_position());
	}

	std::cout << possible_moves.size() << '\n';
	if (possible_moves.size() == 0)
	{
		std::cout << "GOATS WON\n";
		winner = 0;
		turn = -1;
	}

	reset_color_goats();
	goat_eating_moves.clear();
	goat_eating_move = false;
	possible_moves.clear();
	turn = temp_turn;
}

void Game::reset_color_goats()
{
	for (Goat* goat : goats)
	{
		goat->reset_color();
	}
}

void Game::move_tiger_from_ai(sf::Vector2f tiger_pos, sf::Vector2f new_pos)
{
	for (auto tiger : tigers)
	{
		if (tiger.get_position() == tiger_pos)
		{
			tiger.set_position(new_pos.x, new_pos.y);
			break;
		}
	}
}

bool Game::get_piece_selected()
{
	return piece_selected;
}

void Game::reset()
{
	goats.clear();
	possible_moves.clear();
	goat_eating_moves.clear();
	turn = 0;
	tigers[0].set_position(lowx, lowy);
	tigers[1].set_position(highx, lowy);
	tigers[2].set_position(lowx, highy);
	tigers[3].set_position(highx, highy);
	winner = -1;
	GOATS_KILLED = 0;
	goat_eating_move = false;
	piece_selected = false;
	goats_in_hand = 20;
	goat_no = 0;
	update_info_board();
}