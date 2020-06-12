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

using namespace std;
using namespace std::chrono;

void dae::Minigin::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}
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
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Game");

	auto go = std::make_shared<GameObject>("background");
	go->AddComponent(new TextureComponent("background.jpg"));
	go->AddComponent(new TransformComponent(5));
	go->GetComponent<TransformComponent>()->Translate(0, 0, 0);
	scene.AddGameobject(go);

	//player
	go = std::make_shared<GameObject>("player");
	go->AddComponent(new SpriteComponent("sprites0SMALL.png", 32, 32, 0, 0, 8, 250, true));
	go->AddComponent(new TransformComponent(30, 32, 200));
	go->GetComponent<TransformComponent>()->Translate(240, 180, 0);
	go->AddComponent(new ColliderComponent("player", false));
	go->AddComponent(new ControlComponent());
	go->AddComponent(new RigidbodyComponent(1.0f, 50.0f, -150.f, 75.0f));
	scene.AddGameobject(go);

	//level
	Parser parser{};
	int levelNr = 0;

	parser.ReadFile("../Data/SeperatedLevelData.dat", levelNr);
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
			auto brick = std::make_shared<GameObject>("level" + std::to_string(i));
			brick->AddComponent(new TransformComponent(8, 8, 0));
			brick->GetComponent<TransformComponent>()->Translate(16.f * moduloX, float(posY), 0.f);
			brick->AddComponent(new SpriteComponent("blocks.png", 16, 16, ((levelNr) / 10) * 8, ((levelNr) % 10) * 8, 1, 1, false));
			brick->AddComponent(new ColliderComponent("level", false));
			scene.AddGameobject(brick);

		}

	}

	//enemy
	auto enemy = std::make_shared<GameObject>("enemy");
	enemy->AddComponent(new TransformComponent(16, 16, 0));
	enemy->GetComponent<TransformComponent>()->Translate( 50, 350, 0);
	enemy->AddComponent(new EnemyAIComponent(75));
	enemy->AddComponent(new SpriteComponent("sprites0SMALL.png", 32, 32, 4 * 16, 0, 8, 50, true));
	enemy->AddComponent(new ColliderComponent("enemy", false));
	enemy->AddComponent(new RigidbodyComponent(0, 0, 0, 0));
	scene.AddGameobject(enemy);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto to = std::make_shared<GameObject>("FPS");
	to->AddComponent(new TextComponent());
	to->GetComponent<TextComponent>()->SetFont(font);
	to->GetComponent<TextComponent>()->SetPosition(10, 10);

	scene.AddGameobject(to);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
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

	LoadGame();
	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

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
			LevelBoundaries(scene->GetPlayers());
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
			player->GetComponent<TransformComponent>()->Move(0, -(m_WindowHeight+50), 0);
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
	for (auto coll : colliders)
	{
		for (auto moveColl : playerEnemyColliders)
		{
			moveColl->GetComponent<ColliderComponent>()->GetTag();
			if (moveColl->GetComponent<TransformComponent>()->GetVelocity().y >= 0)
			{
				if (Collision::AABB(moveColl->GetComponent<ColliderComponent>()->GetCollider(), coll->GetCollider())) //player colliding with something
				{
					if (!moveColl->GetComponent<RigidbodyComponent>()->GetIsJumping())
					{

						dae::Vector3 pos = moveColl->GetComponent<TransformComponent>()->GetPosition();
						if (coll->GetCollider().y <= int(pos.y) + 2 && coll->GetCollider().y >= int(pos.y) - 2)
						{
							if (coll->GetCollider().x - pos.x < 0 && moveColl->GetComponent<TransformComponent>()->GetVelocity().x < 0)
							{
								if (moveColl->HasComponent<EnemyAIComponent>())
									moveColl->GetComponent < EnemyAIComponent>()->SetSpeedDirection(-1);
								else
									moveColl->GetComponent<TransformComponent>()->SetVelocityX(0);

							}
							else if (coll->GetCollider().x - pos.x > 0 && moveColl->GetComponent<TransformComponent>()->GetVelocity().x > 0)
							{
								if (moveColl->HasComponent<EnemyAIComponent>())
									moveColl->GetComponent < EnemyAIComponent>()->SetSpeedDirection(-1);
								else
									moveColl->GetComponent<TransformComponent>()->SetVelocityX(0);
							}
						}
						else
						{
							moveColl->GetComponent<TransformComponent>()->SetVelocityY(0);
						}
					}
					onGround = true;
					moveColl->GetComponent<RigidbodyComponent>()->SetIsJumping(false);
				}
			}
		}
	}
	playerEnemyColliders[0]->GetComponent<RigidbodyComponent>()->SetOnGround(onGround);



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
					scene->RemoveGameObject("enemy");
				}
			}
		}
	}
}

