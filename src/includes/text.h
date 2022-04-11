class Text : public sf::Drawable
{
private:
	std::string text; //Tiger wins or goat wins

	sf::Font text_f;
	sf::Text text_t;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(text_t, states);
	}

public:
	Text();
	Text(std::string text, int x, int y, sf::Color color, int size, std::string font);
	void hover(sf::Vector2i pos);
	void create(std::string text, int x, int y, sf::Color color, int size, std::string font);
	void set_text(std::string);
	bool mouse_clicked(sf::Vector2i pos);
};