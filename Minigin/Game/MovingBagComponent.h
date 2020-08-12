#pragma once
#include <BaseComponent.h>
class MovingBagComponent : public BaseComponent
{
public:
	MovingBagComponent(const MovingBagComponent& other) = delete;
	MovingBagComponent(MovingBagComponent&& other) noexcept = delete;
	MovingBagComponent& operator=(const MovingBagComponent& other) = delete;
	MovingBagComponent& operator=(MovingBagComponent&& other) noexcept = delete;
	MovingBagComponent();
	void SetIsMoving(bool isMoving) { m_IsMoving = isMoving; };
	bool GetIsFalling() { return m_IsFalling; };
	void SetOldPosY(float oldPosY) { m_OldPosY = oldPosY; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	bool m_IsMoving = false;
	bool m_IsFalling = true;
	bool m_CanFall = false;
	float m_TimeToFall = 2.0f;
	float m_ElapsedTime = 0.0f;
	float m_OldPosY;
	void CheckForBlock();
	void SpawnGold();
};

