#include "ImposterPCH.h"
#include "QbertGame.h"
#include "SceneManager.h"
#include "Scene.h"
#include "RenderComponent.h"
#include "GameObject.h"
#include "Level.h"
#include "InputManager.h"
#include "MoveCommand.h"
#include "MovementComponent.h"
#include "TileComponent.h"
#include "GameObject.h"
#include "TransformComponent.h"
using namespace dae;
void QbertGame::LoadGame() const
{





	auto& scene = SceneManager::GetInstance().CreateScene("Qbert");
	int levelRows{ 7 }, levelColumns{ 7 };
	Level* level = CreateLevel(levelRows, levelColumns);
	for (auto tile : level->GetTiles())
	{
		scene.Add(tile);
	}

	GameObject* player = new GameObject{ "Qbert" };
	player->AddComponent(new TransformComponent{ player, 320.f,20.f });
	player->AddComponent(new RenderComponent{ player,"Textures/Qbert_Spritesheet.png",32.f,32.f });
	player->GetComponent<RenderComponent>()->SetSrcRect(80.f, 0.f, 16.f, 16.f);
	player->AddComponent(new MovementComponent{ player, player->GetComponent<RenderComponent>(),level });
	SetupKeybindings(player->GetComponent<MovementComponent>());
	player->GetComponent<MovementComponent>()->SetCurrentTile(0, levelColumns - 1);
	scene.Add(player);



}

Level* QbertGame::CreateLevel(const int levelRows, const int levelColumns) const
{
	Level* level = new Level{ levelRows - 1,levelColumns - 1 };
	int pyramidWidth = levelRows;
	int pyramidHeight = levelColumns;
	float startPosX{ 110.f }, startPosY{ 325.f };
	float posX, posY;
	float width{ 64.f }, height{ 64.f };
	float heightOffset = height * 0.75f;
	float halfWidth = width * 0.5f;
	int tileCounter{ 0 };
	for (int i{ 0 }; i < pyramidHeight; i++)
	{
		posX = startPosX + (halfWidth * i);
		posY = startPosY - (heightOffset * i);
		for (int j{ 0 }; j < pyramidWidth; j++)
		{

			GameObject* tile = new GameObject{ std::string("Tile ").append(std::to_string(tileCounter)) };
			tile->AddComponent(new TransformComponent{ tile, posX,posY });
			tile->AddComponent(new RenderComponent{ tile,"Textures/Tile1.png",width,height });
			//tile->GetComponent<RenderComponent>()->SetSrcRect(srcRect);
			posX += width;
			TileComponent* pTileComponent = new TileComponent{ tile ,j,i };
			tile->AddComponent(pTileComponent);
			level->AddTile(tile);
			tileCounter++;
		}
		pyramidWidth--;
	}


	return level;
}

void dae::QbertGame::SetupKeybindings(MovementComponent* pMovementComponent) const
{
	//Controller
	InputManager::GetInstance().AddButtonCommand(ControllerButton::UpDPad, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::up_right));


	//KeyBoard
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_9, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::up_right));
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_7, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::up_left));
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_3, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::down_right));
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_1, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::down_left));

}
