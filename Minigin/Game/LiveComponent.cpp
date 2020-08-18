#include "MiniginPCH.h"
#include "LiveComponent.h"
#include "TransformComponent.h"
#include "StateComponent.h"
LiveComponent::LiveComponent(int amountOfLives, float deathTime)
	:m_AmountOfLives{amountOfLives}
	, m_DeathTime{deathTime}
	, m_ElapsedTime{0.0f}
{

}

void LiveComponent::LoseLive()
{
	--m_AmountOfLives;
	m_HasLostLive = true;
}

void LiveComponent::Init()
{
	m_SpawnPos = m_pGameObject->GetComponent<TransformComponent>()->GetPosition();
}

void LiveComponent::Update(float deltaTime)
{
	if (m_HasLostLive)
	{
		m_ElapsedTime += deltaTime;
		if (m_ElapsedTime > m_DeathTime)
		{
			std::cout << "RESPAWN\n";
			m_ElapsedTime = 0.0f;
			m_pGameObject->GetComponent<TransformComponent>()->Translate(m_SpawnPos);
			m_pGameObject->GetComponent<StateComponent>()->ChangePlayerState(PlayerState::Idle);
			m_HasLostLive = false;

		}
	}
	if (m_AmountOfLives == 0)
		m_IsDeath = true;
}

void LiveComponent::Render()
{
}
