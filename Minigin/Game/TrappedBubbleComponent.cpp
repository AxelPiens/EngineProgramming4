#include "MiniginPCH.h"
#include "TrappedBubbleComponent.h"
#include "Scene.h"
#include "Components.h"
#include "SceneManager.h"
#include "EnemyAIComponent.h"
#include "GameObject.h"
TrappedBubbleComponent::TrappedBubbleComponent(float lifeTime, int bubbleNumber)
	:m_LifeTime{lifeTime},
	m_Number{bubbleNumber}
{
}

void TrappedBubbleComponent::Update(float deltaTime)
{
	m_ElapsedTime += deltaTime;
	if (m_ElapsedTime > m_LifeTime)
	{
		//spawn enemy again
		auto scene = dae::SceneManager::GetInstance().GetScene("Game");
		auto enemy = std::make_shared<dae::GameObject>("enemy", dae::PlayerStates::Nothing, dae::EnemyStates::WalkRight, dae::EnemyType::ZenChan);
		enemy->AddComponent(new TransformComponent(32, 32, 0));
		enemy->GetComponent<TransformComponent>()->Translate(m_pGameObject->GetComponent<TransformComponent>()->GetPosition());
		enemy->AddComponent(new EnemyAIComponent(55));
		enemy->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 64, 0, 8, 50, true));
		enemy->AddComponent(new ColliderComponent("enemy", false));
		enemy->AddComponent(new RigidbodyComponent(50.0f, 50.0f, 0.f, 0.0f));
		scene->AddGameobject(enemy);
		scene->RemoveGameObject("bubble" + std::to_string(m_Number));
	}


}

void TrappedBubbleComponent::Render()
{
}
