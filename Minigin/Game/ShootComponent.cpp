#include "MiniginPCH.h"
#include "ShootComponent.h"
#include "ChangeSpriteComponent.h"

ShootComponent::ShootComponent(float timeToShoot)
	: m_TimeToShoot{timeToShoot}
{
}

void ShootComponent::Update(float deltaTime)
{
	//after shot
	if (!m_CanShoot)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_TimeToShoot)
		{
			std::cout << "CAN SHOOT\n";
			m_pGameObject->GetComponent<ChangeSpriteComponent>()->SetLastState(PlayerState::Nothing);
			m_CanShoot = true;
			m_ElapsedTime = 0;
		}
	}

}

void ShootComponent::Render()
{
}
