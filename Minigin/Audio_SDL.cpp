#include "ImposterPCH.h"
#include "Audio_SDL.h"
#include "SDL.h"
#include "SDL_mixer.h"
#include "AudioManager.h"
#include "AudioQueue.h"

using namespace dae;

void Audio_SDL::PlaySound(const AudioStruct& audio)
{
	
	
	AudioQueue::GetInstance().PlaySound(audio);
}

void dae::Audio_SDL::StopSound(const AudioStruct&)
{
	
}


void dae::Audio_SDL::StopAllSounds()
{
	
}



