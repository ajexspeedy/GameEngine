#pragma once
#include "Component.h"

namespace dae
{

	class GameObject;
	class PlayerCollisionComponent : public Component
	{
	public:
		PlayerCollisionComponent(GameObject* pParent);
		~PlayerCollisionComponent();
		virtual void Update() override;
	

		void AddEnemy(GameObject* pEnemy);

		PlayerCollisionComponent(const PlayerCollisionComponent& other) = delete;
		PlayerCollisionComponent(PlayerCollisionComponent&& other) = delete;
		PlayerCollisionComponent& operator=(const PlayerCollisionComponent& other) = delete;
		PlayerCollisionComponent& operator=(PlayerCollisionComponent&& other) = delete;

	private:
		bool IsColliding(GameObject* pEnemy);
		std::vector<GameObject*> m_pEnemies;
	};

}