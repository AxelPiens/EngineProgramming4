#include "MiniginPCH.h"
#include "ShootCommand.h"
#include "Components.h"
#include "..\Game\ProjectileComponent.h" //change
#include "SceneManager.h"
#include "Scene.h"
void ShootCommand::Execute(engine::GameObject* object)
{
	if (m_CanShoot)
	{
		auto scene = engine::SceneManager::GetInstance().GetScene("Game");
		auto projectile = std::make_shared<engine::GameObject>("projectile" + std::to_string(m_Number));
		projectile->AddComponent(new TransformComponent(16, 16, 100));
		projectile->GetComponent<TransformComponent>()->Translate(object->GetComponent<TransformComponent>()->GetPosition());
		projectile->AddComponent(new SpriteComponent("sprites1SMALL.png", 32, 32, 192, 0, 8, 50, true));
		int dir = object->GetComponent<TransformComponent>()->GetDirection();
		projectile->AddComponent(new ProjectileComponent(15, 100, 3, dir, true));
		projectile->GetComponent<ProjectileComponent>()->SetNumber(m_Number);
		projectile->AddComponent(new ColliderComponent("projectile" + std::to_string(m_Number), true, 0,0));

		scene->AddGameobject(projectile);
		m_CanShoot = false;
		++m_Number;
	}
}

void ShootCommand::Dexecute(engine::GameObject* object)
{
	UNREFERENCED_PARAMETER(object);
	m_CanShoot = true;
}
