#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"

ColliderComponent::ColliderComponent(std::string tag, bool isTrigger, int changeX, int changeY)
	:m_Tag{tag},
	m_Collider{0},
	m_IsTrigger{isTrigger}
	, m_ChangeX{changeX}
	, m_ChangeY{changeY}
{
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Update(float deltaTime)
{
	m_SizeX = m_pGameObject->GetComponent<TransformComponent>()->GetWidth();
	m_SizeY = m_pGameObject->GetComponent<TransformComponent>()->GetHeight();
	UNREFERENCED_PARAMETER(deltaTime);
		m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x + m_ChangeX);
		m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y + m_ChangeY);

		m_Collider.w = m_SizeX *
			static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetScale().x);

		m_Collider.h = m_SizeY *
			static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetScale().y);
}

void ColliderComponent::Render()
{
}
