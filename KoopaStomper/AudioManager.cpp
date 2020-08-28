#include "AudioManager.h"

AudioManager::~AudioManager()
{
	Mix_FreeChunk(mJump);
	Mix_FreeMusic(mMusic);
}

void AudioManager::Initialize()
{
	GetInstance();
}

void AudioManager::PlayJump()
{
	Mix_PlayChannel(-1, GetInstance().mJump, 0);
}

void AudioManager::PlayStomp()
{
	Mix_PlayChannel(-1, GetInstance().mStomp, 0);
}

AudioManager::AudioManager()
{
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
	

	LoadAndPlayMusic();

	LoadSFX();	
}

AudioManager& AudioManager::GetInstance()
{
	static AudioManager audio;
	return audio;
}

void AudioManager::LoadAndPlayMusic()
{
	mMusic = Mix_LoadMUS("Resources/Sounds/music.wav");
	Mix_PlayMusic(mMusic, -1);
	Mix_VolumeMusic(8);
}

void AudioManager::LoadSFX()
{
	mJump = Mix_LoadWAV("Resources/Sounds/jump.wav");
	mStomp = Mix_LoadWAV("Resources/Sounds/stomp.wav");

	Mix_VolumeChunk(mJump, 32);
	Mix_VolumeChunk(mStomp, 32);
}
