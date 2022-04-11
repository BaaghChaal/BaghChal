#ifndef BAGHCHAL
#define BAGHCHAL

class Audio
{
private:
	sf::SoundBuffer sound_b;
	sf::Sound sound_s;

public:
	Audio(std::string, float);
	void play();
	void pause();
	void stop();
};
#endif