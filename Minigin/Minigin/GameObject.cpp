#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

dae::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
}

void dae::GameObject::AddComponent(BaseComponent * pComp)
{
	//check if already in gameobject
	for (auto* component : m_pComponents)
	{
		if (component == pComp)
		{
			return;
		}
	}
	m_pComponents.push_back(pComp);
	pComp->m_pGameObject = this;
}

void dae::GameObject::RemoveComponent(BaseComponent* pComp)
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (it == m_pComponents.end())
	{
		return;
	}

	m_pComponents.erase(it);
	pComp->m_pGameObject = nullptr;

}

void dae::GameObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	for(BaseComponent* pComp : m_pComponents)
	{
		pComp->Update(deltaTime);
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}
}

