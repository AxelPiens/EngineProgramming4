#pragma once
#include <XInput.h>
#pragma comment(lib, "Xinput.lib")
#include "Singleton.h"
#include "JumpCommand.h"
#include "ShootCommand.h"
#include "WalkRightCommand.h"
#include "WalkLeftCommand.h"
namespace engine
{
	class Command;
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
		~InputManager();
		Command* ProcessInput(bool& isReleased);
		
		bool IsPressed(ControllerButton button) const;
		bool IsQuitting() const { return m_Quit; };
		void SetKeyBoardCommands(Command* aKey, Command* dKey, Command* wKey, Command* sKey)
		{
			m_AKey = aKey;
			m_DKey = dKey;
			m_WKey = wKey;
			m_SKey = sKey;
		}

		void SetControllerCommands(Command* aButton, Command* xButton, Command* yButton, Command* bButton)
		{
			m_AButton = aButton;
			m_XButton = xButton;
			m_BButton = bButton;
			m_YButton = yButton;
		}
	private:
		XINPUT_STATE m_CurrentState{};

		bool m_Quit = false;

		Command* m_WKey;
		Command* m_SKey;
		Command* m_DKey;
		Command* m_AKey;

		Command* m_AButton;
		Command* m_XButton;
		Command* m_BButton;
		Command* m_YButton;

		Command* m_LastPressedButton;
	};
}
