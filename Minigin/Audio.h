#pragma once

namespace dae
{
  
    class Audio abstract
    {
    public:
        struct AudioStruct
        {
            int id;
            bool isStopped;
        };
        virtual ~Audio() {}
        virtual void PlaySound(int soundID) = 0;
        virtual void StopSound(int soundID) = 0;
        virtual void StopAllSounds() = 0;
    };

}