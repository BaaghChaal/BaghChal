#ifndef HOME
#define HOME

#include "Audio.h"

class Home : public sf::Drawable
{
private:
	sf::Sprite home_s;
	sf::Texture home_t;
	sf::Sprite soundbutton_s;
	sf::Texture soundbutton_t;
	std::string sound_image, play_button;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(home_s, states);
		target.draw(soundbutton_s, states);
	}

public:
	Home();
	void change_sound_state(Audio&);
	void change_play_button();
	bool mute_button_clicked(int, int);
	bool play_button_hover(int, int);
};

#endif