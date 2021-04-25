#pragma once
#include "Command.h"

namespace dae
{
	class EnableAudioLogging :public Command
	{
	public:

		virtual void Execute() override;
	private:
		std::atomic<bool> m_bIsEnabled{ false };
		
	};

}