#pragma once
#include <BaseComponent.h>
class SwitchingScenesComponent : public BaseComponent
{
public:
	SwitchingScenesComponent(const SwitchingScenesComponent& other) = delete;
	SwitchingScenesComponent(SwitchingScenesComponent&& other) noexcept = delete;
	SwitchingScenesComponent& operator=(const SwitchingScenesComponent& other) = delete;
	SwitchingScenesComponent& operator=(SwitchingScenesComponent&& other) noexcept = delete;
	SwitchingScenesComponent();
	bool GetSwitch() { return m_Switch; };
	void ChangeSwitch(bool hasSwitch) { m_Switch = hasSwitch; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	bool m_Switch = false;
};

