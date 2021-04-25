#pragma once


namespace dae
{
  
    class Audio abstract
    {
    public:
        struct Channel
        {
            bool isInUse{ false };
            uint16_t channelIndex;

        };
        struct AudioStruct
        {
            int id;
            float volume;
            Channel channel;
        };
        virtual ~Audio() {}
        virtual void PlaySound(const AudioStruct& audio) = 0;
        virtual void StopSound(const AudioStruct& audio) = 0;
        virtual void StopAllSounds() = 0;
    };

}