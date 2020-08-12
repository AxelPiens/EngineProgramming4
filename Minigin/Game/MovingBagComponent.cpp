#include "MiniginPCH.h"
#include "MovingBagComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collision.h"
#include "SpriteComponent.h"
#include "ColliderComponent.h"

MovingBagComponent::MovingBagComponent()
{
}

void MovingBagComponent::Update(float deltaTime)
{
	if (m_IsMoving)
	{
		int modulo = int(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) % 27;
		if (modulo == 0)
		{
			m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
			m_IsMoving = false;
		}

	}
	CheckForBlock();

	if (m_CanFall)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_TimeToFall)
		{
			m_IsFalling = true;
			m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(70.f);
			m_ElapsedTime = 0.f;
		}
	}
	else
	{
		m_IsFalling = false;
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0.f);
	}

}

void MovingBagComponent::Render()
{
}

void MovingBagComponent::CheckForBlock()
{
	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();

	float posX = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 12;
	float posY = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 28;
	bool allFailed = true;
	SDL_Rect m_Collider;
	m_Collider.x = posX;
	m_Collider.y = posY;
	m_Collider.w = 1;
	m_Collider.h = 1;

	
	bool removeBlock = false;
	for (auto trigger : triggers)

	{
		if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
		{
			m_CanFall = false;
			if (m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y - m_OldPosY > 32)
			{
				std::cout << "FELL 2 BLOCKS\n";
				removeBlock = true;
			}

			m_OldPosY = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y;
			break;
		}
		else
			m_CanFall = true;
	}

	if (removeBlock)
	{
		SpawnGold();
		scene->RemoveGameObject(m_pGameObject->GetName());
	}
}

void MovingBagComponent::SpawnGold()
{
	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto coins = std::make_shared<engine::GameObject>("coins");
	coins->AddComponent(new TransformComponent(27, 15, 100));
	coins->GetComponent<TransformComponent>()->Translate(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x, 
		m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 13, 0);
	coins->AddComponent(new SpriteComponent("/Digger/coins.png", 27, 15, 0, 0, 8, 50, false));
	coins->AddComponent(new ColliderComponent("coins", true, 0, 0));

	scene->AddGameobject(coins);

}
