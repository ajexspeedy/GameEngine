#pragma once
#include "Component.h"
#include "Transform.h"
namespace dae
{
	class RenderComponent;
	class Transform;

	class TileComponent : public Component
	{
	public:
		enum class TileColor
		{
			defaultColor = 0,
			color1 = 1,
			color2 = 2
		};
		TileComponent(GameObject* pParent,const int row,const int column);


		bool IsOnTile(const int row,const int column);

		TileColor GetTileColor() const;


		void SetTileColor(TileColor tileColor);
		void Update() override;

	private:

		TileColor m_TileColor;
		
		int  m_Column, m_Row;
	};
}