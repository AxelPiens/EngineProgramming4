#pragma once
#include <BaseComponent.h>
#include "StateComponent.h"
class ChangeSpriteComponent : public BaseComponent
{
public:
	ChangeSpriteComponent(const ChangeSpriteComponent& other) = delete;
	ChangeSpriteComponent(ChangeSpriteComponent&& other) noexcept = delete;
	ChangeSpriteComponent& operator=(const ChangeSpriteComponent& other) = delete;
	ChangeSpriteComponent& operator=(ChangeSpriteComponent&& other) noexcept = delete;
	ChangeSpriteComponent();
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	PlayerState m_LastState;
};

