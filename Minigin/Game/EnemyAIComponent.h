#pragma once
#include "BaseComponent.h"
#include "Vector3.h"
class EnemyAIComponent : public BaseComponent
{
public:
	EnemyAIComponent(const EnemyAIComponent& other) = delete;
	EnemyAIComponent(EnemyAIComponent&& other) noexcept = delete;
	EnemyAIComponent& operator=(const EnemyAIComponent& other) = delete;
	EnemyAIComponent& operator=(EnemyAIComponent&& other) noexcept = delete;
	EnemyAIComponent(float speed);
	void SetSpeedDirection(float dir) {	m_Speed *= dir;	};
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	float m_Speed = 0.0f;
	dae::Vector3 m_OldPos;
};

