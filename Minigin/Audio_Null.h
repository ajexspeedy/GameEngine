#pragma once
#include "Audio.h"
namespace dae
{
    class Audio_Null :
        public Audio
    {
    public:
        virtual void PlaySound(const AudioStruct&) { /* Do nothing. */ }
        virtual void StopSound(const AudioStruct&) { /* Do nothing. */ }
        virtual void StopAllSounds() { /* Do nothing. */ }
    };

}