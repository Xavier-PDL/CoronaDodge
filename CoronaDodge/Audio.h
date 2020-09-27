#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include "SFML/Audio.hpp"

#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "openal32.lib")
#pragma comment(lib, "flac.lib")
#pragma comment(lib, "vorbisenc.lib")
#pragma comment(lib, "vorbisfile.lib")
#pragma comment(lib, "vorbis.lib")
#pragma comment(lib, "ogg.lib")

#ifdef _DEBUG
#pragma comment(lib, "sfml-system-s-d.lib")
#pragma comment(lib, "sfml-window-s-d.lib")
#pragma comment(lib, "sfml-graphics-s-d.lib")
#pragma comment(lib, "sfml-audio-s-d.lib")
#else
#pragma comment(lib, "sfml-system-s.lib")
#pragma comment(lib, "sfml-window-s.lib")
#pragma comment(lib, "sfml-graphics-s.lib")
#pragma comment(lib, "sfml-audio-s.lib")

#endif

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