#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Vector3.h"
#include "GameObject.h"
#include "Components.h"
#include "Command.h"

engine::InputManager::~InputManager()
{
	delete m_WKey;
	m_WKey = nullptr;
	delete m_SKey;
	m_SKey = nullptr;
	delete m_DKey;
	m_DKey = nullptr;
	delete m_AKey;
	m_AKey = nullptr;
	
	delete m_AButton;
	m_AButton = nullptr;
	delete m_XButton;
	m_XButton = nullptr;
	delete m_BButton;
	m_BButton = nullptr;
	delete m_YButton;
	m_YButton = nullptr;
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
			if (e.key.keysym.sym == SDLK_w)
			{
				isReleased = false;
				return m_WKey;
			}
			else if (e.key.keysym.sym == SDLK_d)
			{
				isReleased = false;
				return m_DKey;
			}
			else if (e.key.keysym.sym == SDLK_a)
			{
				isReleased = false;
				return m_AKey;
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				isReleased = false;
				return m_SKey;
			}
		}
		if (e.type == SDL_KEYUP)
		{

			if (e.key.keysym.sym == SDLK_w)
			{
				isReleased = true;
				return m_WKey;
			}
			else if (e.key.keysym.sym == SDLK_d)
			{
				isReleased = true;
				return m_DKey;
			}
			else if (e.key.keysym.sym == SDLK_a)
			{
				isReleased = true;
				return m_AKey;
			}
			else if (e.key.keysym.sym == SDLK_s)
			{
				isReleased = true;
				return m_SKey;
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
	default: return false;
	}
}

