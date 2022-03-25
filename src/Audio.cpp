#include "includes/Audio.h"

Audio ::Audio(std::string sound_path, float volume)
{
	sound_b.loadFromFile(sound_path);
	sound_s.setBuffer(sound_b);
	sound_s.setVolume(volume);
	sound_s.setLoop(true);
}

void Audio ::play()
{
	sound_s.play();
}

void Audio::pause()
{
	sound_s.pause();
}
