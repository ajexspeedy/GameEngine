#include "ImposterPCH.h"
#include "EnableAudioLogging.h"
#include "Locator.h"
#include "AudioLogger.h"


using namespace dae;



void EnableAudioLogging::Execute()
{
	m_bIsEnabled.store(!m_bIsEnabled.load());
	if (m_bIsEnabled.load())
	{
	
		Locator::Provide(new AudioLogger(Locator::GetAudio()));
		std::cout << "Logging enabled\n";
	}
	else
	{
	
		std::cout << "Logging disabled\n";
	}
}
