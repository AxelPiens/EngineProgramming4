#pragma once
#include <BaseComponent.h>
class WinComponent : public BaseComponent
{
public:
	WinComponent(const WinComponent& other) = delete;
	WinComponent(WinComponent&& other) noexcept = delete;
	WinComponent& operator=(const WinComponent& other) = delete;
	WinComponent& operator=(WinComponent&& other) noexcept = delete;
	WinComponent(int amountOfEmeralds);
	void RemoveEmerald() { --m_AmountOfEmeralds; };
	int GetEmeralds() { return m_AmountOfEmeralds; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	int m_AmountOfEmeralds;

};

