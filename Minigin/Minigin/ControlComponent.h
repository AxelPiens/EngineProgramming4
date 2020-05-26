#pragma once
#include "BaseComponent.h"
class TransformComponent;
class ControlComponent : public BaseComponent
{
public:
	ControlComponent(const ControlComponent& other) = delete;
	ControlComponent(ControlComponent&& other) noexcept = delete;
	ControlComponent& operator=(const ControlComponent& other) = delete;
	ControlComponent& operator=(ControlComponent&& other) noexcept = delete;

	ControlComponent();
	~ControlComponent() = default;
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
};

