#include "MiniginPCH.h"
#include "ScoreComponent.h"
#include "StateComponent.h"
#include "SceneManager.h"
#include "Scene.h"
#include "TextComponent.h"

ScoreComponent::ScoreComponent()
{
}

void ScoreComponent::AddScore(std::shared_ptr<engine::GameObject> pGameObject)
{
	Scores scoreState = pGameObject->GetComponent<StateComponent>()->GetScoresState();
	if (scoreState == Scores::Nobbins)
	{
		m_TotalScore += 250;
		m_EmeraldsInARow = 0;
	}
	else if(scoreState == Scores::Hobbins)
	{
		m_TotalScore += 250;
		m_EmeraldsInARow = 0;
	}
	else if (scoreState == Scores::Emeralds)
	{
		m_TotalScore += 25;
		++m_EmeraldsInARow;
	}
	else if (scoreState == Scores::Gold)
	{
		m_TotalScore += 500;
		m_EmeraldsInARow = 0;
	}
	if (m_EmeraldsInARow == 8)
	{
		m_TotalScore += 250;
		m_EmeraldsInARow = 0;
	}

	auto scene = engine::SceneManager::GetInstance().GetScene("Game");
	auto texts = scene->GetTexts();
	texts[0]->GetComponent<TextComponent>()->SetText(std::to_string(m_TotalScore));
}

void ScoreComponent::Update(float deltaTime)
{
}

void ScoreComponent::Render()
{
}
