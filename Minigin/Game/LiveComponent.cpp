#include "MiniginPCH.h"
#include "LiveComponent.h"
#include "TransformComponent.h"
#include "StateComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "SpriteComponent.h"
#include "SpiderSpawnComponent.h"
LiveComponent::LiveComponent(int amountOfLives, float deathTime)
	:m_AmountOfLives{amountOfLives}
	, m_DeathTime{deathTime}
	, m_ElapsedTime{0.0f}
{

}

void LiveComponent::LoseLive()
{
	--m_AmountOfLives;
	m_HasLostLive = true;
}

void LiveComponent::Init()
{
	m_SpawnPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
}

void LiveComponent::Update(float deltaTime)
{
	std::cout << m_AmountOfLives << std::endl;
	if (m_HasLostLive)
	{
		auto scene = engine::SceneManager::GetInstance().GetScene("Game");
		auto objects = scene->GetObjects();
		for (auto obj : objects)
		{
			if (obj)
			{
				if (obj->GetName() == "lives")
					obj->GetComponent<SpriteComponent>()->ChangeWidth(21 * m_AmountOfLives);
			}
		}

		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_DeathTime)
		{
			std::cout << "RESPAWN\n";
			m_ElapsedTime = 0.0f;
			m_pGameObject->GetComponent<TransformComponent>()->Translate(m_SpawnPos);
			m_pGameObject->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::Idle);
			m_HasLostLive = false;

			scene->RemoveGameObject("spawner");
			for (size_t i = 0; i < 5; i++)
			{
				scene->RemoveGameObject("spider" + std::to_string(i));
			}
			auto spawnSpider = std::make_shared<engine::GameObject>("spawner");
			spawnSpider->AddComponent(new SpiderSpawnComponent(5, 4.0f));
			scene->AddGameobject(spawnSpider);

		}
	}
	if (m_AmountOfLives == 0)
		m_IsDeath = true;

}

void LiveComponent::Render()
{
}
