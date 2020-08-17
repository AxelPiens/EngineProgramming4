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
	//

	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	auto colliders = scene->GetColliders();



	SDL_Rect m_Collider;
	m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 50;
	m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 7;
	m_Collider.w = 1;
	m_Collider.h = 1;

	float velX = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().x;
	float velY = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().y;
	bool foundBlock = false;
	bool foundBlockRight = false;
	bool foundBlockLeft = false;
	bool foundBlockUp = false;
	bool foundBlockDown = false;

	for (auto trigger : triggers)
	{
		if( trigger->GetName().find("level") != std::string::npos)
		{
			m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 27;
			m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 5;
			if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_Collider)) // right
			{
				foundBlockRight = true;
			}
			m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x;
			m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 5;
			if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_Collider)) //left
			{
				foundBlockLeft = true;
			}
			m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 5;
			m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y;
			if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_Collider)) //up
			{
				foundBlockUp = true;
			}
			m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 5;
			m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 27;
			if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_Collider)) //down
			{
				foundBlockDown = true;
			}
		}
	}

	for (auto collider : colliders)
	{
		m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 27;
		m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 5;
		if (engine::Collision::AABB(collider->GetCollider(), m_Collider)) // right
		{
			foundBlockRight = true;
		}
		m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x;
		m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 5;
		if (engine::Collision::AABB(collider->GetCollider(), m_Collider)) //left
		{
			foundBlockLeft = true;
		}
		m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 5;
		m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y;
		if (engine::Collision::AABB(collider->GetCollider(), m_Collider)) //up
		{
			foundBlockUp = true;
		}
		m_Collider.x = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + 5;
		m_Collider.y = m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + 27;
		if (engine::Collision::AABB(collider->GetCollider(), m_Collider)) //down
		{
			foundBlockDown = true;
		}
	}

	if (velX > 0) //right
	{
		if (!foundBlockRight)
		{
		}
		else
		{
			if (!foundBlockUp)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(-m_Speed);
			}
			else if (!foundBlockDown)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(m_Speed);
			}
			else if (!foundBlockLeft)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(-m_Speed);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
			}
		}

	}
	else if (velX < 0)
	{
		if (!foundBlockLeft)
		{
		}
		else
		{
			if (!foundBlockUp)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(-m_Speed);
			}
			else if (!foundBlockDown)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(m_Speed);
			}
			else if (!foundBlockRight)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
			}
		}
	}
	else if (velY > 0)
	{
		if (!foundBlockDown)
		{
		}
		else
		{

			if (!foundBlockLeft)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(-m_Speed);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
			}
			else if (!foundBlockRight)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
			}
			else if (!foundBlockUp)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(-m_Speed);
			}
		}
	}
	else if (velY < 0)
	{
		if (!foundBlockUp)
		{
		}
		else
		{

			if (!foundBlockLeft)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(-m_Speed);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
			}
			else if (!foundBlockRight)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(0);
			}
			else if (!foundBlockDown)
			{
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(0);
				m_pGameObject->GetComponent<TransformComponent>()->SetVelocityY(m_Speed);
			}
		}

	}



}
