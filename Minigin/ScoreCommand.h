#pragma once
#include "Command.h"
namespace dae
{
	class ScoreCommand :
		public Command
	{
	public:
		ScoreCommand(PlayerComponent* component);

		void Execute() override;
	private:
		PlayerComponent* m_pPlayerComponent;
	};

}