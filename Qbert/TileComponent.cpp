#include "ImposterPCH.h"
#include "TileComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::TileComponent::TileComponent(GameObject* pParent, const int row, const int column) :
	Component{ pParent },
	m_TileColor{ TileColor::defaultColor },
	m_Row{ row },
	m_Column{ column }

{


}


bool dae::TileComponent::IsOnTile(const int row, const int column)
{
	//if (row < 0 || row > m_MaxRows || column < 0)
	//{
	//	isFalling;
	//	//return false;
	//	std::cout << "Fall off the map: " << m_MaxRows << " - " << m_MaxColumns << std::endl;
	//}
	return row == m_Row && column == m_Column;
}

dae::TileComponent::TileColor dae::TileComponent::GetTileColor() const
{
	return m_TileColor;
}

void dae::TileComponent::SetTileColor(TileColor tileColor)
{
	m_TileColor = tileColor;
	switch (m_TileColor)
	{
	case TileColor::color1:
		GetParent()->GetComponent<RenderComponent>()->SetTexture("Textures/Tile2.png");
		break;
	case TileColor::color2:
		GetParent()->GetComponent<RenderComponent>()->SetTexture("Textures/Tile3.png");
		break;
	case TileColor::defaultColor:
		GetParent()->GetComponent<RenderComponent>()->SetTexture("Textures/Tile1.png");
		break;
	}
}

void dae::TileComponent::Update()
{
}
