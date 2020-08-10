#pragma once
#include <BaseComponent.h>
enum class PlayerState
{
	WalkRight,
	WalkLeft,
	WalkUp,
	WalkDown, 
	Shoot,
	Idle,
	Death,
	Nothing
};
class StateComponent : public BaseComponent
{
public:
	StateComponent(const StateComponent& other) = delete;
	StateComponent(StateComponent&& other) noexcept = delete;
	StateComponent& operator=(const StateComponent& other) = delete;
	StateComponent& operator=(StateComponent&& other) noexcept = delete;
	StateComponent();
	void ChangeState(PlayerState pState) { m_pState = pState; };
	PlayerState GetState() { return m_pState; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	PlayerState m_pState;
};

