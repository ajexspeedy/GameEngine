#pragma once
#include "Audio_Null.h"

namespace dae
{
	class Locator
	{
	public:
		
		static void Initialize();

		static Audio& GetAudio();

		static void Provide(Audio* service);
		static void CleanUp();


	private:
		static Audio* m_Service;
		static Audio_Null m_NullService;
	};

}