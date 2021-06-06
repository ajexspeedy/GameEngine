#pragma once
#include "Command.h"
#include "TransformComponent.h"

namespace dae
{
	class RenderComponent;
	class MenuSelectorComponent;
	class MenuSelectCommand :
		public Command
	{

	public:
		enum class MenuMovement
		{
			up,
			down,
			select
		};

		MenuSelectCommand(MenuSelectorComponent* transform,MenuMovement movement);
		~MenuSelectCommand() = default;

		void Execute() override;
	private:

		MenuSelectorComponent* m_MenuSelector;

		MenuMovement m_Movement;

	};
}
