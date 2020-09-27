
/// Written by Daniyal Kabir

#pragma once
#include "SFMLBase.h"

enum AudioType
{
	SoundEffect,
	BackgroundMusic
};

class Audio
{
	AudioType audioType;
	sf::Music music;
	sf::SoundBuffer sfxBuffer;
	sf::Sound sfx;

public:
	Audio(AudioType audioType);
	Audio();
	void putType(AudioType audioType);
	void load(const char* filePath);
	void play();
	void pause();
	void stop();
	void setVolume(float volume);
	float getVolume();
	void setPitch(float pitch);
	float getPitch();
	void setLoop(bool loop);
};