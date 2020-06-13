#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Vector3.h"
#include "GameObject.h"
#include "Components.h"
#include "Command.h"

dae::InputManager::~InputManager()
{
	delete m_WKey;
	m_WKey = nullptr;
	delete m_SKey;
	m_SKey = nullptr;
	delete m_DKey;
	m_DKey = nullptr;
	delete m_AKey;
	m_AKey = nullptr;
}

dae::Command* dae::InputManager::ProcessInput(bool& isReleased)
{
	ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_CurrentState);

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return nullptr;
		}
		if (e.key.keysym.sym == SDLK_q) {
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
			if (e.key.keysym.sym == SDLK_d)
			{
				isReleased = false;
				return m_DKey;
			}
			if (e.key.keysym.sym == SDLK_a)
			{
				isReleased = false;
				return m_AKey;
			}
			if (e.key.keysym.sym == SDLK_s)
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
			if (e.key.keysym.sym == SDLK_d)
			{
				isReleased = true;
				return m_DKey;
			}
			if (e.key.keysym.sym == SDLK_a)
			{
				isReleased = true;
				return m_AKey;
			}
			if (e.key.keysym.sym == SDLK_s)
			{
				isReleased = true;
				return m_SKey;
			}
		}
	}

	return nullptr;
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

