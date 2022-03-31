#include "includes/Text.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <sstream>
int main()
{

	sf::Font font;
	font.loadFromFile("content/test.ttf");

	sf::Text text;
	text.setFont(font);
	text.setPosition(900, 10);
	text.setCharacterSize(34);
	text.setFillColor(sf::Color::Red);

	sf::Clock clock;   // starts the clock
	sf::Time elapsed1; // set time object
	std::stringstream ss;

	sf::RenderWindow window(sf::VideoMode(1050, 600), "test");

	int win = 1; //Goat-0 Tiger - 1

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
	if (!winner_t.loadFromFile(winner_path))
	{
		std::cout << "Status code : 404" << std::endl;
	}
	sf::Sprite winner_s;
	winner_s.setTexture(winner_t);
	winner_s.setOrigin(100, 100);

	winner_s.setPosition(525, 290);

	sf::Texture home_t;
	if (!home_t.loadFromFile("content/home_button.png"))
	{
		std::cout << "Status code : 404" << std::endl;
	}
	sf::Sprite home_s;
	home_s.setTexture(home_t);
	home_s.setOrigin(50, 50);
	home_s.setPosition(525, 450);

	Text t1("Tiger Wins", 525, 250, sf::Color(157, 2, 8), 85, "content/test.ttf");
	Text t2("Goat Wins", 525, 250, sf::Color(208, 0, 0), 85, "content/test.ttf");

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
		}
		if (win == 0)
		{
			window.draw(t2);
		}
		else
		{
			window.draw(t1);
		}
		elapsed1 = clock.getElapsedTime();

		ss.str(std::string()); //clear the string
		ss << elapsed1.asSeconds();

		text.setString(ss.str().c_str());
		window.draw(winner_s);
		window.draw(home_s);
		window.draw(text);
		window.display();
		window.clear();
	}
	return 0;
}
