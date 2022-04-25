#include "AI.cpp"

#include "includes/Home_Page.h"
#include "includes/button.h"
#include "includes/game.h"

using namespace std;

class Baghchal
{
	sf::RenderWindow window;
	sf::Image icon;
	sf::Image cursor_img;
	sf::Cursor cursor;
	Game game;
	sf::Event event;
	AI ai;
	int winner;

public:
	Baghchal();
	void main_loop();
	void run_home();
	int run_game(bool);
	int win_screen(int);
};