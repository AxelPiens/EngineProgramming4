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
enum class Scores
{
	Nobbins,//250
	Hobbins,//250
	Emeralds,//25
	Gold //500
};
class StateComponent : public BaseComponent
{
public:
	StateComponent(const StateComponent& other) = delete;
	StateComponent(StateComponent&& other) noexcept = delete;
	StateComponent& operator=(const StateComponent& other) = delete;
	StateComponent& operator=(StateComponent&& other) noexcept = delete;
	StateComponent();
	void ChangePlayerState(PlayerState pState) { m_PlayerState = pState; };
	PlayerState GetPlayerState() { return m_PlayerState; };
	void ChangeScoresState(Scores pState) { m_ScoresState = pState; };
	Scores GetScoresState() { return m_ScoresState; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	PlayerState m_PlayerState;
	Scores m_ScoresState;
};

