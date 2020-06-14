#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "BaseComponent.h"
#include "TextComponent.h"
#include "TransformComponent.h"

engine::GameObject::~GameObject()
{
	for (BaseComponent* pComp : m_pComponents)
	{
		delete pComp;
		pComp = nullptr;
	}
}

void engine::GameObject::AddComponent(BaseComponent *pComp)
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

void engine::GameObject::RemoveComponent(BaseComponent* pComp)
{
	auto it = find(m_pComponents.begin(), m_pComponents.end(), pComp);

	if (it == m_pComponents.end())
	{
		return;
	}

	m_pComponents.erase(it);
	pComp->m_pGameObject = nullptr;

}

void engine::GameObject::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_pComponents.size() != 0)
	{
		for (BaseComponent* pComp : m_pComponents)
		{
			if (m_pComponents.size() != 0)
				pComp->Update(deltaTime);
		}
	}
}

void engine::GameObject::Render() const
{
	for (BaseComponent* pComp : m_pComponents)
	{
		pComp->Render();
	}
}

