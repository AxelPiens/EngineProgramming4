#include "MiniginPCH.h"
#include "WalkRightCommand.h"
#include "RigidbodyComponent.h"
#include "StateComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ColliderComponent.h"
#include "Collision.h"
#include "MovingBagComponent.h"
#include "LiveComponent.h"
void WalkRightCommand::Execute(engine::GameObject* object)
{

	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	auto colliders = scene->GetColliders();
	float posX = object->GetComponent<TransformComponent>()->GetPosition().x+27;
	float posY = object->GetComponent<TransformComponent>()->GetPosition().y+12;
	bool allFailed = true;
	SDL_Rect m_Collider;
	m_Collider.x = static_cast<int>(posX);
	m_Collider.y = static_cast<int>(posY);
	m_Collider.w = 1;
	m_Collider.h = 1;

	if (object->GetComponent<TransformComponent>()->GetVelocity().y == 0.0f)
	{
		if (!object->GetComponent<LiveComponent>()->HasLostLive())
		{
			for (auto trigger : triggers)

			{
				if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
				{

					int modulo = int(object->GetComponent<TransformComponent>()->GetPosition().y) % 27;
					if (modulo >= -4 && modulo <= 4)
					{
						object->GetComponent<RigidbodyComponent>()->WalkX(0.5f);
						object->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::WalkRight);
					}
					allFailed = false;
				}
			}
			if (allFailed)
			{
				object->GetComponent<RigidbodyComponent>()->WalkX(0.5f);
				object->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::WalkRight);
			}

			m_Collider.x = static_cast<int>(object->GetComponent<TransformComponent>()->GetPosition().x) + 21;

			for (auto col : colliders)
			{
				SDL_Rect m_SmallColl;
				m_SmallColl.x = static_cast<int>(object->GetComponent<TransformComponent>()->GetPosition().x) + 5;
				m_SmallColl.y = static_cast<int>(object->GetComponent<TransformComponent>()->GetPosition().y) + 5;
				m_SmallColl.w = 16;
				m_SmallColl.h = 17;
				if (engine::Collision::AABB(m_SmallColl, col->GetCollider()))
				{
					if (col->GetGameObject()->GetName().find("money") != std::string::npos)
					{
						col->GetGameObject()->GetComponent<MovingBagComponent>()->SetIsMoving(true);
						col->GetGameObject()->GetComponent<TransformComponent>()->SetVelocityX(70.f);
					}
					if (col->GetGameObject()->GetName().find("level") != std::string::npos)
					{
						object->GetComponent<TransformComponent>()->SetVelocityX(0.f);
						object->GetComponent<TransformComponent>()->Translate(static_cast<float>(col->GetCollider().x) - 21, object->GetComponent<TransformComponent>()->GetPosition().y, 0);
						break;
					}
				}
			}
		}
	}
}

void WalkRightCommand::Dexecute(engine::GameObject* object)
{
	if (!object->GetComponent<LiveComponent>()->HasLostLive())
	{
		object->GetComponent<RigidbodyComponent>()->WalkX(0);
		object->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::Idle);
	}
}
