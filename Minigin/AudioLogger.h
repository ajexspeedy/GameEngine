#pragma once
#include "Audio.h"
namespace dae
{
    class AudioLogger :
        public Audio
    {
    public:
       
        AudioLogger(Audio& wrapped);
        ~AudioLogger();
        virtual void PlaySound(const AudioStruct& audio) override;
        virtual void StopSound(const AudioStruct& audio) override;
        virtual void StopAllSounds() override;

    private:
        void Log(const char* message);
        Audio& m_Wrapped;
    };

}