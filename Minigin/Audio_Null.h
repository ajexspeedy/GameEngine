#pragma once
#include "Audio.h"
namespace dae
{
    class Audio_Null :
        public Audio
    {
    public:
        virtual void PlaySound(int) { /* Do nothing. */ }
        virtual void StopSound(int) { /* Do nothing. */ }
        virtual void StopAllSounds() { /* Do nothing. */ }
    };

}