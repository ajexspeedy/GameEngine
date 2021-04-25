#include "MiniginPCH.h"
#include "AudioQueue.h"
#include <cassert>
#include "AudioManager.h"
#include <SDL_mixer.h>
#include <algorithm>

using namespace dae;

int AudioQueue::m_Head = 0;
int AudioQueue::m_Tail = 0;
Audio::AudioStruct AudioQueue::m_Pending[AudioQueue::MAX_PENDING] = {};

void AudioQueue::PlaySound(const Audio::AudioStruct& audio)
{
	assert((m_Tail + 1) % MAX_PENDING != m_Head);
	for (int i = m_Head; i != m_Tail; i = (i + 1) % MAX_PENDING)
	{
		if (m_Pending[i].id == audio.id)
		{
			// Merge the 2 requests
			m_Pending[i].volume = max(m_Pending[i].volume, audio.volume);
			return;
		}

	}
	m_Pending[m_Tail].id = audio.id;
	m_Pending[m_Tail].volume = audio.volume;
	m_Pending[m_Tail].channel = audio.channel;

	m_Tail = (m_Tail + 1) % MAX_PENDING;
}



void AudioQueue::Update()
{
	if (m_Head == m_Tail) return;

	Mix_PlayChannel(m_Pending[m_Head].channel.channelIndex, AudioManager::GetInstance().GetSound(m_Pending[m_Head].id), 0);
	Mix_VolumeChunk(AudioManager::GetInstance().GetSound(m_Pending[m_Head].id), int((float)MIX_MAX_VOLUME * m_Pending[m_Head].volume));
	m_Head = (m_Head + 1) % MAX_PENDING;

}
