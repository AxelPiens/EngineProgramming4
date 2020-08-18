#pragma once
#include "BaseComponent.h"
class ProjectileComponent : public BaseComponent
{
public:
	ProjectileComponent(const ProjectileComponent& other) = delete;
	ProjectileComponent(ProjectileComponent&& other) noexcept = delete;
	ProjectileComponent& operator=(const ProjectileComponent& other) = delete;
	ProjectileComponent& operator=(ProjectileComponent&& other) noexcept = delete;
	ProjectileComponent(float range, float speed, float liveTime, int direction, bool goingUp);
	void SetNumber(int number) { m_Number = number; };
	int GetNumber() { return m_Number; };

protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	float m_Range;
	float m_Speed;
	float m_DistanceTraveled;
	float m_ElapsedTime;
	float m_DeathTime;
	int m_Number;
	int m_Direction;
	bool m_IsGoingUp;
	void CheckForBlock();
};

