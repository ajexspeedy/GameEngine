#include "MiniginPCH.h"
#include "ScoreCommand.h"

#include "PlayerComponent.h"



dae::ScoreCommand::ScoreCommand(std::shared_ptr<PlayerComponent> component):
m_pPlayerComponent(component)
{
}

void dae::ScoreCommand::Execute()
{
	m_pPlayerComponent->ChangeScore(25);
}
