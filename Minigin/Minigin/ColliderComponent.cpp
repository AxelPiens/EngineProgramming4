#include "MiniginPCH.h"
#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
ColliderComponent::ColliderComponent(std::string tag)
	:m_Tag{tag},
	m_Collider{0}
{
}

ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	m_Collider.x = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().x);
	m_Collider.y = static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetPosition().y);

	m_Collider.w = m_pGameObject->GetComponent<TransformComponent>()->GetWidth() * 
		static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetScale().x);

	m_Collider.h = m_pGameObject->GetComponent<TransformComponent>()->GetHeight() *
		static_cast<int>(m_pGameObject->GetComponent<TransformComponent>()->GetScale().y);
}

void ColliderComponent::Render()
{
}
