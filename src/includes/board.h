
class Board : public sf::Drawable
{
private:
	sf::Sprite board_s;
	sf::Texture board_t;

	sf::Sprite grid_s;
	sf::Texture grid_t;

	sf::Sprite goats_ate_s;
	sf::Sprite turn_s;
	sf::Texture goats_ate_t;
	sf::Texture turn_t;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(board_s, states);
		target.draw(grid_s, states);
		target.draw(goats_ate_s, states);
		target.draw(turn_s, states);
	}

public:
	Board();
	void set_grid_position();
	sf::FloatRect grid_dimensions();
};