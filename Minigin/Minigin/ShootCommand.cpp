#include "MiniginPCH.h"
#include "ShootCommand.h"
#include "Components.h"
#include "..\Game\ProjectileComponent.h" //change
#include "SceneManager.h"
#include "Scene.h"
void dae::ShootCommand::Execute(GameObject* object)
{
	if (m_CanShoot)
	{
		auto scene = SceneManager::GetInstance().GetScene("Game");
		auto projectile = std::make_shared<GameObject>("projectile" + std::to_string(m_Number), dae::PlayerStates::Nothing, dae::EnemyStates::Nothing, dae::EnemyType::Nothing);
		projectile->AddComponent(new TransformComponent(16, 16, 100));
		projectile->GetComponent<TransformComponent>()->Translate(object->GetComponent<TransformComponent>()->GetPosition());
		projectile->AddComponent(new SpriteComponent("sprites1SMALL.png", 32, 32, 192, 0, 8, 50, true));
		int dir = object->GetComponent<TransformComponent>()->GetDirection();
		projectile->AddComponent(new ProjectileComponent(25, 100, 3, dir));
		projectile->GetComponent<ProjectileComponent>()->SetNumber(m_Number);
		projectile->AddComponent(new ColliderComponent("projectile" + std::to_string(m_Number), true));

		scene->AddGameobject(projectile);
		m_CanShoot = false;
		++m_Number;
		if(dir>0)
			object->SetPlayerState(dae::PlayerStates::ShootRight);
		else 
			object->SetPlayerState(dae::PlayerStates::ShootLeft);
	}
}

void dae::ShootCommand::Dexecute(GameObject* object)
{
	UNREFERENCED_PARAMETER(object);
	object->SetPlayerState(dae::PlayerStates::Idle);//change
	m_CanShoot = true;
}
