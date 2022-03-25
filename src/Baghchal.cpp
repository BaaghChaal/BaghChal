#include "includes/Baghchal.h"
Baghchal::Baghchal()
{
	window.create(sf::VideoMode(1050, 600), "BaghChal");
}
void Baghchal::run_home()
{
	Home home;
	Audio audio("content/deep.wav", 80);

	audio.play();

	Text t1("MULTIPLAYER", "content/home_font.ttf", sf::Color(85, 99, 7), 50, sf::Vector2f(370, 270));
	Text t2("VS TIGER", "content/home_font.ttf", sf::Color(85, 99, 7), 50, sf::Vector2f(410, 335));
	while (window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				// std::cout << "Key is pressed" << std::endl;
				window.close();
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				if (home.mute_button_clicked(pos.x, pos.y))
				{
					home.change_sound_state(audio);
				}
				if (t1.mouse_clicked(pos))
				{
					run_game(false);
				}
				if (t2.mouse_clicked(pos))
				{
					run_game(true);
				}
			}
		}
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		t1.hover(pos);
		t2.hover(pos);
		window.clear();
		window.draw(home);
		window.draw(t1);
		window.draw(t2);
		window.display();
	}
}

void Baghchal::run_game(bool aii)
{
	sf::Time t = sf::seconds(1);
	sf::sleep(t);
	bool ai_piece = aii;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				if (!game.get_piece_selected() and game.get_turn() and !ai_piece)
				{
					game.select_tiger(pos.x, pos.y);
				}

				else if (!game.get_piece_selected() and game.get_turn() == 0)
				{
					game.select_goat(pos.x, pos.y);
				}
				else
				{
					game.move_piece(pos.x, pos.y);
					//there is win check at the end
				}
			}
		}

		window.clear();
		window.draw(game);
		window.display();
		if (game.get_turn() == 1 and ai_piece)
		{
			sf::Time t = sf::seconds(1.2f);
			sf::sleep(t);
			ai.find_best_move(game);
		}
	}
}
