class Button : public sf::Drawable
{
	sf::Texture button_t;
	sf::Sprite button_s;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(button_s, states);
	}

public:
	Button(std::string, sf::Vector2f);
	bool clicked(sf::Vector2i);
	void produce_sound();
};