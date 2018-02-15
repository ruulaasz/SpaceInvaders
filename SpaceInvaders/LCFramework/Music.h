#pragma once
#include "Audio.h"

class Music : public Audio
{
public:
	Music();
	~Music();

	/**
	* Loads a texture from a file.
	*
	* @param _path
	* String to the file direction.
	*
	*/
	bool loadFromFile(std::string _path);
	void play(int _loops = -1);
	void playFadeIn(int _ms, int _loops = -1);

public:
	Mix_Music* m_music;
};