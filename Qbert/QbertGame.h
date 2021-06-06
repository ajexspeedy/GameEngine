#pragma once
#include "Game.h"
#include <string>

namespace dae
{
	class Level;
	class MovementComponent;
	class MenuSelectorComponent;
	class GameObject;
	class QbertGame final : public Game
	{
	public:

		virtual ~QbertGame() = default;

		virtual void LoadGame() override;
		virtual void CleanUp() override;
	private:
		Level* CreateLevel(const int levelRows, const int levelColumns, const float startLevelX, const float startLevelY, const std::string& filePath) const;
		
		GameObject* CreateMenu() const;
		GameObject* CreateMenuSelector() const;
		GameObject* CreateEndScreen() const;

		GameObject* CreatePlayer()const;
		GameObject* CreateLifeDisplay(GameObject* player, const int lives) const;
		GameObject* CreateScoreDisplay(GameObject* player) const;

		GameObject* CreateCoily(GameObject* player) const;
		GameObject* CreateWrongway() const;
		GameObject* CreateUgg() const;
		GameObject* CreateSlick() const;
		GameObject* CreateSam() const;

		void SetupKeybindings(MovementComponent* pMovementComponent, MenuSelectorComponent* pMenuSelector) const;
		void SetupAudio() const;

		Level* m_pLevel;

	};
}

