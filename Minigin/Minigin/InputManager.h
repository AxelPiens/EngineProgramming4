#pragma once
#include <XInput.h>
#pragma comment(lib, "Xinput.lib")
#include "Singleton.h"
#include "JumpCommand.h"
#include "ShootCommand.h"
#include "WalkRightCommand.h"
#include "WalkLeftCommand.h"
namespace dae
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
	private:
		XINPUT_STATE m_CurrentState{};

		bool m_Quit = false;

		Command* m_WKey;//change to button x or something
		Command* m_SKey;
		Command* m_DKey;
		Command* m_AKey;
	};
}
