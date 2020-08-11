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
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	bool m_IsMoving = false;
	float m_OldPosY;
	void CheckForBlock();
	void SpawnGold();
};

