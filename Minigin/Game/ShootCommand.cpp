#include "MiniginPCH.h"
#include "ShootCommand.h"
#include "Components.h"
#include "..\Game\ProjectileComponent.h" //change
#include "SceneManager.h"
#include "Scene.h"
#include "ShootComponent.h"
#include "ChangeSpriteComponent.h"
void ShootCommand::Execute(engine::GameObject* object)
{
	if (object->GetComponent<ShootComponent>()->CanShoot() && m_CanShoot)
	{
		auto scene = engine::SceneManager::GetInstance().GetScene("Game");
		auto projectile = std::make_shared<engine::GameObject>("projectile" + std::to_string(m_Number));
		projectile->AddComponent(new TransformComponent(16, 16, 100));
		projectile->GetComponent<TransformComponent>()->Translate(object->GetComponent<TransformComponent>()->GetPosition());
		projectile->GetComponent<TransformComponent>()->Move(5, 5, 0);
		projectile->AddComponent(new SpriteComponent("Digger/bullet.png", 14, 14, 0, 0, 4, 50, true));
		int dir = object->GetComponent<TransformComponent>()->GetDirection();
		projectile->AddComponent(new ProjectileComponent(0.f, 50.0f, 0.0f, dir, false));
		projectile->AddComponent(new ColliderComponent("projectile" + std::to_string(m_Number), true, 0,0));

		scene->AddGameobject(projectile);
		m_CanShoot = false;
		object->GetComponent<ShootComponent>()->SetCanShoot(false);
		object->GetComponent<ChangeSpriteComponent>()->SetLastState(PlayerState::Nothing);
		++m_Number;
	}
}

void ShootCommand::Dexecute(engine::GameObject* object)
{
	UNREFERENCED_PARAMETER(object);
	m_CanShoot = true;
}
