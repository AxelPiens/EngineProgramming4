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
	m_Collider.x = posX;
	m_Collider.y = posY;
	m_Collider.w = 1;
	m_Collider.h = 1;

	if (!object->GetComponent<LiveComponent>()->HasLostLive())
	{
		for (auto trigger : triggers)

		{
			if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
			{
				int modulo = int(object->GetComponent<TransformComponent>()->GetPosition().x) % 27;
				if (modulo >= -4 && modulo <= 4)
				{
					object->GetComponent<RigidbodyComponent>()->WalkY(0.8f);
					object->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::WalkDown);
				}
				allFailed = false;
			}
		}
		if (allFailed)
		{
			object->GetComponent<RigidbodyComponent>()->WalkY(0.8f);
			object->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::WalkDown);
		}
		m_Collider.x = object->GetComponent<TransformComponent>()->GetPosition().x + 5;
		m_Collider.y = object->GetComponent<TransformComponent>()->GetPosition().y + 30;

		for (auto col : colliders)
		{
			if (engine::Collision::AABB(m_Collider, col->GetCollider()))
			{
				if (col->GetGameObject()->GetName().find("money") != std::string::npos)
				{
					object->GetComponent<TransformComponent>()->SetVelocityY(0.f);
					break;
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
