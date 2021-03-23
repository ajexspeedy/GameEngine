#pragma once
#include "Audio.h"


namespace dae
{
    class Audio_SDL :
        public Audio
    {
    public:
      
        virtual void PlaySound(int soundID);
        virtual void StopSound(int soundID);
        virtual void StopAllSounds();
    };
}
