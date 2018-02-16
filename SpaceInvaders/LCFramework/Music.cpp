#include "Music.h"

namespace LCF
{
	Music::Music()
	{

	}

	Music::~Music()
	{
		Mix_FreeMusic(m_music);
	}

	bool Music::loadFromFile(std::string _path)
	{
		m_music = Mix_LoadMUS(_path.c_str());

		if (m_music == NULL)
		{
			printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
			return false;
		}

		return true;
	}

	void Music::play(int _loops)
	{
		Mix_PlayMusic(m_music, _loops);
	}

	void Music::playFadeIn(int _ms, int _loops)
	{
		Mix_FadeInMusic(m_music, _loops, _ms);
	}
}