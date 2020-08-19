#pragma once
#include <BaseComponent.h>
class TurnHobbinComponent : public BaseComponent
{
public:
	TurnHobbinComponent(const TurnHobbinComponent& other) = delete;
	TurnHobbinComponent(TurnHobbinComponent&& other) noexcept = delete;
	TurnHobbinComponent& operator=(const TurnHobbinComponent& other) = delete;
	TurnHobbinComponent& operator=(TurnHobbinComponent&& other) noexcept = delete;
	TurnHobbinComponent(float timeToTurn, float timeTurned);
	bool GetIsTurned() { return m_IsTurned; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	float m_ElapsedTimeToTurn = 0.0f;
	float m_TimeToTurn = 0.0f;
	float m_TimeTurned = 0.0f;
	float m_ElapsedTimeTurned = 0.0f;
	bool m_IsTurned = false;
};

