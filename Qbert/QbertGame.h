#pragma once
#include "Game.h"
#include <string>

namespace dae
{
	class Level;
	class MovementComponent;
	class GameObject;
	class QbertGame final : public Game
	{
	public:
		virtual ~QbertGame() = default;

		virtual void LoadGame() const override;
	private:
		Level* CreateLevel(const int levelRows, const int levelColumns,const float startLevelX, const float startLevelY, const std::string& filePath) const;
		GameObject* CreatePlayer(Level* level, const int levelColumns,const float startPlayerX, const float startPlayerY)const;
		GameObject* CreateLifeDisplay(GameObject* player,const int lives) const;
		
		GameObject* CreateCoily(GameObject* player) const;

		void SetupKeybindings(MovementComponent* pMovementComponent) const;
		void SetupAudio() const;


	};
}

