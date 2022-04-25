#include "includes/Audio.h"
Audio::Audio()
{}
Audio ::Audio(std::string sound_path, float volume)
{
	create(sound_path, volume);
}
void Audio::create(std::string sound_path, float volume)
{
	sound_b.loadFromFile(sound_path);
	sound_s.setBuffer(sound_b);
	sound_s.setVolume(volume);
	sound_s.setLoop(false);
}

void Audio ::play()
{
	sound_s.play();
}

void Audio::pause()
{
	sound_s.pause();
}
void Audio::stop()
{
	sound_s.stop();
}
void Audio::set_loop(bool x)
{
	sound_s.setLoop(x);
}
