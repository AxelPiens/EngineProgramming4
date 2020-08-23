#include "MiniginPCH.h"
#include "WalkDownCommand.h"
#include "RigidbodyComponent.h"
#include "StateComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "LiveComponent.h"


void WalkDownCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	auto colliders = scene->GetColliders();
	float posX = object->GetComponent<TransformComponent>()->GetPosition().x + 10;
	float posY = object->GetComponent<TransformComponent>()->GetPosition().y + 32;
	bool allFailed = true;
	SDL_Rect m_Collider;
	m_Collider.x = static_cast<int>(posX);
	m_Collider.y = static_cast<int>(posY);
	m_Collider.w = 1;
	m_Collider.h = 1;

	if (object->GetComponent<TransformComponent>()->GetVelocity().x == 0.0f)
	{
		if (!object->GetComponent<LiveComponent>()->HasLostLive())
		{
			for (auto trigger : triggers)

			{
				if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
				{
					int modulo = int(object->GetComponent<TransformComponent>()->GetPosition().x) % 27;
					if (modulo >= -4 && modulo <= 4)
					{
						object->GetComponent<RigidbodyComponent>()->WalkY(0.5f);
						object->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::WalkDown);
					}
					allFailed = false;
				}
			}
			if (allFailed)
			{
				object->GetComponent<RigidbodyComponent>()->WalkY(0.5f);
				object->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::WalkDown);
			}
			m_Collider.x = static_cast<int>(object->GetComponent<TransformComponent>()->GetPosition().x) + 5;
			m_Collider.y = static_cast<int>(object->GetComponent<TransformComponent>()->GetPosition().y) + 30;

			for (auto col : colliders)
			{
				SDL_Rect m_SmallColl;
				m_SmallColl.x = static_cast<int>(object->GetComponent<TransformComponent>()->GetPosition().x) + 5;
				m_SmallColl.y = static_cast<int>(object->GetComponent<TransformComponent>()->GetPosition().y) +5;
				m_SmallColl.w = 11;
				m_SmallColl.h = 22;
				if (engine::Collision::AABB(m_SmallColl, col->GetCollider()))
				{
					if (col->GetGameObject()->GetName().find("money") != std::string::npos)
					{
						object->GetComponent<TransformComponent>()->SetVelocityY(0.f);
						break;
					}
					if (col->GetGameObject()->GetName().find("level") != std::string::npos)
					{
						object->GetComponent<TransformComponent>()->SetVelocityY(0.f);
						object->GetComponent<TransformComponent>()->Translate(object->GetComponent<TransformComponent>()->GetPosition().x, static_cast<float>(col->GetCollider().y)-27, 0);
						break;
					}
				}
			}
		}
	}
}

void WalkDownCommand::Dexecute(engine::GameObject* object)
{
	if (!object->GetComponent<LiveComponent>()->HasLostLive())
	{
		object->GetComponent<RigidbodyComponent>()->WalkY(0);
		object->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::Idle);
	}
}
