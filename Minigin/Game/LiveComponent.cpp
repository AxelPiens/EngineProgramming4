#include "MiniginPCH.h"
#include "LiveComponent.h"
#include "TransformComponent.h"
LiveComponent::LiveComponent(int amountOfLives, float deathTime)
	:m_AmountOfLives{amountOfLives}
	, m_DeathTime{deathTime}
	, m_ElapsedTime{0.0f}
{

}

void LiveComponent::LoseLive()
{
	--m_AmountOfLives;
	m_pGameObject->SetPlayerState(dae::PlayerStates::Death);
}

void LiveComponent::Init()
{
	m_SpawnPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
}

void LiveComponent::Update(float deltaTime)
{
	if (m_pGameObject->GetPlayerState() == dae::PlayerStates::Death)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_DeathTime)
		{
			m_ElapsedTime = 0.0f;
			m_pGameObject->SetPlayerState(dae::PlayerStates::Idle);
			m_pGameObject->GetComponent<TransformComponent>()->Translate(m_SpawnPos);
		}

	}
	if (m_AmountOfLives == 0)
	{
		std::cout << "death\n";
	}
}

void LiveComponent::Render()
{
}
