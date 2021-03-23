#include "MiniginPCH.h"
#include "Locator.h"

using namespace dae;

Audio* Locator::m_Service;
Audio_Null Locator::m_NullService;


void Locator::Initialize()
{
	m_Service = (Audio*)&m_NullService;
}

Audio& Locator::GetAudio()
{
	return *m_Service;
}

void Locator::Provide(Audio* service)
{
    if (service == nullptr)
    {
        // Revert to null service.
        m_Service = (Audio*)&m_NullService; // Reference tells user this will always be a valid object
    }
    else
    {
        m_Service = service;
    }
}

void dae::Locator::CleanUp()
{
    delete m_Service;
}
