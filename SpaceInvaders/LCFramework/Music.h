#pragma once
#include "Audio.h"

namespace LCF
{
	/**
	* A container class for a Music 
	*/
	class Music : public LCF::Audio
	{
	public:
		Music();
		~Music();

		/**
		* Loads a music from a file.
		*
		* @param _path
		* String to the file direction.
		*
		*/
		bool loadFromFile(std::string _path);

		/**
		* Reproduce the sfx file
		*
		* @param _loops
		* the number of loops, -1 by default(infinite*)
		*
		*/
		void play(int _loops = -1);

		/**
		* Reproduce the sfx file with a fade in effect
		*
		* @param _ms
		* the time to reach max volume.
		*
		* @param _loops
		* the number of loops, -1 by default(infinite*)
		*
		*/
		void playFadeIn(int _ms, int _loops = -1);

	public:
		Mix_Music* m_music;
	};
}