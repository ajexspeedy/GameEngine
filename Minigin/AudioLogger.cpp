#include "ImposterPCH.h"
#include "AudioLogger.h"



dae::AudioLogger::AudioLogger(Audio& wrapped):
	m_Wrapped(wrapped)
{
}

dae::AudioLogger::~AudioLogger()
{
	if (&m_Wrapped)
	{
		delete &m_Wrapped;
	}
}

void dae::AudioLogger::PlaySound(const AudioStruct& audio)
{
	std::string message = "Played sound: " + std::to_string(audio.id) + "\n";
	Log(message.c_str());
	m_Wrapped.PlaySound(audio);
}

void dae::AudioLogger::StopSound(const AudioStruct& audio)
{
	std::string message = "Stopped sound: " + std::to_string(audio.id) + "\n";
	Log(message.c_str());
	m_Wrapped.StopSound(audio);
}

void dae::AudioLogger::StopAllSounds()
{
	std::string message = "Stopped all sounds\n";
	Log(message.c_str());
	m_Wrapped.StopAllSounds();
}

void dae::AudioLogger::Log(const char* message)
{
	std::cout << message;
}
