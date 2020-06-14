#include "MiniginPCH.h"
#include "Minigin.h"
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

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
	SDL_Init(SDL_INIT_AUDIO);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		throw std::runtime_error(std::string("SDL_Audio Error: ") + Mix_GetError());

	bgm = Mix_LoadMUS("../Data/Audio/BackgroundMusic.mp3");


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
void dae::Minigin::LoadGame(int level) const
{
	Mix_PlayMusic(bgm, -1);

	auto& scene = SceneManager::GetInstance().CreateScene("Game");

	//player
	auto go = std::make_shared<GameObject>("player", dae::PlayerStates::Idle, dae::EnemyStates::Nothing, dae::EnemyType::Nothing);
	go->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 0, 0, 8, 150, true));
	go->AddComponent(new TransformComponent(30, 32, 200));
	go->GetComponent<TransformComponent>()->Translate(240, 180, 0);
	go->AddComponent(new ColliderComponent("player", false));
	go->AddComponent(new ControlComponent());
	go->AddComponent(new RigidbodyComponent(1.0f, 50.0f, -150.f, 75.0f));
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
			auto brick = std::make_shared<GameObject>("level" + std::to_string(i), dae::PlayerStates::Nothing, dae::EnemyStates::Nothing, dae::EnemyType::Nothing);
			brick->AddComponent(new TransformComponent(8, 8, 0));
			brick->GetComponent<TransformComponent>()->Translate(16.f * moduloX, float(posY), 0.f);
			brick->AddComponent(new SpriteComponent("blocks.png", 16, 16, ((level) / 10) * 8, ((level) % 10) * 8, 1, 1, false));
			brick->AddComponent(new ColliderComponent("level", false));
			scene.AddGameobject(brick);

		}

	}


	//enemy
	for (size_t i = 0; i < 2; i++)
	{
		auto enemy = std::make_shared<GameObject>("enemy" + std::to_string(i), dae::PlayerStates::Nothing, dae::EnemyStates::WalkRight, dae::EnemyType::ZenChan);
		enemy->AddComponent(new TransformComponent(32, 32, 0));
		enemy->GetComponent<TransformComponent>()->Translate(75 + (i * 300), 30, 0);
		enemy->AddComponent(new EnemyAIComponent(55, i));
		enemy->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 64, 0, 8, 50, true));
		enemy->AddComponent(new ColliderComponent("enemy", false));
		enemy->AddComponent(new RigidbodyComponent(1.0f, 50.0f, 0.f, 0.0f));
		enemy->GetComponent<RigidbodyComponent>()->SetOnGround(false);

		scene.AddGameobject(enemy);
	}

	auto enemy = std::make_shared<GameObject>("enemy3", dae::PlayerStates::Nothing, dae::EnemyStates::WalkRight, dae::EnemyType::Mighta);
	enemy->AddComponent(new TransformComponent(32, 32, 0));
	enemy->GetComponent<TransformComponent>()->Translate(200, 30, 0);
	enemy->AddComponent(new EnemyAIComponent(55, 3));
	enemy->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 64, 0, 8, 50, true));
	enemy->AddComponent(new ColliderComponent("enemy", false));
	enemy->AddComponent(new RigidbodyComponent(1.0f, 50.0f, 0.f, 0.0f));
	enemy->GetComponent<RigidbodyComponent>()->SetOnGround(false);

	scene.AddGameobject(enemy);

	auto bubble = std::make_shared<GameObject>("enemy", dae::PlayerStates::Nothing, dae::EnemyStates::Nothing, dae::EnemyType::Nothing);
	bubble->AddComponent(new TransformComponent(32, 32, 0));
	bubble->GetComponent<TransformComponent>()->Translate(75, 325, 0);
	bubble->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 512, 0, 8, 150, true));
	scene.AddGameobject(bubble);


	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>("FPS", dae::PlayerStates::Nothing, dae::EnemyStates::Nothing, dae::EnemyType::Nothing);
	to->AddComponent(new TextComponent());
	to->GetComponent<TextComponent>()->SetFont(font);
	to->GetComponent<TextComponent>()->SetPosition(10, 10);

	scene.AddGameobject(to);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	Mix_FreeMusic(bgm);
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	std::cout << "RUN\n";

	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame(m_LevelNumber);
	++m_LevelNumber;
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		input.SetKeyBoardCommands(new WalkLeftCommand(), new WalkRightCommand(), new JumpCommand(), new ShootCommand());
		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			const auto currentTime = high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			doContinue = !input.IsQuitting();
			sceneManager.Update(deltaTime);
			CollisionChecks();
			auto scene = sceneManager.GetScene("Game");
			LevelBoundaries(scene->GetPlayerEnemyColliders());
			CheckForNextLevel(deltaTime);
			renderer.Render();
		}
	}

	Cleanup();
}

void dae::Minigin::LevelBoundaries(std::vector<std::shared_ptr<GameObject>> players)
{
	for (auto player : players)
	{
		if (player->GetComponent<TransformComponent>()->GetPosition().y > m_WindowHeight)
		{
			player->GetComponent<TransformComponent>()->Move(0.f, -(m_WindowHeight+50.f), 0.f);
		}
	}
}

void dae::Minigin::CollisionChecks()
{
	auto& sceneManager = SceneManager::GetInstance();
	auto scene = sceneManager.GetScene("Game");

	auto colliders = scene->GetColliders();
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
				if (Collision::AABB(moveColl->GetComponent<ColliderComponent>()->GetCollider(), coll->GetCollider())) //player colliding with something
				{
					int name = moveColl->GetName().size();
					std::string name2 = moveColl->GetName();

						Vector3 pos = moveColl->GetComponent<TransformComponent>()->GetPosition();
						if (coll->GetCollider().y <= int(pos.y) + 2 && coll->GetCollider().y >= int(pos.y) - 2)
						{
							if (coll->GetCollider().x - pos.x < 0 && moveColl->GetComponent<TransformComponent>()->GetVelocity().x < 0)
							{
								if (moveColl->HasComponent<EnemyAIComponent>())
								{
									moveColl->GetComponent < EnemyAIComponent>()->SetSpeedDirection(-1);
									moveColl->SetEnemyState(dae::EnemyStates::WalkRight);
								}
								else
									moveColl->GetComponent<TransformComponent>()->SetVelocityX(0);

							}
							else if (coll->GetCollider().x - pos.x > 0 && moveColl->GetComponent<TransformComponent>()->GetVelocity().x > 0)
							{
								if (moveColl->HasComponent<EnemyAIComponent>())
								{
									moveColl->GetComponent < EnemyAIComponent>()->SetSpeedDirection(-1);
									moveColl->SetEnemyState(dae::EnemyStates::WalkLeft);
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


	auto triggers = scene->GetTriggers();
	for (auto trigger : triggers)
	{
		for (auto moveColl : playerEnemyColliders)
		{
			if (trigger->GetName().find("projectile") != std::string::npos && moveColl->GetName().find("enemy") != std::string::npos)
			{
				if (Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(),
					moveColl->GetComponent<ColliderComponent>()->GetCollider())) //projecitle colliding with enemy
				{
					scene->RemoveGameObject("projectile" + std::to_string(trigger->GetComponent<ProjectileComponent>()->GetNumber()));
					scene->RemoveGameObject("enemy" + std::to_string(moveColl->GetComponent<EnemyAIComponent>()->GetNumber()));

					if (moveColl->GetEnemyType() == dae::EnemyType::ZenChan)
					{
						//collider
						auto bubble = std::make_shared<GameObject>("bubble" + std::to_string(m_BubbleAmount), 
							dae::PlayerStates::Nothing, dae::EnemyStates::Nothing, dae::EnemyType::Mighta);
						bubble->AddComponent(new TransformComponent(16, 16, 100));
						bubble->GetComponent<TransformComponent>()->Translate(moveColl->GetComponent<TransformComponent>()->GetPosition());
						bubble->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 480, 0, 8, 200, true));
						bubble->GetComponent<TransformComponent>()->SetVelocityX(0);
						bubble->GetComponent<TransformComponent>()->SetVelocityY(-100 / 3);
						bubble->AddComponent(new TrappedBubbleComponent(8.0f, m_BubbleAmount));
						bubble->AddComponent(new ColliderComponent("bubble" + std::to_string(m_BubbleAmount), true));
						scene->AddGameobject(bubble);		
						m_BubbleAmount++;
					}
					else if (moveColl->GetEnemyType() == dae::EnemyType::Mighta)
					{
						auto bubble = std::make_shared<GameObject>("bubble" + std::to_string(m_BubbleAmount),
							dae::PlayerStates::Nothing, dae::EnemyStates::Nothing, dae::EnemyType::Mighta);
						bubble->AddComponent(new TransformComponent(16, 16, 100));
						bubble->GetComponent<TransformComponent>()->Translate(moveColl->GetComponent<TransformComponent>()->GetPosition());
						bubble->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 528, 0, 8, 200, true));
						bubble->GetComponent<TransformComponent>()->SetVelocityX(0);
						bubble->GetComponent<TransformComponent>()->SetVelocityY(-100 / 3);
						bubble->AddComponent(new TrappedBubbleComponent(8.0f, m_BubbleAmount));
						bubble->AddComponent(new ColliderComponent("bubble" + std::to_string(m_BubbleAmount), true));
						scene->AddGameobject(bubble);
						m_BubbleAmount++;
					}

				}
			}
			if (trigger->GetName().find("bubble") != std::string::npos && moveColl->GetName().find("player") != std::string::npos)
			{
				if (Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(),
					moveColl->GetComponent<ColliderComponent>()->GetCollider())) //bubble colliding with player
				{
					scene->RemoveGameObject("bubble" + std::to_string(trigger->GetComponent<TrappedBubbleComponent>()->GetNumber()));
					--m_EnemyCounter;
					//spawn food

				}
			}
		}
	}


	//enemy player collision
	for (size_t i = 1; i < playerEnemyColliders.size(); i++)
	{
		if (playerEnemyColliders[0]->GetPlayerState() != dae::PlayerStates::Death)
		{
			if (Collision::AABB(playerEnemyColliders[i]->GetComponent<ColliderComponent>()->GetCollider(),
				playerEnemyColliders[0]->GetComponent<ColliderComponent>()->GetCollider())) //projecitle colliding with enemy
			{
				playerEnemyColliders[0]->GetComponent<LiveComponent>()->LoseLive();
				m_Lives = playerEnemyColliders[0]->GetComponent<LiveComponent>()->GetLives();
			}
		}
	}
}

void dae::Minigin::CheckForNextLevel(float deltaTime)
{
	auto& sceneManager = SceneManager::GetInstance();

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
}

