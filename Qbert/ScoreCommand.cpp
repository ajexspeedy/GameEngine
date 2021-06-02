#include "ImposterPCH.h"
#include "ScoreCommand.h"

#include "PlayerComponent.h"
#include "Locator.h"
#include "Audio_SDL.h"


dae::ScoreCommand::ScoreCommand(std::shared_ptr<PlayerComponent> component):
m_pPlayerComponent(component)
{
}

void dae::ScoreCommand::Execute()
{
	m_pPlayerComponent->ChangeScore(25);

	Audio* audio = &Locator::GetAudio();
	audio->PlaySound(Audio::AudioStruct{ 1,0.f,{} });
}
