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

void WalkRightCommand::Execute(engine::GameObject* object)
{

	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto triggers = scene->GetTriggers();
	auto colliders = scene->GetColliders();
	float posX = object->GetComponent<TransformComponent>()->GetPosition().x+27;
	float posY = object->GetComponent<TransformComponent>()->GetPosition().y+12;
	bool allFailed = true;
	SDL_Rect m_Collider;
	m_Collider.x = posX;
	m_Collider.y = posY;
	m_Collider.w = 1;
	m_Collider.h = 1;


	for (auto trigger : triggers)

	{
		if (engine::Collision::AABB(m_Collider, trigger->GetComponent<ColliderComponent>()->GetCollider()))
		{

			int modulo = int(object->GetComponent<TransformComponent>()->GetPosition().y) % 27;
			if (modulo >= -4 && modulo <= 4)
			{
				object->GetComponent<RigidbodyComponent>()->WalkX(0.8f);
				object->GetComponent<StateComponent>()->ChangeState(PlayerState::WalkRight);
			}
			allFailed = false;
		}
	}
	if (allFailed)
	{
		object->GetComponent<RigidbodyComponent>()->WalkX(0.8f);
		object->GetComponent<StateComponent>()->ChangeState(PlayerState::WalkRight);
	}

	m_Collider.x = object->GetComponent<TransformComponent>()->GetPosition().x + 21;

	for (auto col : colliders)
	{
		if (engine::Collision::AABB(m_Collider, col->GetCollider()))
		{
			if (col->GetGameObject()->GetName() == "money")
			{
				col->GetGameObject()->GetComponent<MovingBagComponent>()->SetIsMoving(true);
				col->GetGameObject()->GetComponent<TransformComponent>()->SetVelocityX(70.f);
			}
		}

	}
}

void WalkRightCommand::Dexecute(engine::GameObject* object)
{
	object->GetComponent<RigidbodyComponent>()->WalkX(0);
	object->GetComponent<StateComponent>()->ChangeState(PlayerState::Idle);
}
