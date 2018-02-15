#include "AudioManager.h"
#include "SDL_Manager.h"

AudioManager::AudioManager()
{
}


AudioManager::~AudioManager()
{
}

int AudioManager::SetSfxVolume(int _channel, int _volume)
{
	return Mix_Volume(_channel, _volume);
}

void AudioManager::StopChannel(int _channel)
{
	Mix_HaltChannel(_channel);
}

void AudioManager::StopChannelFadeOut(int _channel, int _ms)
{
	Mix_FadeOutChannel(_channel, _ms);
}

void AudioManager::PauseChannel(int _channel)
{
	Mix_Pause(_channel);
}

void AudioManager::ResumeChannel(int _channel)
{
	Mix_Resume(_channel);
}

int AudioManager::PausedChannel(int _channel)
{
	return Mix_Paused(_channel);
}

int AudioManager::SetMusicVolume(int _volume)
{
	return Mix_VolumeMusic(_volume);
}

void AudioManager::StopMusic()
{
	Mix_HaltMusic();
}

void AudioManager::StopMusicFadeOut(int _ms)
{
	Mix_FadeOutMusic(_ms);
}

void AudioManager::PauseMusic()
{
	Mix_PauseMusic();
}

void AudioManager::ResumeMusic()
{
	Mix_ResumeMusic();
}

int AudioManager::PausedMusic()
{
	return Mix_PausedMusic();
}