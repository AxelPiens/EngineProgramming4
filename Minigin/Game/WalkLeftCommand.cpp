#include "MiniginPCH.h"
#include "WalkLeftCommand.h"
#include "RigidbodyComponent.h"
#include "StateComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "ColliderComponent.h"
#include "Collision.h"


void WalkLeftCommand::Execute(engine::GameObject* object)
{

	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	float posX = object->GetComponent<TransformComponent>()->GetPosition().x - 20;
	float posY = object->GetComponent<TransformComponent>()->GetPosition().y + 12;
	bool allFailed = true;
	SDL_Rect m_Collider;
	m_Collider.x = posX;
	m_Collider.y = posY;
	m_Collider.w = 1;
	m_Collider.h = 1;
	auto colliders = scene->GetColliders();


	for (auto trigger : triggers)

	{
		if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
		{
			int modulo = int(object->GetComponent<TransformComponent>()->GetPosition().y) % 27;
			if (modulo >= -4 && modulo <= 4)
			{
				object->GetComponent<RigidbodyComponent>()->WalkX(-1);
				object->GetComponent<StateComponent>()->ChangeState(PlayerState::WalkLeft);
			}
			allFailed = false;
		}
	}
	if (allFailed)
	{
		object->GetComponent<RigidbodyComponent>()->WalkX(-1);
		object->GetComponent<StateComponent>()->ChangeState(PlayerState::WalkLeft);
	}

	for (auto col : colliders)
	{
		if (engine::Collision::AABB(m_Collider, col->GetCollider()))
		{
			if (col->GetGameObject()->GetName() == "money")
			{
				col->GetGameObject()->GetComponent<TransformComponent>()->Move(-32, 0, 0);
			}
		}
	}
}

void WalkLeftCommand::Dexecute(engine::GameObject* object)
{
	object->GetComponent<RigidbodyComponent>()->WalkX(0);
	object->GetComponent<StateComponent>()->ChangeState(PlayerState::Idle);
}
