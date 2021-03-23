#pragma once
#include "Audio.h"
namespace dae
{
    class AudioLogger :
        public Audio
    {
    public:
        AudioLogger(Audio& wrapped);

        virtual void PlaySound(int soundID) override;
        virtual void StopSound(int soundID) override;
        virtual void StopAllSounds() override;

    private:
        void Log(const char* message);
        Audio& m_Wrapped;
    };

}