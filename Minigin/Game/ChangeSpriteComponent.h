#pragma once
#include <BaseComponent.h>
#include "StateComponent.h"
#include "SpriteComponent.h"
class ChangeSpriteComponent : public BaseComponent
{
public:
	ChangeSpriteComponent(const ChangeSpriteComponent& other) = delete;
	ChangeSpriteComponent(ChangeSpriteComponent&& other) noexcept = delete;
	ChangeSpriteComponent& operator=(const ChangeSpriteComponent& other) = delete;
	ChangeSpriteComponent& operator=(ChangeSpriteComponent&& other) noexcept = delete;
	ChangeSpriteComponent();
	void SetLastState(PlayerState state) { m_LastState = state; };
	void SetY(int y) { m_pGameObject->GetComponent<SpriteComponent>()->ChangeYPos(y); };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	PlayerState m_LastState;
};

