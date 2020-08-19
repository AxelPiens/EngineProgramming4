#pragma once
#include <BaseComponent.h>
class ShootComponent : public BaseComponent
{
public:
	ShootComponent(const ShootComponent& other) = delete;
	ShootComponent(ShootComponent&& other) noexcept = delete;
	ShootComponent& operator=(const ShootComponent& other) = delete;
	ShootComponent& operator=(ShootComponent&& other) noexcept = delete;
	ShootComponent(float timeToShoot);
	bool CanShoot() { return m_CanShoot; };
	void SetCanShoot(bool canShoot) { m_CanShoot = canShoot; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	float m_ElapsedTime = 0.f;
	float m_TimeToShoot = 0.f;
	bool m_CanShoot = false;

};

