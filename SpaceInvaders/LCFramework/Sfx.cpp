#include "Sfx.h"

namespace LCF
{
	Sfx::Sfx()
	{

	}

	Sfx::~Sfx()
	{
		Mix_FreeChunk(m_sfx);
	}

	bool Sfx::loadFromFile(std::string _path)
	{
		m_sfx = Mix_LoadWAV(_path.c_str());

		if (m_sfx == NULL)
		{
			printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}

		return true;
	}

	void Sfx::play(int _channel, int _loops)
	{
		m_currentChannel = Mix_PlayChannel(_channel, m_sfx, _loops);
	}

	void Sfx::playFadeIn(int _channel, int _ms, int _loops)
	{
		m_currentChannel = Mix_FadeInChannel(_channel, m_sfx, _loops, _ms);
	}
}