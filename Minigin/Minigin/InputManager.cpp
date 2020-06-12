#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Vector3.h"
#include "GameObject.h"
#include "Components.h"
#include "SceneManager.h"
#include "Scene.h"
#include "..\Game\ProjectileComponent.h" //change

bool dae::InputManager::ProcessInput(GameObject* object)
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.key.keysym.sym == SDLK_q) {
			m_Quit = true;
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (object)
			{
					if (e.key.keysym.sym == SDLK_w)
					{
						object->GetComponent<RigidbodyComponent>()->Jump();
						//vec.y = -1.2f;
					}
					if (e.key.keysym.sym == SDLK_d)
					{
						//vec.x = 1;
						if (object->GetComponent<RigidbodyComponent>()->GetOnGround())
							object->GetComponent<RigidbodyComponent>()->Walk(1);
						else
							object->GetComponent<RigidbodyComponent>()->Walk(0.25f);
					}
					if (e.key.keysym.sym == SDLK_a) 
					{
						if (object->GetComponent<RigidbodyComponent>()->GetOnGround())
							object->GetComponent<RigidbodyComponent>()->Walk(-1);
						else
							object->GetComponent<RigidbodyComponent>()->Walk(-0.25f);
					}
					if (e.key.keysym.sym == SDLK_s)
					{

						if (m_CanShoot)
						{
							auto scene = SceneManager::GetInstance().GetScene("Game");
							auto projectile = std::make_shared<GameObject>("projectile" + std::to_string(m_Number));
							projectile->AddComponent(new TransformComponent(16, 16, 100));
							projectile->GetComponent<TransformComponent>()->Translate(object->GetComponent<TransformComponent>()->GetPosition());
							projectile->AddComponent(new SpriteComponent("sprites1SMALL.png", 32, 32, 16 * 12, 0, 8, 50, true));
							int dir = object->GetComponent<TransformComponent>()->GetDirection();
							projectile->AddComponent(new ProjectileComponent(25, 100, 3, dir));
							projectile->GetComponent<ProjectileComponent>()->SetNumber(m_Number);
							projectile->AddComponent(new ColliderComponent("projectile" + std::to_string(m_Number), true));

							scene->AddGameobject(projectile);
							m_CanShoot = false;
							++m_Number;
						}
					}
			}
		}
		if (e.type == SDL_KEYUP)
		{

			if (e.key.keysym.sym == SDLK_w)
			{
				//vec.y = 0;
			}
			if (e.key.keysym.sym == SDLK_d)
			{
				//vec.x = 0;
				object->GetComponent<RigidbodyComponent>()->Walk(0);
			}
			if (e.key.keysym.sym == SDLK_a)
			{
				//vec.x = 0;
				object->GetComponent<RigidbodyComponent>()->Walk(0);
			}
			if (e.key.keysym.sym == SDLK_s)
			{
				//vec.y = 0;
				m_CanShoot = true;
			}
		}
	}

	return true;
}

bool dae::InputManager::IsPressed(ControllerButton button) const
{
	switch (button)
	{
	case ControllerButton::ButtonA:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_A;
	case ControllerButton::ButtonB:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_B;
	case ControllerButton::ButtonX:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_X;
	case ControllerButton::ButtonY:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_Y;
	default: return false;
	}
}

