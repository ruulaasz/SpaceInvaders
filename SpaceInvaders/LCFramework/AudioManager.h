#pragma once

#include "Module.h"

namespace LCF
{
	/**
	* Manager class for inputs
	*/
	class AudioManager : public LCF::Module<AudioManager>
	{
	public:
		AudioManager();
		virtual ~AudioManager();

		/**
		* Set the sfx volume
		*
		* @param _channel
		* the channel number, -1 for all channels
		*
		* @param _volume
		* the new volume 0-128
		*
		* @return int
		* if the recieved volume its -1 return the current volume
		*
		*/
		int SetSfxVolume(int _channel, int _volume);

		/**
		* Stop the reproduction on a channel
		*
		* @param _channel
		* the channel number, -1 for all channels
		*
		*/
		void StopChannel(int _channel);

		/**
		* Stop the reproduction on a channel with a fade out
		*
		* @param _channel
		* the channel number, -1 for all channels
		*
		* @param _ms
		* the duration of the fade out
		*
		*/
		void StopChannelFadeOut(int _channel, int _ms);

		/**
		* Pause the reproduction on a channel
		*
		* @param _channel
		* the channel number, -1 for all channels
		*
		*/
		void PauseChannel(int _channel);

		/**
		* Resume the reproduction on a channel
		*
		* @param _channel
		* the channel number, -1 for all channels
		*
		*/
		void ResumeChannel(int _channel);

		/**
		* Get the pause status of a channel
		*
		* @param _channel
		* the channel number, -1 for all channels
		*
		* @return int
		* 0 if is not paused, 1 if is paused
		*
		*/
		int PausedChannel(int _channel);

		/**
		* Get if the channel is playing
		*
		* @param _channel
		* the channel number, -1 for all channels
		*
		* @return int
		* 0 if the channel is not playing
		*
		*/
		int PlayingChannel(int _channel);

		/**
		* Set the music volume
		*
		* @param _volume
		* the new volume 0-128
		*
		* @return int
		* if the recieved volume its -1 return the current volume
		*
		*/
		int SetMusicVolume(int _volume);

		/**
		* Stop the reproduction on the music
		*
		*/
		void StopMusic();

		/**
		* Stop the reproduction on music with a fade out
		*
		* @param _ms
		* the duration of the fade out
		*
		*/
		void StopMusicFadeOut(int _ms);

		/**
		* Pause the reproduction on the music
		*
		*/
		void PauseMusic();

		/**
		* Resume the reproduction on the music
		*
		*/
		void ResumeMusic();

		/**
		* Get the pause status of the music
		*
		* @return int
		* 0 if is not paused, 1 if is paused
		*
		*/
		int PausedMusic();
	};
}