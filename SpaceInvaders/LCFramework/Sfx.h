#pragma once
#include "Audio.h"

namespace LCF
{
	/**
	* A container class for a Sfx
	*/
	class Sfx : public Audio
	{
	public:
		Sfx();
		~Sfx();

		/**
		* Loads a sfx from a file.
		*
		* @param _path
		* String to the file direction.
		*
		*/
		bool loadFromFile(std::string _path);

		/**
		* Reproduce the sfx file
		*
		* @param _channel
		* the channel number.
		*
		* @param _loops
		* the number of loops, 0 by default.
		*
		*/
		void play(int _channel, int _loops = 0);

		/**
		* Reproduce the sfx file with a fade in effect
		*
		* @param _channel
		* the channel number.
		*
		* @param _ms
		* the time to reach max volume.
		*
		* @param _loops
		* the number of loops, 0 by default.
		*
		*/
		void playFadeIn(int _channel, int _ms, int _loops = 0);

	public:
		Mix_Chunk* m_sfx;
	};
}