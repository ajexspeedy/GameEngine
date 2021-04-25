#pragma once
#include "Audio.h"


namespace dae
{
    class Audio_SDL :
        public Audio
    {
    public:
      
        virtual void PlaySound(const AudioStruct& audio);
        virtual void StopSound(const AudioStruct& audio);
        virtual void StopAllSounds();
    };
}
