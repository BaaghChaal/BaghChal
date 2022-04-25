#include "Platform/Platform.hpp"
#include "includes/game.h"

using namespace std;
class AI
{
public:
	Tiger* tiger_pointer;
	array<array<char, 5>, 5> board;
	array<array<char, 5>, 5>* ptr;
	sf::Vector2f tiger_pos;
	int goat_killed;
	sf::Vector2f initial_t_pos;
	vector<int> final_goat_ate_pos;
	Audio tiger_audio_ai;

	int lowx, lowy, highx, highy, width;

	AI()
	{
		tiger_audio_ai.create("content/Tiger_game_voice.wav", 40);
		goat_killed = 0;
		board = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' };
		board[0][0] = 'T';
		board[0][4] = 'T';
		board[4][0] = 'T';
		board[4][4] = 'T';

		lowx = 325;
		lowy = 100;
		highx = 725;
		highy = 500;
		width = 100;
	}

	void print_moves(std::vector<std::vector<int>> possible_moves)
	{
		std::cout << "possible moves\n";
		for (auto move : possible_moves)
		{
			std::cout << move[0] << ',' << move[1] << '\n';
		}
	}

	void reset()
	{
		goat_killed = 0;
		board = { '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-', '-' };
		board[0][0] = 'T';
		board[0][4] = 'T';
		board[4][0] = 'T';
		board[4][4] = 'T';
	}

	void print_gmoves(vector<vector<sf::Vector2i>> eating_moves)
	{
		cout << "eating moves\n";
		for (auto move : eating_moves)
		{
			std::cout << move[0].x << ',' << move[0].y << '\n';
		}
	}

	void print_board(array<array<char, 5>, 5> board)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				std::cout << board[i][j] << " ";
			}
			std::cout << '\n';
		}
	}

	vector<vector<int>> calc_goat_moves(array<array<char, 5>, 5> board)
	{
		vector<vector<int>> p_moves;
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (board[i][j] == '-')
				{
					p_moves.push_back({ i, j });
				}
			}
		}
		return p_moves;
	}

	void goat_eat_checker(vector<int> move, vector<vector<sf::Vector2i>> eating_moves, bool& eating_move, vector<int>& ate_move)
	{

		for (auto m : eating_moves)
		{
			if (m[0].x == move[0] and m[0].y == move[1])
			{

				goat_killed += 1;
				(*ptr)[m[1].x][m[1].y] = '-';
				eating_move = true;
				ate_move.push_back(m[1].x);
				ate_move.push_back(m[1].y);
			}
		}
	}

	int evaluate(array<array<char, 5>, 5> board, bool is_max)
	{

		if (is_max)
		{
			vector<vector<int>> t_moves;
			vector<vector<sf::Vector2i>> eating_moves;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (board[i][j] == 'T')
					{
						sf::Vector2f point = denormalize({ i, j });
						calc_possible_moves(t_moves, eating_moves, point, 1);
					}
				}
			}
			return 10 + goat_killed * 50 + eating_moves.size() * 10;
		}
		else
		{
			int count = 0;
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (board[i][j] == 'G')
					{
						count++;
					}
				}
			}

			return -10 - count * 10;
		}
	}

	void find_best_move(Game& game)
	{
		vector<int> goat_move = normalize({ game.goat_pos4_ai.x, game.goat_pos4_ai.y });
		board[goat_move[0]][goat_move[1]] = 'G';

		//if the placement is finished then goat position from before should be removed
		if (game.goats_in_hand == 0)
		{
			vector<int> goat_pos_before = normalize({ int(game.goat_pos4_ai_delete_goat_pos.x), int(game.goat_pos4_ai_delete_goat_pos.y) });
			board[goat_pos_before[0]][goat_pos_before[1]] = '-';
		}

		cout << "initial board\n";
		// print_board(board);

		int best_score = -10000;
		int best_move[2] = { 100, 100 }; //random move for now

		for (Tiger& tiger : *(game.tigers_ptr))
		{
			sf::Vector2f pos = tiger.get_position();
			ptr = &board;
			vector<int> t_pos = normalize({ (int)pos.x, (int)pos.y });

			vector<vector<int>> t_moves;
			vector<vector<sf::Vector2i>> dummy_eating_moves;
			calc_possible_moves(t_moves, dummy_eating_moves, pos, 1);
			normalize_possible_moves(t_moves, dummy_eating_moves);
			print_moves(t_moves);

			for (auto move : t_moves)
			{
				// cout << "initial move: " << move[0] << ',' << move[1] << endl;
				tiger_pos = denormalize(move);
				board[t_pos[0]][t_pos[1]] = '-'; //working with tiger at each position
				board[move[0]][move[1]] = 'T';

				//just for this case
				bool eating_move = false; ///to determined if the move eats a goat
				vector<int> ate_move;

				for (auto e_move : dummy_eating_moves)
				{
					if (move[0] == e_move[0].x and move[1] == e_move[0].y)
					{
						cout << "gooat eaten at " << move[0] << ',' << move[1] << '\n';
						goat_killed += 1;
						ate_move.push_back(e_move[1].x); //pushing the goat_pos which was eaten
						ate_move.push_back(e_move[1].y);
						board[e_move[1].x][e_move[1].y] = '-';
						eating_move = true;
					}
				}

				// goat_eat_checker(move, eating_moves, );
				ptr = &board;
				// print_board(board);
				int score = minimax(board, 0, 2, false);

				// cout << "best score for " << move[0] << ',' << move[1] << '=' << score << endl;
				board[t_pos[0]][t_pos[1]] = 'T'; //reset
				board[move[0]][move[1]] = '-';

				if (score > best_score)
				{
					best_score = score;
					tiger_pointer = &tiger;
					initial_t_pos = tiger_pointer->get_position();
					best_move[0] = move[0];
					best_move[1] = move[1];
					if (eating_move)
						final_goat_ate_pos = ate_move;
				}
				if (eating_move)
				{
					board[ate_move[0]][ate_move[1]] = 'G';
					cout << "gooat returned at " << ate_move[0] << ',' << ate_move[1] << '\n';
					eating_move = false;
					// print_board((board));
					ate_move.clear();
				}

				goat_killed = 0;
			}
		}
		cout << "1m best score" << best_score << best_move[0] << ',' << best_move[0] << "\n";
		board[best_move[0]][best_move[1]] = 'T';
		cout << "2m\n";
		vector<int> initial_tiger = normalize({ int(initial_t_pos.x), int(initial_t_pos.y) });
		board[initial_tiger[0]][initial_tiger[1]] = '-';
		cout << "3m\n";
		if (final_goat_ate_pos.size())
		{
			board[final_goat_ate_pos[0]][final_goat_ate_pos[1]] = '-';
			sf::Vector2f delete_goat_pos = denormalize(final_goat_ate_pos);
			game.delete_goat(sf::Vector2i(delete_goat_pos.x, delete_goat_pos.y)); //to delete goat in the actual board
			final_goat_ate_pos.clear();
		}

		print_board(board);
		cout << "best move " << best_move[0] << ',' << best_move[1] << endl;
		sf::Vector2f final_pos = denormalize({ best_move[0], best_move[1] });
		tiger_audio_ai.play();
		tiger_pointer->set_position(final_pos.x, final_pos.y);
		game.turn = 0;
		game.win();
		// print_board(board);
	}

	int minimax(array<array<char, 5>, 5> board, int depth, int h, bool is_max)
	{
		if (depth == h)
		{
			return evaluate(board, !is_max);
		}
		if (is_max)
		{
			// cout << "maximizing\n";

			int best_score = -10000;
			vector<vector<int>> t_moves;
			vector<vector<sf::Vector2i>> eating_moves;
			calc_possible_moves(t_moves, eating_moves, tiger_pos, 1);
			normalize_possible_moves(t_moves, eating_moves);

			for (auto move : t_moves)
			{
				ptr = &board;
				sf::Vector2f last_pos = tiger_pos;
				vector<int> pos = normalize({ (int)last_pos.x, (int)last_pos.y });

				board[pos[0]][pos[1]] = '-';
				board[move[0]][move[1]] = 'T';

				bool eating_move = false;
				vector<int> ate_move;
				goat_eat_checker(move, eating_moves, eating_move, ate_move);
				// print_board(board);
				int score = minimax(board, depth + 1, h, !is_max);

				// cout << "score : " << score << endl;
				best_score = max(best_score, score);

				// board[pos[0]][pos[1]] = 'T'; //reset

				board[move[0]][move[1]] = '-';
				if (eating_move)
				{
					board[ate_move[0]][ate_move[1]] = 'G';
					eating_move = false;
					ate_move.clear();
					goat_killed -= 1;
				}
			}

			//test
			if (t_moves.size() == 0)
			{
				return -5;
			}
			// cout << "best score " << best_score << endl;
			return best_score;
		}
		else
		{
			// cout << "minimizer\n";
			int best_score = 10000;

			vector<vector<int>> g_moves = calc_goat_moves(board);
			int count = 1;
			for (auto move : g_moves)
			{
				//cout << "goat possible move " << count << endl;
				count++;
				board[move[0]][move[1]] = 'G';
				// print_board(board);
				ptr = &board;
				int score = minimax(board, depth + 1, h, !is_max);
				//cout << "score min : " << score << endl;

				board[move[0]][move[1]] = '-';
				//cout << "reset board for next goat move\n";
				// print_board(board);
				best_score = min(score, best_score);
			}
			// cout << "best score for min " << best_score << endl;
			return best_score;
		}
	}

	void calc_possible_moves(vector<vector<int>>& moves, vector<vector<sf::Vector2i>>& eating_moves, sf::Vector2f point, int turn)
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

						possible_moves_utility(moves, eating_moves, point, x1, y1, turn);
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
						possible_moves_utility(moves, eating_moves, point, x1, y1, turn);
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

	void possible_moves_utility(vector<vector<int>>& moves, vector<vector<sf::Vector2i>>& eating_moves, sf::Vector2f tiger_pos, int x, int y, int turn) //x,y is point of goat on possible moves of tiger
	{
		if (turn and !tiger_there(x, y) and !goat_there(x, y))
		{

			moves.push_back({ x, y });
		}
		if (turn == 0 and !goat_there(x, y) and !tiger_there(x, y))
		{
			moves.push_back({ x, y });
		}
		if (turn and goat_there(x, y))
		{
			eat_goat_check(moves, eating_moves, tiger_pos.x, tiger_pos.y, x, y); //push the goat eating point to possible_moves
		}
	}

	void eat_goat_check(vector<vector<int>>& moves, vector<vector<sf::Vector2i>>& goat_eating_moves, int x1, int y1, int x2, int y2)
	{

		int w = width;
		int slope, px, py;

		slope = std::isinf((y2 - y1) / (float)(x2 - x1)) ? 2 : (y2 - y1) / (x2 - x1);
		if (slope == 0 and x2 > x1)
		{
			px = x2 + w;
			py = y2;
			goat_eat_check_utility(moves, goat_eating_moves, px, py, x2, y2);
		}
		else if (slope == 0 and x2 < x1)
		{
			px = x2 - w;
			py = y2;
			goat_eat_check_utility(moves, goat_eating_moves, px, py, x2, y2);
		}
		else if (slope == -1 and x2 > x1)
		{
			px = x2 + w;
			py = y2 - w;
			goat_eat_check_utility(moves, goat_eating_moves, px, py, x2, y2);
		}
		else if (slope == -1 and x1 > x2)
		{
			px = x2 - w;
			py = y2 + w;
			goat_eat_check_utility(moves, goat_eating_moves, px, py, x2, y2);
		}

		else if (slope == 1 and x2 > x1)
		{
			px = x2 + w;
			py = y2 + w;
			goat_eat_check_utility(moves, goat_eating_moves, px, py, x2, y2);
		}
		else if (slope == 1 and x1 > x2)
		{
			px = x2 - w;
			py = y2 - w;
			goat_eat_check_utility(moves, goat_eating_moves, px, py, x2, y2);
		}
		else if (slope == 2 and y2 > y1)
		{
			px = x2;
			py = y2 + w;
			goat_eat_check_utility(moves, goat_eating_moves, px, py, x2, y2);
		}
		else if (slope == 2 and y1 > y2)
		{
			px = x2;
			py = y2 - w;
			goat_eat_check_utility(moves, goat_eating_moves, px, py, x2, y2);
		}
	}

	void goat_eat_check_utility(vector<vector<int>>& moves, vector<vector<sf::Vector2i>>& eating_moves, int x, int y, int x2, int y2)
	{
		if (!goat_there(x, y) and !tiger_there(x, y) and x >= lowx and y >= lowy and x <= highx and y <= highy)
		{

			moves.push_back({ x, y });
			sf::Vector2i next_pos(x, y);
			sf::Vector2i goat_pos(x2, y2);

			eating_moves.push_back({ next_pos, goat_pos });
		}
	}

	bool tiger_there(int x, int y)
	{
		//normalizing the point
		int b = (x - lowx) / width;
		int a = (y - lowy) / width;
		return ((*ptr)[a][b] == 'T');
	}

	bool goat_there(int x, int y)
	{
		//normalizing the point
		int b = (x - lowx) / width;
		int a = (y - lowy) / width;
		return ((*ptr)[a][b] == 'G');
	}

	void normalize_possible_moves(vector<vector<int>>& possible_moves, vector<vector<sf::Vector2i>>& goat_eating_moves)
	{

		for (unsigned int i = 0; i < possible_moves.size(); i++)
		{
			possible_moves[i] = normalize(possible_moves[i]);
		}

		for (unsigned int i = 0; i < goat_eating_moves.size(); i++)
		{
			sf::Vector2i next_pos = goat_eating_moves[i][0];
			int x1 = next_pos.x;
			int y1 = next_pos.y;
			sf::Vector2i goat_pos = goat_eating_moves[i][1];
			int x2 = goat_pos.x;
			int y2 = goat_pos.y;

			goat_eating_moves[i][0] = sf::Vector2i((y1 - lowy) / width, (x1 - lowx) / width);
			goat_eating_moves[i][1] = sf::Vector2i((y2 - lowy) / width, (x2 - lowx) / width);
		}
	}
	vector<int> normalize(vector<int> point)
	{
		int x = (point[1] - lowy) / width;
		int y = (point[0] - lowx) / width;
		return { x, y };
	}
	sf::Vector2f denormalize(vector<int> point)
	{
		int x = point[1] * width + lowx;
		int y = point[0] * width + lowy;
		return sf::Vector2f(x, y);
	}
};
