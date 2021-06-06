#pragma once
#include "Component.h"
#include "TransformComponent.h"

namespace dae
{

	class GameObject;
	class Level;
	class MenuSelectorComponent : public Component
	{
	public:
		MenuSelectorComponent(GameObject* pParent, Level* pLevel);
		~MenuSelectorComponent() = default;
		virtual void Update() override;

		void AddButtonLocation(const glm::vec2& button);
		glm::vec2 NextButton();
		glm::vec2 PreviousButton();

		glm::vec2 GetCurrentButtonLocation() const;
		int GetCurrentSelection() const;

		void StartGame();
		void LoseGame();
		void ResetGame();

		MenuSelectorComponent(const MenuSelectorComponent& other) = delete;
		MenuSelectorComponent(MenuSelectorComponent&& other) = delete;
		MenuSelectorComponent& operator=(const MenuSelectorComponent& other) = delete;
		MenuSelectorComponent& operator=(MenuSelectorComponent&& other) = delete;

	private:
		std::vector<glm::vec2> m_ButtonLocations;
		int m_CurrentButton;

		Level* m_pLevel;
	};

}