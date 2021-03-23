#include "MiniginPCH.h"
#include "AudioLogger.h"

dae::AudioLogger::AudioLogger(Audio& wrapped):
	m_Wrapped(wrapped)
{
}

void dae::AudioLogger::PlaySound(int soundID)
{
	std::string message = "Played sound: " + std::to_string(soundID) + "\n";
	Log(message.c_str());
	m_Wrapped.PlaySound(soundID);
}

void dae::AudioLogger::StopSound(int soundID)
{
	std::string message = "Stopped sound: " + std::to_string(soundID) + "\n";
	Log(message.c_str());
	m_Wrapped.StopSound(soundID);
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
