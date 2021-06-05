#include "ImposterPCH.h"
#include "KillCommand.h"
#include "Locator.h"
#include "Audio_SDL.h"

dae::KillCommand::KillCommand(std::shared_ptr<PlayerComponent> component) :
	m_pPlayerComponent(component)
{


}

void dae::KillCommand::Execute()
{
	m_pPlayerComponent->KillPlayer();
	
	Audio* audio = &Locator::GetAudio();
	audio->PlaySound(Audio::AudioStruct{ 1,0.2f,{} });
}
