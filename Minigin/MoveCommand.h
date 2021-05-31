#pragma once
#include "Command.h"
#include "MovementComponent.h"

namespace dae
{
	class RenderComponent;
	
	class MovementCommand :
		public Command
	{

	public:

		MovementCommand(MovementComponent* pMovementComponent, MovementComponent::MovementDirection direction);
		~MovementCommand() = default;

		void Execute() override;
	private:
		
	
		MovementComponent* m_pMovementComponent;
		MovementComponent::MovementDirection m_Direction;
	};
}
