#pragma once
#include <BaseComponent.h>
#include "Vector3.h"
class LiveComponent : public BaseComponent
{
public:
	LiveComponent(const LiveComponent& other) = delete;
	LiveComponent(LiveComponent&& other) noexcept = delete;
	LiveComponent& operator=(const LiveComponent& other) = delete;
	LiveComponent& operator=(LiveComponent&& other) noexcept = delete;
	LiveComponent(int amountOfLives, float deathTime);
	void LoseLive();
	int GetLives() const { return m_AmountOfLives; };
	void Init();
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	int m_AmountOfLives = 0;
	float m_ElapsedTime = 0.0f;
	float m_DeathTime = 4.0f;
	dae::Vector3 m_SpawnPos;
};

