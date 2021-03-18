#pragma once
#include "Command.h"
#include "PlayerComponent.h"
namespace dae
{
	class KillCommand :
		public Command
	{
	public:
		~KillCommand() = default;
		KillCommand(std::shared_ptr<PlayerComponent> component);

		void Execute() override;
	private:
		std::shared_ptr<PlayerComponent> m_pPlayerComponent;
	};
}
