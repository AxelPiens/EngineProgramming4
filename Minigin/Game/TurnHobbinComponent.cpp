#include "MiniginPCH.h"
#include "TurnHobbinComponent.h"
#include "StateComponent.h"
TurnHobbinComponent::TurnHobbinComponent(float timeToTurn, float timeTurned)
	: m_TimeToTurn{timeToTurn},
	m_TimeTurned{timeTurned}
{
}

void TurnHobbinComponent::Update(float deltaTime)
{
	m_ElapsedTimeToTurn += deltaTime;
	if (m_ElapsedTimeToTurn > m_TimeToTurn)
	{
		m_pGameObject->GetComponent<StateComponent>()->ChangeScoresState(Scores::Hobbins);
		m_IsTurned = true;
		m_ElapsedTimeTurned += deltaTime;
		if (m_ElapsedTimeTurned > m_TimeTurned)
		{
			m_IsTurned = false;
			m_ElapsedTimeToTurn = 0.0f;
			m_ElapsedTimeTurned = 0.0f;
			m_pGameObject->GetComponent<StateComponent>()->ChangeScoresState(Scores::Nobbins);

		}
	}
}

void TurnHobbinComponent::Render()
{
}
