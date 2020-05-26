#pragma once
#include "BaseComponent.h"
class TransformComponent;
class RigidbodyComponent : public BaseComponent
{
public:
	RigidbodyComponent(const RigidbodyComponent& other) = delete;
	RigidbodyComponent(RigidbodyComponent&& other) noexcept = delete;
	RigidbodyComponent& operator=(const RigidbodyComponent& other) = delete;
	RigidbodyComponent& operator=(RigidbodyComponent&& other) noexcept = delete;

	RigidbodyComponent(float accelGrav, float maxGrav);
	~RigidbodyComponent() = default;

	void SetOnGround(bool onGround) { m_OnGround = onGround; };
	bool GetOnGround() const { return m_OnGround; };
	void SetIsJumping(bool isJumping) { m_IsJumping = isJumping; };
	bool GetIsJumping() const { return m_IsJumping; };

protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	float m_AccelGrav = 1.0f;
	float m_MaxGrav = 4.0f;


	bool m_OnGround = false;
	bool m_IsJumping = false;
};

