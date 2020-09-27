#include "Audio.h"
// Daniyal

Audio::Audio(AudioType audioType)
{
	this->audioType = audioType;
}

Audio::Audio()
{
}

void Audio::putType(AudioType audioType)
{
	this->audioType = audioType;
}

void Audio::load(const char* filePath)
{
	if (audioType == AudioType::SoundEffect)
	{
		sfxBuffer.loadFromFile(filePath);
		sfx.setBuffer(sfxBuffer);
	}
	else
		music.openFromFile(filePath);
}

void Audio::play()
{
	if (audioType == AudioType::SoundEffect)
		sfx.play();
	else
		music.play();
}

void Audio::pause()
{
	if (audioType == AudioType::SoundEffect)
		sfx.pause();
	else
		music.pause();
}

void Audio::stop()
{
	if (audioType == AudioType::SoundEffect)
		sfx.stop();
	else
		music.stop();
}

void Audio::setVolume(float volume)
{
	if (audioType == AudioType::SoundEffect) 
		sfx.setVolume(volume);
	else 
		music.setVolume(volume);
}

float Audio::getVolume()
{
	if (audioType == AudioType::SoundEffect)
		return sfx.getVolume();
	else
		return music.getVolume();
}

void Audio::setPitch(float pitch)
{
	if (audioType == AudioType::SoundEffect)
		sfx.setPitch(pitch);
	else
		music.setPitch(pitch);
}

float Audio::getPitch()
{
	if (audioType == AudioType::SoundEffect)
		return sfx.getPitch();
	else
		return music.getPitch();
}

void Audio::setLoop(bool loop)
{
	if (audioType == AudioType::SoundEffect)
		return sfx.setLoop(loop);
	else
		return music.setLoop(loop);
}
