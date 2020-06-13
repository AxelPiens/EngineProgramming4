#pragma once
#include <BaseComponent.h>
class LiveComponent : public BaseComponent
{
public:
	LiveComponent(const LiveComponent& other) = delete;
	LiveComponent(LiveComponent&& other) noexcept = delete;
	LiveComponent& operator=(const LiveComponent& other) = delete;
	LiveComponent& operator=(LiveComponent&& other) noexcept = delete;
	LiveComponent(int amountOfLives);
	void LoseLive();
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	int m_AmountOfLives = 0;
};

