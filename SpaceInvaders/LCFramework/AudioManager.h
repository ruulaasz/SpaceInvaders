#pragma once
class AudioManager
{
public:
	AudioManager();
	virtual ~AudioManager();

	int SetSfxVolume(int _channel, int _volume);
	void StopChannel(int _channel);
	void StopChannelFadeOut(int _channel, int _ms);
	void PauseChannel(int _channel);
	void ResumeChannel(int _channel);
	int PausedChannel(int _channel);

	int SetMusicVolume(int _volume);
	void StopMusic();
	void StopMusicFadeOut( int _ms);
	void PauseMusic();
	void ResumeMusic();
	int PausedMusic();
};

