#include <string>
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
	Text(std::string, int, int, sf::Color, int, std::string); //winner,x_pos,y_pos,text_color,font_size,font_family
};

// Text t1("fgjfkg",200,300,color,"font")