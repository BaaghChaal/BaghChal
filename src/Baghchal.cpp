#include "includes/Baghchal.h"

Baghchal::Baghchal()
{
	winner = -1;
	window.create(sf::VideoMode(1050, 600), "BaghChal");
	icon.loadFromFile("content/logo.png");
	cursor_img.loadFromFile("content/cursor.png");
	cursor.loadFromPixels(cursor_img.getPixelsPtr(), cursor_img.getSize(), sf::Vector2u(0, 0));
	window.setMouseCursor(cursor);
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void Baghchal::run_home()
{
	Home home;
	Audio audio("content/deep.wav", 30);

	audio.play();

	Text t1("MULTIPLAYER", 370, 270, sf::Color(85, 99, 7), 50, "content/home_font.ttf");
	Text t2("VS TIGER", 410, 335, sf::Color(85, 99, 7), 50, "content/home_font.ttf");
	while (window.isOpen())
	{

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

					winner = run_game(false);
					// std::cout << audio_temp.getStatus();
				}
				if (t2.mouse_clicked(pos))
				{
					winner = run_game(true);
				}
			}
		}

		if (winner != -1)
		{
			sf::sleep(sf::Time(sf::seconds(1.5)));
			winner = win_screen(winner); //inorder to reset winner back to -1
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

int Baghchal::run_game(bool aii)
{
	game.winner = -1;
	Audio audio_temp("content/click.wav", 20);
	audio_temp.set_loop(true);
	audio_temp.play();

	sf::Time t = sf::seconds(0.2);
	sf::sleep(t);
	audio_temp.pause();
	bool ai_piece = aii; //true if AI was selected to play with

	//back button
	Button back_button("content/back.png", sf::Vector2f(900, 100));

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				if (back_button.clicked(pos))
				{
					game.reset();
					ai.reset();
					audio_temp.play();
					sf::sleep(sf::Time(sf::seconds(0.2)));
					return -1;
				}
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
		window.draw(back_button);
		window.display();
		if (game.get_turn() == 1 and ai_piece and game.winner == -1)
		{
			sf::Time t = sf::seconds(1.2f);
			sf::sleep(t);
			ai.find_best_move(game);
			game.update_info_board();
		}
		if (game.winner != -1)
		{
			window.clear();
			window.draw(game);
			window.draw(back_button);
			window.display();
			return game.winner;
		}
	}
	return -1;
}

int Baghchal::win_screen(int winner)
{
	sf::Font font;
	font.loadFromFile("content/test.ttf");
	Audio audio_temp("content/click.wav", 20);
	Audio tiger_win("content/tiger_win.wav", 90);
	Audio goat_win("content/goat_win.wav", 90);
	sf::Text text;
	Button back_button("content/home_button.png", sf::Vector2f(520, 400));
	text.setFont(font);
	text.setPosition(900, 10);
	text.setCharacterSize(34);
	text.setFillColor(sf::Color::Red);

	int win = winner; //Goat-0 Tiger - 1

	sf::Texture texture;
	if (!texture.loadFromFile("content/bg.jpg"))
	{
		std::cout << "Error loading texture" << std::endl;
		system(" pause ");
	}
	sf::Sprite sprite;
	sprite.setTexture(texture);

	std::string winner_path = win == 1 ? "content/bigger_tiger.png" : "content/bigger_goat.png";
	sf::Texture winner_t;
	winner_t.loadFromFile(winner_path);

	sf::Sprite winner_s;
	winner_s.setTexture(winner_t);
	winner_s.setOrigin(100, 100);

	winner_s.setPosition(525, 190);

	Text t1("Tiger Wins", 320, 250, sf::Color(157, 2, 8), 85, "content/test.ttf");
	Text t2("Goat Wins", 320, 250, sf::Color(208, 0, 0), 85, "content/test.ttf");
	win == 1 ? tiger_win.play() : goat_win.play();
	while (window.isOpen())
	{
		sf::Event event;
		window.draw(sprite);
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				sf::Vector2i pos = sf::Mouse::getPosition(window);
				if (back_button.clicked(pos))
				{
					game.reset();
					ai.reset();
					audio_temp.play();
					sf::sleep(sf::Time(sf::seconds(0.2)));
					return -1;
				}
			}
		}
		if (win == 0)
		{
			window.draw(t2);
		}
		else
		{
			window.draw(t1);
		}
		window.draw(winner_s);
		window.draw(text);
		window.draw(back_button);
		window.display();
		window.clear();
	}
	return -1;
}