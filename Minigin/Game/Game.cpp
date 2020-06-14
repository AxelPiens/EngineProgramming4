#include "MiniginPCH.h"
#include "Game.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextObject.h"
#include "GameObject.h"
#include "Scene.h"
#include "Collision.h"
#include "Parser.h"
#include "ProjectileComponent.h"
#include "EnemyAIComponent.h"
#include "Components.h"
#include "..\Game\TrappedBubbleComponent.h"
#include "..\Game\LiveComponent.h"

using namespace std;
using namespace std::chrono;

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	SDL_Init(SDL_INIT_AUDIO);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		throw std::runtime_error(std::string("SDL_Audio Error: ") + Mix_GetError());

	m_BackgroundMusic = Mix_LoadMUS("../Data/Audio/BackgroundMusic.mp3");
	Mix_PlayMusic(m_BackgroundMusic, -1);


	m_WindowHeight = 400;
	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		510,
		m_WindowHeight,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);

}

/**
 * Code constructing the scene world starts here
 */
void Game::LoadGame(int level) const
{

	auto& scene = engine::SceneManager::GetInstance().CreateScene("Game");

	//player
	auto go = std::make_shared<engine::GameObject>("player", engine::PlayerStates::Idle, 
		engine::EnemyStates::Nothing, engine::EnemyType::Nothing, engine::FoodType::Nothing);
	go->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 0, 0, 8, 150, true));
	go->AddComponent(new TransformComponent(30, 32, 200));
	go->GetComponent<TransformComponent>()->Translate(240, 180, 0);
	go->AddComponent(new ColliderComponent("player", false));
	go->AddComponent(new ControlComponent());
	go->AddComponent(new RigidbodyComponent(1.0f, 50.0f, -155.f, 75.0f));
	go->AddComponent(new LiveComponent(m_Lives, 3.0f));
	scene.AddGameobject(go);
	go->GetComponent<LiveComponent>()->Init();
	//level
	Parser parser{};

	parser.ReadFile("../Data/SeperatedLevelData.dat", level);
	std::vector<int> levelData{};
	parser.GetLevelData(levelData);
	int posY = -16;
	int moduloX = 0;
	for (size_t i = 0; i < levelData.size(); i++)
	{
		moduloX = i % 32;
		if (moduloX == 0)
		{
			posY += 16;
		}
		if (levelData[i] == 1)
		{
			auto brick = std::make_shared<engine::GameObject>("level" + std::to_string(i), engine::PlayerStates::Nothing,
				engine::EnemyStates::Nothing, engine::EnemyType::Nothing, engine::FoodType::Nothing);
			brick->AddComponent(new TransformComponent(8, 8, 0));
			brick->GetComponent<TransformComponent>()->Translate(16.f * moduloX, float(posY), 0.f);
			brick->AddComponent(new SpriteComponent("blocks.png", 16, 16, ((level) / 10) * 8, ((level) % 10) * 8, 1, 1, false));
			brick->AddComponent(new ColliderComponent("level", false));
			scene.AddGameobject(brick);

		}

	}


	//enemy
	for (int i = 0; i < 2; i++)
	{
		auto enemy = std::make_shared<engine::GameObject>("enemy" + std::to_string(i), engine::PlayerStates::Nothing,
			engine::EnemyStates::WalkRight, engine::EnemyType::ZenChan, engine::FoodType::Nothing);
		enemy->AddComponent(new TransformComponent(25, 32, 0));
		enemy->GetComponent<TransformComponent>()->Translate(80 + (i * 300.f), 30.f, 0);
		enemy->AddComponent(new EnemyAIComponent(55.f, i));
		enemy->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 64, 0, 8, 50, true));
		enemy->AddComponent(new ColliderComponent("enemy", false));
		enemy->AddComponent(new RigidbodyComponent(1.0f, 50.0f, 0.f, 0.0f));
		enemy->GetComponent<RigidbodyComponent>()->SetOnGround(false);

		scene.AddGameobject(enemy);
	}

	auto enemy = std::make_shared<engine::GameObject>("enemy3", engine::PlayerStates::Nothing, engine::EnemyStates::WalkRight, 
		engine::EnemyType::Mighta, engine::FoodType::Nothing);
	enemy->AddComponent(new TransformComponent(25, 32, 0));
	enemy->GetComponent<TransformComponent>()->Translate(200, 30, 0);
	enemy->AddComponent(new EnemyAIComponent(55, 3));
	enemy->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 64, 0, 8, 50, true));
	enemy->AddComponent(new ColliderComponent("enemy", false));
	enemy->AddComponent(new RigidbodyComponent(1.0f, 50.0f, 0.f, 0.0f));
	enemy->GetComponent<RigidbodyComponent>()->SetOnGround(false);

	scene.AddGameobject(enemy);

	auto font = engine::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);


	auto lives = std::make_shared<engine::GameObject>("lives", engine::PlayerStates::Nothing, engine::EnemyStates::Nothing,
		engine::EnemyType::Nothing, engine::FoodType::Nothing);
	lives->AddComponent(new TextComponent());
	lives->GetComponent<TextComponent>()->SetFont(font);
	lives->GetComponent<TextComponent>()->SetPosition(450, 20);
	lives->GetComponent<TextComponent>()->SetText(to_string(m_Lives));
	scene.AddGameobject(lives);


	auto score = std::make_shared<engine::GameObject>("score", engine::PlayerStates::Nothing, engine::EnemyStates::Nothing,
		engine::EnemyType::Nothing, engine::FoodType::Nothing);
	score->AddComponent(new TextComponent());
	score->GetComponent<TextComponent>()->SetFont(font);
	score->GetComponent<TextComponent>()->SetPosition(250, 20);
	score->GetComponent<TextComponent>()->SetText(to_string(m_Score));
	scene.AddGameobject(score);

	auto to = std::make_shared<engine::GameObject>("FPS", engine::PlayerStates::Nothing, engine::EnemyStates::Nothing, 
		engine::EnemyType::Nothing, engine::FoodType::Nothing);
	to->AddComponent(new TextComponent());
	to->GetComponent<TextComponent>()->SetFont(font);
	to->GetComponent<TextComponent>()->SetPosition(30, 15);

	scene.AddGameobject(to);


}

void Game::Cleanup()
{
	Renderer::GetInstance().Destroy();
	Mix_FreeMusic(m_BackgroundMusic);
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Game::Run()
{

	Initialize();

	// tell the resource manager where he can find the game data
	engine::ResourceManager::GetInstance().Init("../Data/");

	LoadGame(m_LevelNumber);
	++m_LevelNumber;
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = engine::SceneManager::GetInstance();
		auto& input = engine::InputManager::GetInstance();
		input.SetKeyBoardCommands(new engine::WalkLeftCommand(), new engine::WalkRightCommand(), new engine::JumpCommand(), new engine::ShootCommand());
		input.SetControllerCommands(new engine::ShootCommand(), new engine::WalkLeftCommand(), new engine::JumpCommand(), new engine::WalkRightCommand());

		auto lastTime = std::chrono::high_resolution_clock::now();
		while (m_Continue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			m_Continue = !input.IsQuitting();
			sceneManager.Update(deltaTime);
			CollisionChecks();
			auto scene = sceneManager.GetScene("Game");
			LevelBoundaries(scene->GetPlayerEnemyColliders());
			CheckForNextLevel(deltaTime);
			ChangeTexts();
			CheckForDeath();
			renderer.Render();
		}
	}

	Cleanup();
}

void Game::LevelBoundaries(std::vector<std::shared_ptr<engine::GameObject>> players)
{
	for (auto player : players)
	{
		if (player->GetComponent<TransformComponent>()->GetPosition().y > m_WindowHeight)
		{
			player->GetComponent<TransformComponent>()->Move(0.f, -(m_WindowHeight+50.f), 0.f);
		}
		if (player->GetComponent<TransformComponent>()->GetPosition().y < 16)
		{
			player->GetComponent<TransformComponent>()->Move(0.f, 2.0f, 0.f);
			player->GetComponent<TransformComponent>()->SetVelocityY(0);
		}

	}
}

void Game::CollisionChecks()
{
	auto& sceneManager = engine::SceneManager::GetInstance();
	auto scene = sceneManager.GetScene("Game");

	std::vector<ColliderComponent*> colliders = scene->GetColliders();
	auto playerEnemyColliders = scene->GetPlayerEnemyColliders();

	bool onGround = false;
	bool onGroundFinal = false;
	for (auto coll : colliders)
	{
		for (auto moveColl : playerEnemyColliders)
		{
			moveColl->GetComponent<ColliderComponent>()->GetTag();
			if (moveColl->GetComponent<TransformComponent>()->GetVelocity().y >= 0)
			{
				if (engine::Collision::AABB(moveColl->GetComponent<ColliderComponent>()->GetCollider(), coll->GetCollider())) //player colliding with something
				{
						engine::Vector3 pos = moveColl->GetComponent<TransformComponent>()->GetPosition();
						if (coll->GetCollider().y <= int(pos.y) + 2 && coll->GetCollider().y >= int(pos.y) - 2)
						{
							if (coll->GetCollider().x - pos.x < 0 && moveColl->GetComponent<TransformComponent>()->GetVelocity().x < 0)
							{
								if (moveColl->HasComponent<EnemyAIComponent>())
								{
									moveColl->GetComponent < EnemyAIComponent>()->SetSpeedDirection(-1);
									moveColl->SetEnemyState(engine::EnemyStates::WalkRight);
								}
								else
									moveColl->GetComponent<TransformComponent>()->SetVelocityX(0);

							}
							else if (coll->GetCollider().x - pos.x > 0 && moveColl->GetComponent<TransformComponent>()->GetVelocity().x > 0)
							{
								if (moveColl->HasComponent<EnemyAIComponent>())
								{
									moveColl->GetComponent < EnemyAIComponent>()->SetSpeedDirection(-1);
									moveColl->SetEnemyState(engine::EnemyStates::WalkLeft);
								}
								else
									moveColl->GetComponent<TransformComponent>()->SetVelocityX(0);
							}
						}
						else
						{
							moveColl->GetComponent<TransformComponent>()->SetVelocityY(0);
						}
					onGround = true;
					moveColl->GetComponent<RigidbodyComponent>()->SetOnGround(onGround);
					onGroundFinal = true;
					moveColl->GetComponent<RigidbodyComponent>()->SetIsJumping(false);
					//break;
				}
				else
					onGround = false;
			}
			else
				onGround = false;
			if(!onGroundFinal)
				moveColl->GetComponent<RigidbodyComponent>()->SetOnGround(onGround);
		}
	}

	//enemy player collision
	for (size_t i = 1; i < playerEnemyColliders.size(); i++)
	{
		if (playerEnemyColliders[0]->GetPlayerState() != engine::PlayerStates::Death)
		{
			if (engine::Collision::AABB(playerEnemyColliders[i]->GetComponent<ColliderComponent>()->GetCollider(),
				playerEnemyColliders[0]->GetComponent<ColliderComponent>()->GetCollider())) //projecitle colliding with enemy
			{
				playerEnemyColliders[0]->GetComponent<LiveComponent>()->LoseLive();
				m_Lives = playerEnemyColliders[0]->GetComponent<LiveComponent>()->GetLives();
			}
		}
	}

	auto triggers = scene->GetTriggers();
	for (auto trigger : triggers)
	{
		for (auto moveColl : playerEnemyColliders)
		{
			if (trigger->GetName().find("projectile") != std::string::npos && moveColl->GetName().find("enemy") != std::string::npos)
			{
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(),
					moveColl->GetComponent<ColliderComponent>()->GetCollider())) //projecitle colliding with enemy
				{
					scene->RemoveGameObject("projectile" + std::to_string(trigger->GetComponent<ProjectileComponent>()->GetNumber()));
					scene->RemoveGameObject("enemy" + std::to_string(moveColl->GetComponent<EnemyAIComponent>()->GetNumber()));
					//collider
					auto bubble = std::make_shared<engine::GameObject>("bubble" + std::to_string(m_BubbleAmount),
						engine::PlayerStates::Nothing, engine::EnemyStates::Nothing, moveColl->GetEnemyType(), engine::FoodType::Nothing);
					bubble->AddComponent(new TransformComponent(16, 16, 100));
					bubble->GetComponent<TransformComponent>()->Translate(moveColl->GetComponent<TransformComponent>()->GetPosition());

					if (moveColl->GetEnemyType() == engine::EnemyType::ZenChan) //because of sprites
					{
						bubble->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 480, 0, 8, 200, true));
					}
					else if (moveColl->GetEnemyType() == engine::EnemyType::Mighta)
					{
						bubble->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 528, 0, 8, 200, true));
					}
					bubble->GetComponent<TransformComponent>()->SetVelocityX(0);
					bubble->GetComponent<TransformComponent>()->SetVelocityY(-100 / 3);
					bubble->AddComponent(new TrappedBubbleComponent(8.0f, m_BubbleAmount));
					bubble->AddComponent(new ColliderComponent("bubble" + std::to_string(m_BubbleAmount), true));
					scene->AddGameobject(bubble);
					m_BubbleAmount++;

				}
			}
			if (trigger->GetName().find("bubble") != std::string::npos && moveColl->GetName().find("player") != std::string::npos)
			{
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(),
					moveColl->GetComponent<ColliderComponent>()->GetCollider())) //bubble colliding with player
				{
					scene->RemoveGameObject("bubble" + std::to_string(trigger->GetComponent<TrappedBubbleComponent>()->GetNumber()));
					--m_EnemyCounter;

					//spawn food
					if (trigger->GetEnemyType() == engine::EnemyType::ZenChan)
					{
						auto food = std::make_shared<engine::GameObject>("food" + to_string(m_FoodNumber), engine::PlayerStates::Nothing, 
							engine::EnemyStates::Nothing, engine::EnemyType::Nothing, engine::FoodType::Melon);
						food->AddComponent(new TransformComponent(25, 32, 0));
						food->GetComponent<TransformComponent>()->Translate(440, 360, 0);
						food->AddComponent(new SpriteComponent("spritesfood.png", 34, 24, 20, 30, 0, 0, false));
						food->AddComponent(new ColliderComponent("food" + to_string(m_FoodNumber), true));

						scene->AddGameobject(food);
					}
					else if (trigger->GetEnemyType() == engine::EnemyType::Mighta)
					{
						auto food = std::make_shared<engine::GameObject>("food" + to_string(m_FoodNumber), engine::PlayerStates::Nothing,
							engine::EnemyStates::Nothing, engine::EnemyType::Nothing, engine::FoodType::Fries);
						food->AddComponent(new TransformComponent(25, 32, 0));
						food->GetComponent<TransformComponent>()->Translate(160, 180, 0);
						food->AddComponent(new SpriteComponent("spritesfood.png", 30, 32, 32, 0, 0, 0, false));
						food->AddComponent(new ColliderComponent("food" + to_string(m_FoodNumber), true));

						scene->AddGameobject(food);
					}
					++m_FoodNumber;

				}
			}
			if (trigger->GetName().find("boulder") != std::string::npos && moveColl->GetName().find("player") != std::string::npos)
			{
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(),
					moveColl->GetComponent<ColliderComponent>()->GetCollider())) //bubble colliding with player
				{
					scene->RemoveGameObject("boulder" + std::to_string(trigger->GetComponent<ProjectileComponent>()->GetNumber()));
					if (playerEnemyColliders[0]->GetPlayerState() != engine::PlayerStates::Death)
					{
						playerEnemyColliders[0]->GetComponent<LiveComponent>()->LoseLive();
					}
				}
			}
			if (trigger->GetName().find("food") != std::string::npos && moveColl->GetName().find("player") != std::string::npos)
			{
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(),
					moveColl->GetComponent<ColliderComponent>()->GetCollider())) //bubble colliding with player
				{
					if (playerEnemyColliders[0]->GetPlayerState() != engine::PlayerStates::Death)
					{
						if(trigger->GetFoodType() == engine::FoodType::Melon)
							m_Score += 100;
						else if(trigger->GetFoodType() == engine::FoodType::Fries)
							m_Score += 200;

						scene->RemoveGameObject(trigger->GetComponent<ColliderComponent>()->GetTag());
					}
				}
			}
		}
	}

}

void Game::CheckForNextLevel(float deltaTime)
{
	auto& sceneManager = engine::SceneManager::GetInstance();

	if (m_EnemyCounter == 0)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_NextLevelTime)
		{
			m_ElapsedTime = 0.0f;
			sceneManager.RemoveScene("Game");
			LoadGame(m_LevelNumber);
			++m_LevelNumber;
			m_EnemyCounter = 3;
		}
	}
	if (m_LevelNumber > 2)
		m_Continue = false;
}

void Game::ChangeTexts()
{
	auto& sceneManager = engine::SceneManager::GetInstance();
	auto scene = sceneManager.GetScene("Game");

	std::vector<std::shared_ptr<engine::GameObject>> texts = scene->GetTexts();
	texts[0]->GetComponent<TextComponent>()->SetText(to_string(m_Lives));
	texts[1]->GetComponent<TextComponent>()->SetText(to_string(m_Score));
}

void Game::CheckForDeath()
{
	auto& sceneManager = engine::SceneManager::GetInstance();
	auto scene = sceneManager.GetScene("Game");
	if (scene->GetPlayers()[0]->GetComponent<LiveComponent>()->IsDeath())
		m_Continue = false;
	
}

