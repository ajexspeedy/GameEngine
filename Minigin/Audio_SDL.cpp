#include "MiniginPCH.h"
#include "Audio_SDL.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "AudioManager.h"
#include "AudioQueue.h"

using namespace dae;

void Audio_SDL::PlaySound(int soundID )
{
	
	
	AudioQueue::GetInstance().PlaySound(soundID);
}

void Audio_SDL::StopSound(int soundID)
{
	std::cout << "Stopping soundID " << soundID << std::endl;
}

void Audio_SDL::StopAllSounds()
{
	std::cout << "Stopping all sounds\n ";
}
