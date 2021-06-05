#include "ImposterPCH.h"
#include "QbertGame.h"
#include <vld.h>


#include "SceneManager.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "ResourceManager.h"


#include "Scene.h"
#include "Level.h"
#include "GameObject.h"


#include "RenderComponent.h"
#include "MovementComponent.h"
#include "TileComponent.h"
#include "TransformComponent.h"
#include "PlayerComponent.h"
#include "CoilyComponent.h"
#include "AnimationComponent.h"
#include "PlayerCollisionComponent.h"

#include <SDL_Rect.h>

#include "PlayerLivesDisplay.h"
#include "MoveCommand.h"

#include "Locator.h"
#include "AudioLogger.h"
#include "Audio_SDL.h"
#include "EnableAudioLogging.h"

struct SDL_Rect;

void dae::QbertGame::CleanUp()
{
	if (m_pLevel)
	{
		delete m_pLevel;
		m_pLevel = nullptr;
	}
}
void dae::QbertGame::LoadGame()
{


	auto* menuScene = SceneManager::GetInstance().CreateScene("Menu");

	GameObject* menu = new GameObject{ "Menu" };
	menuScene->Add(menu);

	SetupAudio();
	auto* scene = SceneManager::GetInstance().CreateScene("Qbert");
	int levelRows{ 7 }, levelColumns{ 7 };
	const float StartLevelX{ 110.f }, StartLevelY{ 380.f };
	m_pLevel = CreateLevel(levelRows, levelColumns, StartLevelX, StartLevelY, "../Data/Levels/Level1.xml");
	for (auto tile : m_pLevel->GetTiles())
	{
		scene->Add(tile);
	}
	const int lives{ 3 };
	const float StartPlayerX{ 430.f - StartLevelX }, StartPlayerY{ StartLevelY - 305.f };
	GameObject* player = CreatePlayer(m_pLevel, levelColumns, StartPlayerX, StartPlayerY);
	GameObject* lifeDisplay = CreateLifeDisplay(player, lives);
	GameObject* coily = CreateCoily(player, m_pLevel, levelColumns);
	m_pLevel->AddEntity(player);
	scene->Add(player);
	scene->Add(lifeDisplay);

	//Enemies
	scene->Add(coily);

	player->GetComponent<PlayerCollisionComponent>()->AddEnemy(coily);
}

dae::Level* dae::QbertGame::CreateLevel(const int levelRows, const int levelColumns, const float startLevelX, const float startLevelY, const std::string& filePath) const
{
	Level* level = new Level{ levelRows - 1,levelColumns - 1 , filePath };
	int pyramidWidth = levelRows;
	int pyramidHeight = levelColumns;

	float posX, posY;
	float width{ 64.f }, height{ 64.f };
	float heightOffset = height * 0.75f;
	float halfWidth = width * 0.5f;
	int tileCounter{ 0 };
	for (int i{ 0 }; i < pyramidHeight; i++)
	{
		posX = startLevelX + (halfWidth * i);
		posY = startLevelY - (heightOffset * i);
		for (int j{ 0 }; j < pyramidWidth; j++)
		{

			GameObject* tile = new GameObject{ std::string("Tile ").append(std::to_string(tileCounter)) };
			tile->AddComponent(new TransformComponent{ tile, posX,posY,width,height });
			tile->AddComponent(new RenderComponent{ tile,"Textures/Tile1.png" });
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

dae::GameObject* dae::QbertGame::CreatePlayer(Level* level, const int levelColumns, const float startPlayerX, const float startPlayerY) const
{
	GameObject* player = new GameObject{ "Qbert" };
	float width{ 32.f }, height{ 32.f };
	player->AddComponent(new TransformComponent{ player, startPlayerX,startPlayerY,width,height });



	//player->AddComponent(new RenderComponent{ player,"Textures/Qbert_Spritesheet.png",SDL_Rect{80, 0, 16, 16},32.f,32.f });
	player->AddComponent(new AnimationComponent{ player,4,2,"Textures/Qbert.png",SDL_Rect{0,0,16,16} });
	player->AddComponent(new MovementComponent{ player,level ,0,levelColumns - 1 });
	player->AddComponent(new PlayerCollisionComponent{ player });
	return player;
}

dae::GameObject* dae::QbertGame::CreateLifeDisplay(GameObject* player, const int lives) const
{

	player->AddComponent(new PlayerComponent{ player,lives });
	GameObject* playerLivesDisplay = new GameObject{ "LivesDisplay" };
	playerLivesDisplay->AddComponent(new TransformComponent{ playerLivesDisplay });
	const auto sansFont = ResourceManager::GetInstance().LoadFont("Comic_Sans.otf", 18);
	auto livesDisplay = new PlayerLivesDisplay{ playerLivesDisplay, sansFont,lives,0.f };
	player->GetComponent<PlayerComponent>()->AddObserver(livesDisplay);
	playerLivesDisplay->AddComponent(livesDisplay);

	SetupKeybindings(player->GetComponent<MovementComponent>());

	return playerLivesDisplay;
}

dae::GameObject* dae::QbertGame::CreateCoily(GameObject* player, Level* level, const int levelColumns) const
{
	float StartPosX{ 320.f }, StartPosY{ 85.f }, StartPosFallY{ -50.f }, spawnDuration{ 1.5f };
	float width{ 32.f }, height{ 32.f };
	int numAnim{ 1 }, numFrames{ 2 };

	GameObject* coily = new GameObject{ "Coily" };
	coily->AddComponent(new TransformComponent{ coily,StartPosX,StartPosFallY,width,height });
	coily->AddComponent(new AnimationComponent{ coily,numAnim,numFrames,"Textures/Coily_Egg.png",SDL_Rect{0,0,16,16} });
	coily->AddComponent(new CoilyComponent{ coily,player ,spawnDuration,StartPosX,StartPosY });
	coily->AddComponent(new MovementComponent{ coily,level ,0,levelColumns - 1 ,false });

	return coily;
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

void dae::QbertGame::SetupAudio() const
{
	Audio* audio = new Audio_SDL{};
	Locator::Provide(new AudioLogger{ *audio });
	AudioManager::GetInstance().AddSound("../Data/menu3.wav", 0);
}
