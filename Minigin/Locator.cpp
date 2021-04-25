#include "MiniginPCH.h"
#include "Locator.h"
#include "AudioLogger.h"

using namespace dae;

Audio* Locator::m_Service;

Audio_Null Locator::m_NullService;



Audio& Locator::GetAudio()
{

	if (m_Service == nullptr)
		return m_NullService;
	return *m_Service;
}

void Locator::Provide(Audio* service)
{

	m_Service = service;


}

void dae::Locator::CleanUp()
{

	delete m_Service;

}

