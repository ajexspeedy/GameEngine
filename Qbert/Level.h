#pragma once

namespace dae
{
	class GameObject;
	class Level
	{
	public:
		Level() = default;
		~Level();

		void AddTile(GameObject* pTile);
		const std::vector<GameObject*>& GetTiles() const;

	private:
		std::vector<GameObject*> m_pTiles;
	};

}