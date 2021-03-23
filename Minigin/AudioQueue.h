#pragma once
#include "Singleton.h"
#include "Audio.h"

namespace dae
{
	
	class AudioQueue: public Singleton<AudioQueue>
	{
	public:

		

		static void PlaySound(int soundID);
		static void StopSound(int soundID);

		static void Update();
		
	private:
		static const int MAX_PENDING = 16;

		static Audio::AudioStruct m_Pending[MAX_PENDING];
		static int m_Head;
		static int m_Tail;


	};

}