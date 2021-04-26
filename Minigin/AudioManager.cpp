#include "ImposterPCH.h"
#include "AudioManager.h"

dae::AudioManager::~AudioManager()
{
	
}

void dae::AudioManager::AddSound(const std::string& filePath, int soundID)
{
	Mix_Chunk* sound = Mix_LoadWAV(filePath.c_str());
	if (sound == nullptr)
	{
		std::cout << SDL_GetError();
		throw std::runtime_error(std::string("Error adding sound: ") + SDL_GetError());
	}
	
	m_pSoundList[soundID] = sound;

}

void dae::AudioManager::AddMusic(const std::string&)
{
}

Mix_Chunk* dae::AudioManager::GetSound(int soundID)
{
	
	return m_pSoundList[soundID];
}

void dae::AudioManager::CleanUp()
{
	for (auto pair : m_pSoundList)
	{
		Mix_FreeChunk(pair.second);
	}
}
