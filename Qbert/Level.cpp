#include "ImposterPCH.h"
#include "Level.h"
#include "GameObject.h"

using namespace dae;
Level::~Level()
{
	for (auto tile : m_pTiles)
	{
		if (tile)
		{
			delete tile;
			tile = nullptr;
		}
	}
	m_pTiles.clear();
}

void Level::AddTile(GameObject* pTile)
{
	m_pTiles.push_back(pTile);
}

const std::vector<GameObject*>& dae::Level::GetTiles() const
{
	return m_pTiles;
}
