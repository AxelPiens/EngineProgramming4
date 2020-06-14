#include "MiniginPCH.h"
#include "ShootCommand.h"
#include "Components.h"
#include "..\Game\ProjectileComponent.h" //change
#include "SceneManager.h"
#include "Scene.h"
void engine::ShootCommand::Execute(GameObject* object)
{
	if (object->GetPlayerState() != engine::PlayerStates::Death)
	{
		if (m_CanShoot)
		{
			auto scene = SceneManager::GetInstance().GetScene("Game");
			auto projectile = std::make_shared<GameObject>("projectile" + std::to_string(m_Number), engine::PlayerStates::Nothing,
				engine::EnemyStates::Nothing, engine::EnemyType::Nothing, engine::FoodType::Nothing);
			projectile->AddComponent(new TransformComponent(16, 16, 100));
			projectile->GetComponent<TransformComponent>()->Translate(object->GetComponent<TransformComponent>()->GetPosition());
			projectile->AddComponent(new SpriteComponent("sprites1SMALL.png", 32, 32, 192, 0, 8, 50, true));
			int dir = object->GetComponent<TransformComponent>()->GetDirection();
			projectile->AddComponent(new ProjectileComponent(15, 100, 3, dir, true));
			projectile->GetComponent<ProjectileComponent>()->SetNumber(m_Number);
			projectile->AddComponent(new ColliderComponent("projectile" + std::to_string(m_Number), true));

			scene->AddGameobject(projectile);
			m_CanShoot = false;
			++m_Number;
			if (dir > 0)
				object->SetPlayerState(engine::PlayerStates::ShootRight);
			else
				object->SetPlayerState(engine::PlayerStates::ShootLeft);
		}
	}
}

void engine::ShootCommand::Dexecute(GameObject* object)
{
	if (object->GetPlayerState() != engine::PlayerStates::Death)
	{
		object->SetPlayerState(engine::PlayerStates::Idle);//change
		m_CanShoot = true;
	}
}
