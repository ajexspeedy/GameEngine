#pragma once
#include "Singleton.h"
#include "Audio.h"

namespace dae
{
	
	class AudioQueue: public Singleton<AudioQueue>
	{
	public:

		
		// TODO: Fix channels 
		static void PlaySound(const Audio::AudioStruct& audio);
		

		static void Update();
		
	private:
		static const int MAX_PENDING = 16;

		static Audio::AudioStruct m_Pending[MAX_PENDING];
		static int m_Head;
		static int m_Tail;


	};

}