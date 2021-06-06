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

		GameObject* CreatePlayer(int playerIndex = 0)const;
		GameObject* CreateLifeDisplay(GameObject* player, const int lives, int playerIndex = 0) const;
		GameObject* CreateScoreDisplay(GameObject* player, int playerIndex = 0) const;

		GameObject* CreateCoily(GameObject* player) const;
		GameObject* CreateWrongway() const;
		GameObject* CreateUgg() const;
		GameObject* CreateSlick() const;
		GameObject* CreateSam() const;

		void SetupKeybindings(MovementComponent* pMovementComponent, MovementComponent* pMovementComponent2, MenuSelectorComponent* pMenuSelector) const;
		void SetupAudio() const;

		Level* m_pLevel;

	};
}

