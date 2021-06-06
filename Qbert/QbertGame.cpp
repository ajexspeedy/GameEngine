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
#include "UggWrongwayComponent.h"
#include "SlickSamComponent.h"
#include "MenuSelectorComponent.h"

#include <SDL_Rect.h>

#include "PlayerLivesDisplay.h"
#include "PlayerScoreDisplay.h"
#include "MoveCommand.h"
#include "MenuSelectCommand.h"

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
	srand(unsigned int(time(NULL)));

	auto* scene = SceneManager::GetInstance().CreateScene("Game");
	int levelRows{ 7 }, levelColumns{ 7 };
	const float StartLevelX{ 110.f }, StartLevelY{ 380.f };
	m_pLevel = CreateLevel(levelRows, levelColumns, StartLevelX, StartLevelY, "../Data/Levels/Level1.xml");
	for (auto tile : m_pLevel->GetTiles())
	{
		scene->Add(tile);
	}


	auto* menuScene = SceneManager::GetInstance().CreateScene("Menu");

	GameObject* menuSelector = CreateMenuSelector();
	GameObject* menu = CreateMenu();

	menuScene->Add(menuSelector);
	menuScene->Add(menu);

	auto* endScene = SceneManager::GetInstance().CreateScene("Fail");

	GameObject* newMenuSelector = CreateMenuSelector();
	GameObject* endScreen = CreateEndScreen();
	endScene->Add(newMenuSelector);
	endScene->Add(endScreen);
	SetupAudio();

	const int lives{ 3 };

	GameObject* player = CreatePlayer();
	player->AddComponent(new PlayerComponent{ player,lives });
	GameObject* lifeDisplay = CreateLifeDisplay(player, lives);
	GameObject* scoreDisplay = CreateScoreDisplay(player);
	m_pLevel->SetPlayer1(player);

	GameObject* player2 = CreatePlayer(1);
	player2->AddComponent(new PlayerComponent{ player2,lives });
	m_pLevel->SetPlayer2(player2);
	//GameObject* lifeDisplay2 = CreateLifeDisplay(player2, lives);
	//GameObject* scoreDisplay2 = CreateScoreDisplay(player2);

	GameObject* coily = CreateCoily(player);
	GameObject* wrongway = CreateWrongway();
	GameObject* ugg = CreateUgg();
	GameObject* slick = CreateSlick();
	GameObject* sam = CreateSam();

	m_pLevel->AddEntity(player);
	m_pLevel->AddEntity(player2);
	m_pLevel->AddEntity(coily);
	m_pLevel->AddEntity(wrongway);
	m_pLevel->AddEntity(ugg);
	m_pLevel->AddEntity(slick);
	m_pLevel->AddEntity(sam);
	scene->Add(player);
	scene->Add(lifeDisplay);
	scene->Add(scoreDisplay);
	scene->Add(player2);
	//scene->Add(lifeDisplay2);
	//scene->Add(scoreDisplay2);


	//Enemies
	scene->Add(coily);
	scene->Add(wrongway);
	scene->Add(ugg);
	scene->Add(slick);
	scene->Add(sam);

	auto playerCollision = player->GetComponent<PlayerCollisionComponent>();
	playerCollision->AddEnemy(coily);
	playerCollision->AddEnemy(wrongway);
	playerCollision->AddEnemy(ugg);
	playerCollision->AddEnemy(slick);
	playerCollision->AddEnemy(sam);
	playerCollision->AddEnemy(player2);

	// Menu
	SceneManager::GetInstance().SetCurrentScene(menuScene->GetSceneNumber());

	SetupKeybindings(player->GetComponent<MovementComponent>(),player2->GetComponent<MovementComponent>(), menuSelector->GetComponent<MenuSelectorComponent>());
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

			GameObject* tile = new GameObject{ std::string("Tile ").append(std::to_string(tileCounter)),-1 };
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

dae::GameObject* dae::QbertGame::CreateMenu() const
{
	GameObject* menu = new GameObject{ "Menu",-1 };
	menu->AddComponent(new TransformComponent{ menu,0.f,0.f,640.f,480.f });
	menu->AddComponent(new RenderComponent{ menu,"Textures/Menu.png" });

	return menu;
}

dae::GameObject* dae::QbertGame::CreateMenuSelector() const
{
	GameObject* menuSelector = new GameObject{ "MenuSelector",-1 };
	menuSelector->AddComponent(new TransformComponent{ menuSelector,110.f,55.f,410.f,70.f });
	menuSelector->AddComponent(new RenderComponent{ menuSelector,"Textures/Selector.png" });
	MenuSelectorComponent* menuSelectorcomponent = new MenuSelectorComponent{ menuSelector,m_pLevel };
	menuSelectorcomponent->AddButtonLocation(glm::vec2{ 110.f,55.f });
	menuSelectorcomponent->AddButtonLocation(glm::vec2{ 110.f,200.f });
	menuSelectorcomponent->AddButtonLocation(glm::vec2{ 110.f,355.f });
	menuSelector->AddComponent(menuSelectorcomponent);
	return menuSelector;
}

dae::GameObject* dae::QbertGame::CreateEndScreen() const
{
	GameObject* end = new GameObject{ "Fail",-1 };
	end->AddComponent(new TransformComponent{ end,0.f,0.f,640.f,480.f });
	end->AddComponent(new RenderComponent{ end,"Textures/Fail.png" });

	return end;
}

dae::GameObject* dae::QbertGame::CreatePlayer(int playerIndex) const
{
	if (playerIndex == 0)
	{

		GameObject* player = new GameObject{ "Qbert",-1 };
		float width{ 32.f }, height{ 32.f };
		int startTileX = static_cast<int>(m_pLevel->GetStartTilePlayer().x);
		int startTileY = static_cast<int>(m_pLevel->GetStartTilePlayer().y);
		player->AddComponent(new TransformComponent{ player, m_pLevel->GetStartpositionPlayer().x,m_pLevel->GetStartpositionPlayer().y,width,height });
		player->AddComponent(new AnimationComponent{ player,4,2,"Textures/Qbert.png",SDL_Rect{0,0,16,16} });
		player->AddComponent(new MovementComponent{ player,m_pLevel ,startTileX,startTileY,MovementComponent::EntityType::Qbert });
		player->AddComponent(new PlayerCollisionComponent{ player });
		return player;
	}
	else if (playerIndex == 1)
	{
		float StartPosX{ 510.f }, StartPosY{ 370.f };
		GameObject* player = new GameObject{ "Qbert2",-1 };
		float width{ 32.f }, height{ 32.f };
		player->AddComponent(new TransformComponent{ player, StartPosX,StartPosY,width,height });
		player->AddComponent(new AnimationComponent{ player,4,2,"Textures/Qbert.png",SDL_Rect{0,0,16,16} });
		player->AddComponent(new MovementComponent{ player,m_pLevel ,6,0,MovementComponent::EntityType::Qbert });
		player->AddComponent(new PlayerCollisionComponent{ player });
		return player;
	}
	return nullptr;
}

dae::GameObject* dae::QbertGame::CreateLifeDisplay(GameObject* player, const int lives, int playerIndex) const
{

	if (playerIndex == 0)
	{

		GameObject* playerLivesDisplay = new GameObject{ "LivesDisplay" ,-1 };
		playerLivesDisplay->AddComponent(new TransformComponent{ playerLivesDisplay });
		const auto sansFont = ResourceManager::GetInstance().LoadFont("Comic_Sans.otf", 18);
		auto livesDisplay = new PlayerLivesDisplay{ playerLivesDisplay, sansFont,lives,0.f };
		player->GetComponent<PlayerComponent>()->AddObserver(livesDisplay);
		playerLivesDisplay->AddComponent(livesDisplay);



		return playerLivesDisplay;
	}
	if (playerIndex == 1)
	{

	}
	return nullptr;
}

dae::GameObject* dae::QbertGame::CreateScoreDisplay(GameObject* player, int playerIndex) const
{
	if (playerIndex == 0)
	{
		GameObject* playerScoreDisplay = new GameObject{ "scoreDisplay",-1 };
		playerScoreDisplay->AddComponent(new TransformComponent{ playerScoreDisplay });
		const auto sansFont = ResourceManager::GetInstance().LoadFont("Comic_Sans.otf", 18);
		auto scoreDisplay = new PlayerScoreDisplay{ playerScoreDisplay, sansFont,0.f,30.f };
		player->GetComponent<PlayerComponent>()->AddObserver(scoreDisplay);
		playerScoreDisplay->AddComponent(scoreDisplay);

		return playerScoreDisplay;

	}
	if (playerIndex == 1)
	{

	}
	return nullptr;
}

dae::GameObject* dae::QbertGame::CreateCoily(GameObject* player) const
{
	float StartPosX{ 320.f }, StartPosY{ 85.f }, StartPosFallY{ -50.f }, spawnDuration{ 1.5f };
	float width{ 32.f }, height{ 32.f };
	int numAnim{ 1 }, numFrames{ 2 };
	int row = (int)m_pLevel->GetStartTilePlayer().x;
	int column = (int)m_pLevel->GetStartTilePlayer().y;

	GameObject* coily = new GameObject{ "Coily" ,0 };
	coily->AddComponent(new TransformComponent{ coily,StartPosX,StartPosFallY,width,height });
	coily->AddComponent(new AnimationComponent{ coily,numAnim,numFrames,"Textures/Coily_Egg.png",SDL_Rect{0,0,16,16} });
	coily->AddComponent(new CoilyComponent{ coily,player,spawnDuration,StartPosX,StartPosY });
	coily->AddComponent(new MovementComponent{ coily,m_pLevel ,row,column ,MovementComponent::EntityType::Coily,true });

	return coily;
}

dae::GameObject* dae::QbertGame::CreateWrongway() const
{
	float StartPosX{ 105.f }, StartPosY{ 410.f };
	float width{ 32.f }, height{ 32.f };
	int numAnim{ 2 }, numFrames{ 2 }, startTileX{ 0 }, startTileY{ -1 };

	GameObject* wrongway = new GameObject{ "Wrongway",1 };
	wrongway->AddComponent(new TransformComponent{ wrongway,StartPosX,StartPosY,width,height });
	wrongway->AddComponent(new AnimationComponent{ wrongway,numAnim,numFrames,"Textures/Wrongway.png",SDL_Rect{0,0,16,16} });
	wrongway->AddComponent(new MovementComponent{ wrongway,m_pLevel,startTileX,startTileY,MovementComponent::EntityType::Wrongway,false });
	wrongway->AddComponent(new UggWrongwayComponent{ wrongway,UggWrongwayComponent::UggWrongwayForm::wrongway,StartPosX,StartPosY });

	return wrongway;
}

dae::GameObject* dae::QbertGame::CreateUgg() const
{

	float StartPosX{ 530.f }, StartPosY{ 410.f };
	float width{ 32.f }, height{ 32.f };
	int numAnim{ 2 }, numFrames{ 2 }, startTileX{ 7 }, startTileY{ -1 };

	GameObject* ugg = new GameObject{ "Ugg",1 };
	ugg->AddComponent(new TransformComponent{ ugg,StartPosX,StartPosY,width,height });
	ugg->AddComponent(new AnimationComponent{ ugg,numAnim,numFrames,"Textures/Ugg.png",SDL_Rect{0,0,16,16} });
	ugg->AddComponent(new MovementComponent{ ugg,m_pLevel,startTileX,startTileY,MovementComponent::EntityType::Ugg,false });
	ugg->AddComponent(new UggWrongwayComponent{ ugg,UggWrongwayComponent::UggWrongwayForm::ugg,StartPosX,StartPosY });

	return ugg;
}

dae::GameObject* dae::QbertGame::CreateSlick() const
{
	float StartPosX{ 220.f }, StartPosY{ 225.f }, spawnDuration{ 4.5f };
	float width{ 32.f }, height{ 32.f };
	int numAnim{ 1 }, numFrames{ 2 }, startTileX{ 0 }, startTileY{ 3 };

	GameObject* slick = new GameObject{ "Slick" ,2 };
	slick->AddComponent(new TransformComponent{ slick,StartPosX,StartPosY,width,height });
	slick->AddComponent(new AnimationComponent{ slick,numAnim,numFrames,"Textures/Slick.png",SDL_Rect{0,0,12,16} });
	slick->AddComponent(new MovementComponent{ slick,m_pLevel ,startTileX,startTileY,MovementComponent::EntityType::Slick ,true });
	slick->AddComponent(new SlickSamComponent{ slick,spawnDuration,StartPosX,StartPosY });
	return slick;

}

dae::GameObject* dae::QbertGame::CreateSam() const
{
	float StartPosX{ 420.f }, StartPosY{ 225.f }, spawnDuration{ 4.5f };
	float width{ 32.f }, height{ 32.f };
	int numAnim{ 1 }, numFrames{ 2 }, startTileX{ 3 }, startTileY{ 3 };

	GameObject* slick = new GameObject{ "Sam" ,2 };
	slick->AddComponent(new TransformComponent{ slick,StartPosX,StartPosY,width,height });
	slick->AddComponent(new AnimationComponent{ slick,numAnim,numFrames,"Textures/Sam.png",SDL_Rect{0,0,12,16} });
	slick->AddComponent(new MovementComponent{ slick,m_pLevel ,startTileX,startTileY,MovementComponent::EntityType::Slick ,true });
	slick->AddComponent(new SlickSamComponent{ slick,spawnDuration,StartPosX,StartPosY });
	return slick;
}

void dae::QbertGame::SetupKeybindings(MovementComponent* pMovementComponent, MovementComponent* pMovementComponent2, MenuSelectorComponent* pMenuSelector) const
{

	//Controller
	InputManager::GetInstance().AddButtonCommand(ControllerButton::ButtonB, new MovementCommand(pMovementComponent2, MovementComponent::MovementDirection::up_right));
	InputManager::GetInstance().AddButtonCommand(ControllerButton::ButtonY, new MovementCommand(pMovementComponent2, MovementComponent::MovementDirection::up_left));
	InputManager::GetInstance().AddButtonCommand(ControllerButton::ButtonA, new MovementCommand(pMovementComponent2, MovementComponent::MovementDirection::down_right));
	InputManager::GetInstance().AddButtonCommand(ControllerButton::ButtonX, new MovementCommand(pMovementComponent2, MovementComponent::MovementDirection::down_left));

	InputManager::GetInstance().AddButtonCommand(ControllerButton::DownDPad, new MenuSelectCommand(pMenuSelector, MenuSelectCommand::MenuMovement::down));
	InputManager::GetInstance().AddButtonCommand(ControllerButton::UpDPad, new MenuSelectCommand(pMenuSelector, MenuSelectCommand::MenuMovement::up));
	InputManager::GetInstance().AddButtonCommand(ControllerButton::Start, new MenuSelectCommand(pMenuSelector, MenuSelectCommand::MenuMovement::select));

	//KeyBoard
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_9, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::up_right));
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_7, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::up_left));
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_3, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::down_right));
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_KP_1, new MovementCommand(pMovementComponent, MovementComponent::MovementDirection::down_left));

	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_UP, new MenuSelectCommand(pMenuSelector, MenuSelectCommand::MenuMovement::up));
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_DOWN, new MenuSelectCommand(pMenuSelector, MenuSelectCommand::MenuMovement::down));
	InputManager::GetInstance().AddKeyCommand(SDL_SCANCODE_SPACE, new MenuSelectCommand(pMenuSelector, MenuSelectCommand::MenuMovement::select));
}

void dae::QbertGame::SetupAudio() const
{
	Audio* audio = new Audio_SDL{};
	Locator::Provide(new AudioLogger{ *audio });
	AudioManager::GetInstance().AddSound("../Data/Audio/Jump1.wav", 0);
	AudioManager::GetInstance().AddSound("../Data/Audio/Jump2.wav", 1);
}
