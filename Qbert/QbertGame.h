#pragma once
#include "Game.h"

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
		dae::Level* CreateLevel(const int levelRows,const int levelColumns) const;
		void SetupKeybindings(MovementComponent* pMovementComponent) const;
	};
}

