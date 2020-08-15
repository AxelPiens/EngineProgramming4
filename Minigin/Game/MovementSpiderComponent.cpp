#include "MiniginPCH.h"
#include "MovementSpiderComponent.h"
#include "Components.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Collision.h"

MovementSpiderComponent::MovementSpiderComponent(float speed)
	:m_Speed{speed}
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
	//first check for block in front of it or border
	//if theres a block check 90 degrees to the right
	//ex. <- then ^ or ^ then ->

	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	auto colliders = scene->GetColliders();


	float posX = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 27;
	float posY = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 5;
	SDL_Rect m_Collider;
	m_Collider.x = posX;
	m_Collider.y = posY;
	m_Collider.w = 1;
	m_Collider.h = 1;

	float velX = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().x;
	float velY = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().y;
	bool foundBlock = false;
	if (velX != 0)
	{
		if (velX > 0)//right
		{
			for (auto trigger : triggers)
			{
				if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
				{
					std::cout << "DOWN\n";
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(m_Speed);
					foundBlock = true;
					break;
				}
			}
			if (!foundBlock)
			{
				for (auto col : colliders)
				{
					if (engine::Collision::AABB(m_Collider, col->GetCollider()))
					{
						m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
						m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(-m_Speed);
						break;
					}
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
					std::cout << "UP\n";
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(-m_Speed);
					foundBlock = true;
					break;
				}
			}
			if (!foundBlock)
			{
				for (auto col : colliders)
				{
					if (engine::Collision::AABB(m_Collider, col->GetCollider()))
					{
						m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
						m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
						break;
					}
				}
			}
		}
	}
	else if (velY != 0)
	{
		if (velY > 0)//down
		{
			m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 5;
			m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 27;

			for (auto trigger : triggers)
			{
				if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
				{
					std::cout << "RIGHT\n";
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
					foundBlock = true;
					break;
				}
			}
			if (!foundBlock)
			{
				m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 27;
				for (auto col : colliders)
				{
					if (engine::Collision::AABB(m_Collider, col->GetCollider()))
					{
						m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
						m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(-m_Speed);
						break;
					}
				}
			}
		}
		else // up
		{
			m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 5;
			m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y;
			for (auto trigger : triggers)
			{
				if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
				{
					std::cout << "LEFT\n";
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
					m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(-m_Speed);
					foundBlock = true;
					break;
				}
			}
			if (!foundBlock)
			{
				for (auto col : colliders)
				{
					if (engine::Collision::AABB(m_Collider, col->GetCollider()))
					{
						m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(m_Speed);
						m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
						break;
					}
				}
			}
		}
	}


	//posX = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x;
	//posY = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y;
	//if (posX < 0)
	//{
	//	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
	//	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
	//}
	//else if (posX > 405)
	//{
	//	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
	//	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(-m_Speed);
	//}
	//if (posY < 0)
	//{
	//	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(m_Speed);
	//	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
	//}
	//else if (posY > 243)
	//{
	//	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(-m_Speed);
	//	m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
	//}



}
