#include "MiniginPCH.h"
#include "MovementSpiderComponent.h"
#include "Components.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Collision.h"
#include "ChangeSpriteComponent.h"
#include "TurnHobbinComponent.h"
#include "LiveComponent.h"
#include  "MovingBagComponent.h"
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
	auto players = scene->GetPlayers();


	SDL_Rect m_Collider;
	m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) + 50;
	m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 7;
	m_Collider.w = 1;
	m_Collider.h = 1;

	float velX = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().x;
	float velY = m_pGameObject->GetComponent<TransformComponent>()->GetVelocity().y;
	bool foundBlock = false;
	bool foundBlockRight = false;
	bool foundBlockLeft = false;
	bool foundBlockUp = false;
	bool foundBlockDown = false;

	if (!m_pGameObject->GetComponent<TurnHobbinComponent>()->GetIsTurned())
	{
		for (auto trigger : triggers)
		{
			if (trigger->GetName().find("level") != std::string::npos)
			{
				m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) + 27;
				m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 5;
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_Collider)) // right
				{
					foundBlockRight = true;
				}
				m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x);
				m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 5;
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_Collider)) //left
				{
					foundBlockLeft = true;
				}
				m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) + 5;
				m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y);
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_Collider)) //up
				{
					foundBlockUp = true;
				}
				m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) + 5;
				m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 27;
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_Collider)) //down
				{
					foundBlockDown = true;
				}
			}
			else if (trigger->GetName().find("coins") != std::string::npos)
			{
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(),
					m_pGameObject->GetComponent<ColliderComponent>()->GetCollider()))
				{
					scene->RemoveGameObject(trigger->GetName());
					break;
				}
			}
		}
	}
	else
	{
		for (auto trigger : triggers)
		{
			if (trigger->GetName().find("level") != std::string::npos)
			{
				SDL_Rect m_SmallCollider;
				m_SmallCollider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) + 5;
				m_SmallCollider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 5;
				m_SmallCollider.w = 5;
				m_SmallCollider.h = 5;
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(), m_SmallCollider))
				{
					scene->RemoveGameObject(trigger->GetName());
					break;
				}

			}
			else if (trigger->GetName().find("coins") != std::string::npos)
			{
				if (engine::Collision::AABB(trigger->GetComponent<ColliderComponent>()->GetCollider(),
					m_pGameObject->GetComponent<ColliderComponent>()->GetCollider()))
				{
					scene->RemoveGameObject(trigger->GetName());
					break;
				}
			}
		}

	}

	for (auto collider : colliders)
	{
		m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) + 27;
		m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 5;
		if (engine::Collision::AABB(collider->GetCollider(), m_Collider)) // right
		{
			foundBlockRight = true;
		}
		m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x);
		m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 5;
		if (engine::Collision::AABB(collider->GetCollider(), m_Collider)) //left
		{
			foundBlockLeft = true;
		}
		m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) + 5;
		m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y);
		if (engine::Collision::AABB(collider->GetCollider(), m_Collider)) //up
		{
			foundBlockUp = true;
		}
		m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x) + 5;
		m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 27;
		if (engine::Collision::AABB(collider->GetCollider(), m_Collider)) //down
		{
			foundBlockDown = true;
		}

		SDL_Rect m_SmallCollider;
		m_SmallCollider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x);
		m_SmallCollider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 13;
		m_SmallCollider.w = 27;
		m_SmallCollider.h = 14;
		if (engine::Collision::AABB(collider->GetCollider(), m_SmallCollider))
		{
			if (collider->GetGameObject()->GetName().find("money") != std::string::npos)
			{
				if (collider->GetGameObject()->GetComponent<MovingBagComponent>()->GetIsFalling())
				{
					scene->RemoveGameObject(m_pGameObject->GetName());
					break;
				}
			}
		}
	}

	for (auto player : players)
	{
		SDL_Rect m_SmallCollider;
		m_SmallCollider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x);
		m_SmallCollider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y) + 13;
		m_SmallCollider.w = 27;
		m_SmallCollider.h = 14;
		if (player->GetName().find("player") != std::string::npos)
		{
			if (engine::Collision::AABB(player->GetComponent<ColliderComponent>()->GetCollider(), m_SmallCollider))
			{
				if (player->GetComponent<StateComponent>()->GetPlayerState() != PlayerState::Death)
				{
					player->GetComponent<LiveComponent>()->LoseLive();
					player->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::Death);
					player->GetComponent<TransformComponent>()->SetVelocity(engine::Vector3(0, 0, 0));
					break;
				}
			}
		}
	}


	if (m_pGameObject)
	{
		if (velX > 0) //right
		{
			if (!foundBlockRight)
			{
				if (!m_pGameObject->GetComponent<TurnHobbinComponent>()->GetIsTurned())
				{
					m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetY(27);
				}
				else
					m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetY(27 + 108);

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
				if (!m_pGameObject->GetComponent<TurnHobbinComponent>()->GetIsTurned())
				{
					m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetY(0);
				}
				else
					m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetY(108);

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
				if (!m_pGameObject->GetComponent<TurnHobbinComponent>()->GetIsTurned())
				{
					m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetY(81);
				}
				else
					m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetY(81 + 108);

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
				if (!m_pGameObject->GetComponent<TurnHobbinComponent>()->GetIsTurned())
				{
					m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetY(54);
				}
				else
					m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetY(54 + 108);
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
}
