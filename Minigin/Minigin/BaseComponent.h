#pragma once
#include "GameObject.h"
class BaseComponent
{
	friend class dae::GameObject;
public:
	BaseComponent(const BaseComponent& other) = delete;
	BaseComponent(BaseComponent&& other) noexcept = delete;
	BaseComponent& operator=(const BaseComponent& other) = delete;
	BaseComponent& operator=(BaseComponent&& other) noexcept = delete;
	BaseComponent();
	virtual ~BaseComponent() = default;
	dae::GameObject* GetGameObject() const { return m_pGameObject; }

	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
protected:
	dae::GameObject* m_pGameObject;

};

