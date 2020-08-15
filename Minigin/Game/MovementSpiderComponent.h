#pragma once
#include <BaseComponent.h>
class MovementSpiderComponent : public BaseComponent
{
public:
	MovementSpiderComponent(const MovementSpiderComponent& other) = delete;
	MovementSpiderComponent(MovementSpiderComponent&& other) noexcept = delete;
	MovementSpiderComponent& operator=(const MovementSpiderComponent& other) = delete;
	MovementSpiderComponent& operator=(MovementSpiderComponent&& other) noexcept = delete;
	MovementSpiderComponent(float speed);
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	void CheckForBlocksInFront();
	float m_Speed = 0.0f;
};

