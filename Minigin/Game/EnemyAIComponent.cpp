#include "MiniginPCH.h"
#include "EnemyAIComponent.h"
#include "SceneManager.h"
#include "GameObject.h"
#include "Components.h"
#include "ProjectileComponent.h"
#include "Scene.h"
EnemyAIComponent::EnemyAIComponent(float speed, int number)
	:m_Speed{speed},
	m_OldPos{0,0,0},
	m_Number{number},
	m_AbleToShoot{true}
{
}

void EnemyAIComponent::Update(float deltaTime)
{
	if(m_pGameObject->GetComponent<RigidbodyComponent>()->GetOnGround())
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed);
	else
		m_pGameObject->GetComponent<TransformComponent>()->SetVelocityX(m_Speed/10);

	if (m_pGameObject->GetEnemyType() == engine::EnemyType::Mighta)
	{
		if (m_AbleToShoot)
			Shoot();
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_AbleToShootTime)
		{
			m_ElapsedTime = 0.0f;
			m_AbleToShoot = true;
		}
	}

}

void EnemyAIComponent::Render()
{
}

void EnemyAIComponent::Shoot()
{
	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto projectile = std::make_shared<engine::GameObject>("boulder" + std::to_string(m_Number), engine::PlayerStates::Nothing, 
		engine::EnemyStates::Nothing, engine::EnemyType::Nothing, engine::FoodType::Nothing);
	projectile->AddComponent(new TransformComponent(16, 16, 100));
	projectile->GetComponent<TransformComponent>()->Translate(m_pGameObject->GetComponent<TransformComponent>()->GetPosition());
	projectile->AddComponent(new SpriteComponent("spritesSmall.png", 32, 32, 512, 0, 8, 150, true));
	int dir = m_pGameObject->GetComponent<TransformComponent>()->GetDirection();
	projectile->AddComponent(new ProjectileComponent(20, 150, 3, dir, false));
	projectile->GetComponent<ProjectileComponent>()->SetNumber(m_Number);
	projectile->AddComponent(new ColliderComponent("boulder" + std::to_string(m_Number), true));

	scene->AddGameobject(projectile);
	m_AbleToShoot = false;

}
