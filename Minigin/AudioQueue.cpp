#include "MiniginPCH.h"
#include "AudioQueue.h"
#include <cassert>
#include "AudioManager.h"
#include <SDL_mixer.h>

using namespace dae;

int AudioQueue::m_Head = 0;
int AudioQueue::m_Tail = 0;
Audio::AudioStruct AudioQueue::m_Pending[AudioQueue::MAX_PENDING] = {};

void AudioQueue::PlaySound(int soundID)
{
	assert((m_Tail + 1) % MAX_PENDING != m_Head);
	for (int i = m_Head; i != m_Tail; i = (i + 1) % MAX_PENDING)
	{
		if (m_Pending[i].id == soundID)
		{
			// Merge the 2 requests
			
			return;
		}

	}
	m_Pending[m_Tail].id = soundID;
	m_Pending[m_Tail].isStopped = false;
	m_Tail = (m_Tail + 1) % MAX_PENDING;
}

void dae::AudioQueue::StopSound(int soundID)
{
	if (m_Head == m_Tail) return;
	for (int i = m_Head; i != m_Tail; i = (i + 1) % MAX_PENDING)
	{
		if (m_Pending[i].id == soundID)
		{
			m_Pending[i].isStopped = true;

			return;
		}

	}
}

void AudioQueue::Update()
{
	if (m_Head == m_Tail) return;

	if(!m_Pending[m_Head].isStopped)
		Mix_PlayChannel(-1, AudioManager::GetInstance().GetSound(m_Pending[m_Head].id), 0);
	m_Head = (m_Head + 1) % MAX_PENDING;

}
