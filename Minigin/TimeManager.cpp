#include "ImposterPCH.h"
#include "TimeManager.h"

void dae::TimeManager::CalculateDeltaTime()
{
	m_CurrentTime = std::chrono::high_resolution_clock::now();
	m_DeltaTime = std::chrono::duration<float>(m_CurrentTime - m_LastTime).count();
	m_LastTime = m_CurrentTime;

}

float dae::TimeManager::GetDeltaTime() const
{

	return m_DeltaTime;
}

float dae::TimeManager::GetFPS() const
{
	return 1.f / m_DeltaTime;
}
