#pragma once
#include "Singleton.h"
#include "SDL_mixer.h"
#include <map>

namespace dae
{
	class AudioManager final : public Singleton<AudioManager>
	{
	public:
		~AudioManager();
		void AddSound(const std::string& filePath, int soundID);
		void AddMusic(const std::string& filePath);

		Mix_Chunk* GetSound(int soundID);

		void CleanUp();

	private:
		std::map<int, Mix_Chunk*> m_pSoundList;
		//std::vector<Mix_Music*> m_pMusicList;
	};

}