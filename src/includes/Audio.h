#ifndef BAGHCHAL
#define BAGHCHAL

class Audio
{
private:
	sf::SoundBuffer sound_b;
	sf::Sound sound_s;

public:
	Audio();
	Audio(std::string, float);
	void create(std::string, float);
	void play();
	void pause();
	void stop();
	void set_loop(bool x);
};
#endif