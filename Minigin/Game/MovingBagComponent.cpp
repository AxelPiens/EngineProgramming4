#include "MiniginPCH.h"
#include "MovingBagComponent.h"
#include "TransformComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Collision.h"

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

	bool hasBlock = true;
	bool removeBlock = false;
	for (auto trigger : triggers)

	{
		if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
		{
			hasBlock = true;
			if (m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y - m_OldPosY > 32)
			{
				std::cout << "FELL 2 BLOCKS\n";
				removeBlock = true;
			}

			m_OldPosY = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y;
			break;
		}
		else
			hasBlock = false;
	}

	if (hasBlock)
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0.f);
	else
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(70.f);

	if (removeBlock)
	{
		scene->RemoveGameObject(m_pGameObject->GetName());
		SpawnGold();
	}
}

void MovingBagComponent::SpawnGold()
{
}
