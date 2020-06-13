#pragma once
#include <BaseComponent.h>
class TrappedBubbleComponent : public BaseComponent
{
public:
	TrappedBubbleComponent(const TrappedBubbleComponent& other) = delete;
	TrappedBubbleComponent(TrappedBubbleComponent&& other) noexcept = delete;
	TrappedBubbleComponent& operator=(const TrappedBubbleComponent& other) = delete;
	TrappedBubbleComponent& operator=(TrappedBubbleComponent&& other) noexcept = delete;
	TrappedBubbleComponent(float lifeTime, int bubbleNumber);
	int GetNumber() { return m_Number; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	float m_ElapsedTime = 0.0f;
	float m_LifeTime = 0.0f;
	int m_Number = 0;
};

