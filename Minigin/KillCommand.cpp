#include "MiniginPCH.h"
#include "KillCommand.h"
#include "Locator.h"
#include "Audio_SDL.h"

dae::KillCommand::KillCommand(std::shared_ptr<PlayerComponent> component) :
	m_pPlayerComponent(component)
{


}

void dae::KillCommand::Execute()
{
	m_pPlayerComponent->ChangeHealth(-1);
	
	Audio* audio = &Locator::GetAudio();
	audio->PlaySound(1);
}
