#pragma once
#include <XInput.h>
#include "Singleton.h"

namespace dae
{
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
		bool ProcessInput(dae::Vector3& vec);
		bool IsPressed(ControllerButton button) const;
		bool IsQuitting() const { return m_Quit; };
	private:
		XINPUT_STATE m_CurrentState{};

		bool m_Quit = false;
	};

}
