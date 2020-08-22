#include "MiniginPCH.h"
#include "SpiderSpawnComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Components.h"
#include "MovementSpiderComponent.h"
#include "TurnHobbinComponent.h"
#include "ChangeSpriteComponent.h"
#include "StateComponent.h"


SpiderSpawnComponent::SpiderSpawnComponent(int amountOfSpawns, float spawnTime)
	:m_AmountOfSpawns{amountOfSpawns}
	, m_SpawnTime{spawnTime}
{
}

void SpiderSpawnComponent::Update(float deltaTime)
{
	if (m_AmountOfSpawns > 0)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_SpawnTime)
		{
			m_ElapsedTime = 0.0f;
			--m_AmountOfSpawns;
			auto scene = engine::SceneManager::GetInstance().GetScene("Game");
			//spidertest
			auto spider = std::make_shared<engine::GameObject>("spider" + std::to_string(m_Number));
			spider->AddComponent(new SpriteComponent(("/Digger/spiders.png"), 27, 27, 0, 0, 6, 150, true));
			spider->AddComponent(new TransformComponent(27, 28, 200));
			spider->GetComponent<TransformComponent>()->Translate(375, 54, 0);
			spider->GetComponent<TransformComponent>()->SetVelocityX(50);
			spider->AddComponent(new MovementSpiderComponent(50));
			spider->AddComponent(new ColliderComponent("spider" + std::to_string(m_Number), true, 0, 0));
			spider->AddComponent(new ChangeSpriteComponent());
			spider->AddComponent(new TurnHobbinComponent(5.0f, 2.5f));
			spider->AddComponent(new StateComponent());
			scene->AddGameobject(spider);
			spider->GetComponent<StateComponent>()->ChangeScoresState(Scores::Nobbins);
			++m_Number;

		}
	}
}

void SpiderSpawnComponent::Render()
{
}
