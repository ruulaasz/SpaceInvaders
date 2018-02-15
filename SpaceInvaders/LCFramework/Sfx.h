#pragma once
#include "Audio.h"

class Sfx : public Audio
{
public:
	Sfx();
	~Sfx();

	/**
	* Loads a texture from a file.
	*
	* @param _path
	* String to the file direction.
	*
	*/
	bool loadFromFile(std::string _path);
	void play(int _channel, int _loops = 0);
	void playFadeIn(int _channel, int _ms, int _loops = 0);

public:
	Mix_Chunk* m_sfx;
};