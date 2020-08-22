#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Vector3.h"
#include "GameObject.h"
#include "Components.h"
#include "Command.h"

engine::InputManager::~InputManager()
{
	delete m_AKey;
	m_AKey = nullptr;
	delete m_BKey;
	m_BKey = nullptr;
	delete m_CKey;
	m_CKey = nullptr;
	delete m_DKey;
	m_DKey = nullptr;
	delete m_EKey;
	m_EKey = nullptr;
	delete m_FKey;
	m_FKey = nullptr;
	delete m_GKey;
	m_GKey = nullptr;
	delete m_HKey;
	m_HKey = nullptr;
	delete m_IKey;
	m_IKey = nullptr;
	delete m_JKey;
	m_JKey = nullptr;
	delete m_KKey;
	m_KKey = nullptr;
	delete m_LKey;
	m_LKey = nullptr;
	delete m_MKey;
	m_MKey = nullptr;
	delete m_NKey;
	m_NKey = nullptr;
	delete m_OKey;
	m_OKey = nullptr;
	delete m_PKey;
	m_PKey = nullptr;
	delete m_QKey;
	m_QKey = nullptr;
	delete m_RKey;
	m_RKey = nullptr;
	delete m_SKey;
	m_SKey = nullptr;
	delete m_TKey;
	m_TKey = nullptr;
	delete m_UKey;
	m_UKey = nullptr;
	delete m_VKey;
	m_VKey = nullptr;
	delete m_WKey;
	m_WKey = nullptr;
	delete m_XKey;
	m_XKey = nullptr;
	delete m_YKey;
	m_YKey = nullptr;
	delete m_ZKey;
	m_ZKey = nullptr;
	delete m_SpaceBarKey;
	m_SpaceBarKey = nullptr;
	delete m_EnterKey;
	m_EnterKey = nullptr;
	delete m_ArrowUpKey;
	m_ArrowUpKey = nullptr;
	delete m_ArrowDownKey;
	m_ArrowDownKey = nullptr;
	delete m_ArrowRightKey;
	m_ArrowRightKey = nullptr;
	delete m_ArrowLeftKey;
	m_ArrowLeftKey = nullptr;

	delete m_AButton;
	m_AButton = nullptr;
	delete m_XButton;
	m_XButton = nullptr;
	delete m_BButton;
	m_BButton = nullptr;
	delete m_YButton;
	m_YButton = nullptr;
	delete m_UpButton;
	m_UpButton = nullptr;
	delete m_DownButton;
	m_DownButton = nullptr;
	delete m_RightButton;
	m_RightButton = nullptr;
	delete m_LeftButton;
	m_LeftButton = nullptr;
	delete m_LeftTrigger;
	m_LeftTrigger = nullptr;
	delete m_RightTrigger;
	m_RightTrigger = nullptr;
}

engine::Command* engine::InputManager::ProcessInput(bool& isReleased)
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			m_Quit = true;
			return nullptr;
		}
		if (e.key.keysym.sym == SDLK_ESCAPE) {
			m_Quit = true;
			return nullptr;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_a)
			{
				isReleased = false;
				return m_AKey;
			}
			else if (e.key.keysym.sym == SDLK_b)
			{
				isReleased = false;
				return m_BKey;
			}
			else if (e.key.keysym.sym == SDLK_c)
			{
				isReleased = false;
				return m_CKey;
			}
			else if (e.key.keysym.sym == SDLK_d)
			{
				isReleased = false;
				return m_DKey;
			}
			else if (e.key.keysym.sym == SDLK_e)
			{
				isReleased = false;
				return m_EKey;
			}
			else if (e.key.keysym.sym == SDLK_f)
			{
				isReleased = false;
				return m_FKey;
			}
			else if (e.key.keysym.sym == SDLK_g)
			{
				isReleased = false;
				return m_GKey;
			}
			else if (e.key.keysym.sym == SDLK_h)
			{
				isReleased = false;
				return m_HKey;
			}
			else if (e.key.keysym.sym == SDLK_i)
			{
				isReleased = false;
				return m_IKey;
			}
			else if (e.key.keysym.sym == SDLK_j)
			{
				isReleased = false;
				return m_JKey;
			}
			else if (e.key.keysym.sym == SDLK_k)
			{
				isReleased = false;
				return m_KKey;
			}
			else if (e.key.keysym.sym == SDLK_l)
			{
				isReleased = false;
				return m_LKey;
			}
			else if (e.key.keysym.sym == SDLK_m)
			{
				isReleased = false;
				return m_MKey;
			}
			else if (e.key.keysym.sym == SDLK_n)
			{
				isReleased = false;
				return m_NKey;
			}
			else if (e.key.keysym.sym == SDLK_o)
			{
				isReleased = false;
				return m_OKey;
			}
			else if (e.key.keysym.sym == SDLK_p)
			{
				isReleased = false;
				return m_PKey;
			}
			else if (e.key.keysym.sym == SDLK_q)
			{
				isReleased = false;
				return m_QKey;
			}
			else if (e.key.keysym.sym == SDLK_r)
			{
				isReleased = false;
				return m_RKey;
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				isReleased = false;
				return m_SKey;
			}
			else if (e.key.keysym.sym == SDLK_t)
			{
				isReleased = false;
				return m_TKey;
			}
			else if (e.key.keysym.sym == SDLK_u)
			{
				isReleased = false;
				return m_UKey;
			}
			else if (e.key.keysym.sym == SDLK_v)
			{
				isReleased = false;
				return m_VKey;
			}
			else if (e.key.keysym.sym == SDLK_w)
			{
				isReleased = false;
				return m_WKey;
			}
			else if (e.key.keysym.sym == SDLK_x)
			{
				isReleased = false;
				return m_XKey;
			}
			else if (e.key.keysym.sym == SDLK_y)
			{
				isReleased = false;
				return m_YKey;
			}
			else if (e.key.keysym.sym == SDLK_z)
			{
				isReleased = false;
				return m_ZKey;
			}
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				isReleased = false;
				return m_SpaceBarKey;
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				isReleased = false;
				return m_EnterKey;
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				isReleased = false;
				return m_ArrowUpKey;
			}
			else if (e.key.keysym.sym == SDLK_DOWN)
			{
				isReleased = false;
				return m_ArrowDownKey;
			}
			else if (e.key.keysym.sym == SDLK_RIGHT)
			{
				isReleased = false;
				return m_ArrowRightKey;
			}
			else if (e.key.keysym.sym == SDLK_LEFT)
			{
				isReleased = false;
				return m_ArrowLeftKey;
			}
		}
		if (e.type == SDL_KEYUP)
		{

			if (e.key.keysym.sym == SDLK_a)
			{
				isReleased = true;
				return m_AKey;
			}
			else if (e.key.keysym.sym == SDLK_b)
			{
				isReleased = true;
				return m_BKey;
			}
			else if (e.key.keysym.sym == SDLK_c)
			{
				isReleased = true;
				return m_CKey;
			}
			else if (e.key.keysym.sym == SDLK_d)
			{
				isReleased = true;
				return m_DKey;
			}
			else if (e.key.keysym.sym == SDLK_e)
			{
				isReleased = true;
				return m_EKey;
			}
			else if (e.key.keysym.sym == SDLK_f)
			{
				isReleased = true;
				return m_FKey;
			}
			else if (e.key.keysym.sym == SDLK_g)
			{
				isReleased = true;
				return m_GKey;
			}
			else if (e.key.keysym.sym == SDLK_h)
			{
				isReleased = true;
				return m_HKey;
			}
			else if (e.key.keysym.sym == SDLK_i)
			{
				isReleased = true;
				return m_IKey;
			}
			else if (e.key.keysym.sym == SDLK_j)
			{
				isReleased = true;
				return m_JKey;
			}
			else if (e.key.keysym.sym == SDLK_k)
			{
				isReleased = true;
				return m_KKey;
			}
			else if (e.key.keysym.sym == SDLK_l)
			{
				isReleased = true;
				return m_LKey;
			}
			else if (e.key.keysym.sym == SDLK_m)
			{
				isReleased = true;
				return m_MKey;
			}
			else if (e.key.keysym.sym == SDLK_n)
			{
				isReleased = true;
				return m_NKey;
			}
			else if (e.key.keysym.sym == SDLK_o)
			{
				isReleased = true;
				return m_OKey;
			}
			else if (e.key.keysym.sym == SDLK_p)
			{
				isReleased = true;
				return m_PKey;
			}
			else if (e.key.keysym.sym == SDLK_q)
			{
				isReleased = true;
				return m_QKey;
			}
			else if (e.key.keysym.sym == SDLK_r)
			{
				isReleased = true;
				return m_RKey;
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				isReleased = true;
				return m_SKey;
			}
			else if (e.key.keysym.sym == SDLK_t)
			{
				isReleased = true;
				return m_TKey;
			}
			else if (e.key.keysym.sym == SDLK_u)
			{
				isReleased = true;
				return m_UKey;
			}
			else if (e.key.keysym.sym == SDLK_v)
			{
				isReleased = true;
				return m_VKey;
			}
			else if (e.key.keysym.sym == SDLK_w)
			{
				isReleased = true;
				return m_WKey;
			}
			else if (e.key.keysym.sym == SDLK_x)
			{
				isReleased = true;
				return m_XKey;
			}
			else if (e.key.keysym.sym == SDLK_y)
			{
				isReleased = true;
				return m_YKey;
			}
			else if (e.key.keysym.sym == SDLK_z)
			{
				isReleased = true;
				return m_ZKey;
			}
			else if (e.key.keysym.sym == SDLK_SPACE)
			{
				isReleased = true;
				return m_SpaceBarKey;
			}
			else if (e.key.keysym.sym == SDLK_RETURN)
			{
				isReleased = true;
				return m_EnterKey;
			}
			else if (e.key.keysym.sym == SDLK_UP)
			{
				isReleased = false;
				return m_ArrowUpKey;
			}
			else if (e.key.keysym.sym == SDLK_DOWN)
			{
				isReleased = true;
				return m_ArrowDownKey;
			}
			else if (e.key.keysym.sym == SDLK_RIGHT)
			{
				isReleased = true;
				return m_ArrowRightKey;
			}
			else if (e.key.keysym.sym == SDLK_LEFT)
			{
				isReleased = true;
				return m_ArrowLeftKey;
			}
		}
	}



	if (IsPressed(ControllerButton::ButtonA))
	{
		isReleased = false;
		m_LastPressedButton = m_AButton;
		return m_AButton;
	}
	else if (IsPressed(ControllerButton::ButtonX))
	{
		isReleased = false;
		m_LastPressedButton = m_XButton;
		return m_XButton;
	}
	else if (IsPressed(ControllerButton::ButtonY))
	{
		isReleased = false;
		m_LastPressedButton = m_YButton;
		return m_YButton;
	}
	else if (IsPressed(ControllerButton::ButtonB))
	{
		isReleased = false;
		m_LastPressedButton = m_BButton;
		return m_BButton;
	}
	else if (IsPressed(ControllerButton::ButtonUp))
	{
		isReleased = false;
		m_LastPressedButton = m_UpButton;
		return m_UpButton;
	}
	else if (IsPressed(ControllerButton::ButtonDown))
	{
		isReleased = false;
		m_LastPressedButton = m_DownButton;
		return m_DownButton;
	}
	else if (IsPressed(ControllerButton::ButtonRight))
	{
		isReleased = false;
		m_LastPressedButton = m_RightButton;
		return m_RightButton;
	}
	else if (IsPressed(ControllerButton::ButtonLeft))
	{
		isReleased = false;
		m_LastPressedButton = m_LeftButton;
		return m_LeftButton;
	}
	else if (IsPressed(ControllerButton::RightTrigger))
	{
		isReleased = false;
		m_LastPressedButton = m_RightTrigger;
		return m_RightTrigger;
	}
	else if (IsPressed(ControllerButton::LeftTrigger))
	{
		isReleased = false;
		m_LastPressedButton = m_LeftTrigger;
		return m_LeftTrigger;
	}
	isReleased = true;
	return m_LastPressedButton;
}

bool engine::InputManager::IsPressed(ControllerButton button) const
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
	case ControllerButton::ButtonUp:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP;
	case ControllerButton::ButtonDown:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN;
	case ControllerButton::ButtonRight:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT;
	case ControllerButton::ButtonLeft:
		return m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT;
	case ControllerButton::RightTrigger:
		if (m_CurrentState.Gamepad.bRightTrigger > 100)
			return true;
	case ControllerButton::LeftTrigger:
		if (m_CurrentState.Gamepad.bLeftTrigger > 100)
			return true;

	default: return false;
	}
}

