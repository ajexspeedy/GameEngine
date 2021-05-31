#include "ImposterPCH.h"
#include "MoveCommand.h"



dae::MovementCommand::MovementCommand(MovementComponent* pMovementComponent, MovementComponent::MovementDirection direction):
	m_pMovementComponent{pMovementComponent},
	m_Direction{direction}
{
}

void dae::MovementCommand::Execute()
{
	m_pMovementComponent->Jump(m_Direction);
	//float xTranslate{ 32.f }, yTranslate{48.f};
	//switch (m_Direction)
	//{
	//case MovementComponent::MovementDirection::up_right:
	//	//Move(xTranslate, -yTranslate);
	//	std::cout << "Up" << std::endl;
	//	break;
	//case MovementComponent::MovementDirection::up_left:
	//	//Move(-xTranslate, -yTranslate);
	//	break;
	//case MovementComponent::MovementDirection::down_right:
	//	//Move(xTranslate, yTranslate);
	//	break;
	//case MovementComponent::MovementDirection::down_left:
	//	//Move(-xTranslate, yTranslate);
	//	break;
	//}
}
