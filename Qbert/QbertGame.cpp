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
using namespace dae;
void QbertGame::LoadGame() const
{





	auto& scene = SceneManager::GetInstance().CreateScene("Qbert");

	Level* level = CreateLevel();
	for (auto tile : level->GetTiles())
	{
		scene.Add(tile);
	}

	auto player = new GameObject{ new RenderComponent{"Qbert_Spritesheet.png",32.f,32.f,320.f,20.f},"Qbert" };
	player->GetComponent<RenderComponent>()->SetSrcRect(80.f, 0.f, 16.f, 16.f);
	player->AddComponent(new MovementComponent{ player->GetComponent<RenderComponent>()->GetTransform() });
	SetupKeybindings(player->GetComponent<MovementComponent>());
	//InputManager::GetInstance().AddButtonCommand(ControllerButton::UpDPad, new MovementCommand(player->GetComponent<RenderComponent>(), MovementCommand::MovementDirection::up_right));
	//InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_9, new MovementCommand(player->GetComponent<RenderComponent>(), MovementCommand::MovementDirection::up_right));

	scene.Add(player);


	
}

Level* QbertGame::CreateLevel() const
{
	Level* level = new Level{};
	int pyramidWidth = 7;
	int pyramidHeight = 7;
	float startPosX{ 105.f }, startPosY{ 325.f };
	float posX, posY;
	float width{ 64.f }, height{ 64.f};
	float heightOffset = height * 0.75f;
	float halfWidth = width * 0.5f;
	int tileCounter{ 0 };
	SDL_Rect srcRect{ 0,160,32,32 };
	for (int i{ 0 }; i < pyramidHeight; i++)
	{
		posX = startPosX + (halfWidth * i);
		posY = startPosY - (heightOffset * i);
		for (int j{ 0 }; j < pyramidWidth; j++)
		{
			auto tile = new GameObject{ new RenderComponent{"Qbert_Spritesheet.png",width,height,posX,posY} ,std::string("Tile ").append(std::to_string(tileCounter)) };
			tile->GetComponent<RenderComponent>()->SetSrcRect(srcRect);
			posX += width;
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
