#pragma once
#include <XInput.h>
#pragma comment(lib, "Xinput.lib")
#include "Singleton.h"

namespace dae
{
	class GameObject;
	struct Vector3;
	enum class ControllerButton
	{
		ButtonA,
		ButtonB,
		ButtonX,
		ButtonY
	};

	class InputManager final : public Singleton<InputManager>
	{
	public:
		bool ProcessInput(GameObject* object);
		bool IsPressed(ControllerButton button) const;
		bool IsQuitting() const { return m_Quit; };
	private:
		XINPUT_STATE m_CurrentState{};

		bool m_Quit = false;
		bool m_CanShoot = true;//change
		int m_Number = 0;//change
	};

}
