#pragma once

#include <SDL_mixer.h>

class AudioManager
{
public:
	~AudioManager();
	static void Initialize();
	static void PlayJump();
	static void PlayStomp();

private:
	AudioManager();
	static AudioManager& GetInstance();
	void LoadAndPlayMusic();
	void LoadSFX();

private:
	Mix_Chunk* mJump;
	Mix_Chunk* mStomp;
	Mix_Music* mMusic;
};

