#pragma once
#include "Command.h"
namespace dae
{
	class ScoreCommand :
		public Command
	{
	public:
		~ScoreCommand() = default;
		ScoreCommand(std::shared_ptr<PlayerComponent> component);

		void Execute() override;
	private:
		std::shared_ptr<PlayerComponent> m_pPlayerComponent;
	};

}