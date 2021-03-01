#pragma once
#include "Command.h"
#include "PlayerComponent.h"
namespace dae
{
	class KillCommand :
		public Command
	{
	public:

		KillCommand(PlayerComponent* component);

		void Execute() override;
	private:
		PlayerComponent* m_pPlayerComponent;
	};
}
