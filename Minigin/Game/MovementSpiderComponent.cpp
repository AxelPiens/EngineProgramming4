#include "MiniginPCH.h"
#include "MovementSpiderComponent.h"
#include "Components.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Collision.h"

MovementSpiderComponent::MovementSpiderComponent(float speed)
{
}

void MovementSpiderComponent::Update(float deltaTime)
{
	CheckForBlocksInFront();
}

void MovementSpiderComponent::Render()
{
}

void MovementSpiderComponent::CheckForBlocksInFront()
{
	//first check for block in front of it
	//if theres a block check 90 degrees to the right
	//ex. <- then ^ or ^ then ->

	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	float posX = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 27;
	float posY = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 5;
	SDL_Rect m_Collider;
	m_Collider.x = posX;
	m_Collider.y = posY;
	m_Collider.w = 1;
	m_Collider.h = 1;

	float velX = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().x;
	float velY = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().y;
	if (velX != 0)
	{
		if (velX > 0)//right
		{
			for (auto trigger : triggers)
			{
				if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
				{
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
				}
			}
		}
		else // left
		{
			m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x - 2;

			for (auto trigger : triggers)
			{
				if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
				{
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
				}
			}
		}
	}
	else if (velY != 0)
	{

	}
}
