#include "MiniginPCH.h"
#include "InputManager.h"
#include <SDL.h>
#include "Vector3.h"

bool dae::InputManager::ProcessInput(dae::Vector3& vec)
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

			if (e.key.keysym.sym == SDLK_w) {
				vec.y = -1.2f;
			}
			if (e.key.keysym.sym == SDLK_d) {
				vec.x = 1;
			}
			if (e.key.keysym.sym == SDLK_a) {
				vec.x = -1;
			}
			if (e.key.keysym.sym == SDLK_s) {
				vec.y = 1;
			}
		}
		if (e.type == SDL_KEYUP)
		{

			if (e.key.keysym.sym == SDLK_w) {
				vec.y = 0;
			}
			if (e.key.keysym.sym == SDLK_d) {
				vec.x = 0;
			}
			if (e.key.keysym.sym == SDLK_a) {
				vec.x = 0;
			}
			if (e.key.keysym.sym == SDLK_s) {
				vec.y = 0;
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

