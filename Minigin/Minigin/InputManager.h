#pragma once
#include <XInput.h>
#pragma comment(lib, "Xinput.lib")
#include "Singleton.h"

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
		void SetAKey(Command* command) {
			if (m_AKey)
			{
				//delete m_AKey;
				m_AKey = nullptr;
			}
			m_AKey = command; };
		void SetBKey(Command* command) { m_BKey = command; };
		void SetCKey(Command* command) { m_CKey = command; };
		void SetDKey(Command* command) { m_DKey = command; };
		void SetEKey(Command* command) { m_EKey = command; };
		void SetFKey(Command* command) { m_FKey = command; };
		void SetGKey(Command* command) { m_GKey = command; };
		void SetHKey(Command* command) { m_HKey = command; };
		void SetIKey(Command* command) { m_IKey = command; };
		void SetJKey(Command* command) { m_JKey = command; };
		void SetKKey(Command* command) { m_KKey = command; };
		void SetLKey(Command* command) { m_LKey = command; };
		void SetMKey(Command* command) { m_MKey = command; };
		void SetNKey(Command* command) { m_NKey = command; };
		void SetOKey(Command* command) { m_OKey = command; };
		void SetPKey(Command* command) { m_PKey = command; };
		void SetQKey(Command* command) { m_QKey = command; };
		void SetRKey(Command* command) { m_RKey = command; };
		void SetSKey(Command* command) { m_SKey = command; };
		void SetTKey(Command* command) { m_TKey = command; };
		void SetUKey(Command* command) { m_UKey = command; };
		void SetVKey(Command* command) { m_VKey = command; };
		void SetWKey(Command* command) { m_WKey = command; };
		void SetXKey(Command* command) { m_XKey = command; };
		void SetYKey(Command* command) { m_YKey = command; };
		void SetZKey(Command* command) { m_ZKey = command; };
		void SetSpaceBarKey(Command* command) { m_SpaceBarKey = command; };
		void SetEnterKey(Command* command) { m_EnterKey = command; };
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

		Command* m_AKey;
		Command* m_BKey;
		Command* m_CKey;
		Command* m_DKey;
		Command* m_EKey;
		Command* m_FKey;
		Command* m_GKey;
		Command* m_HKey;
		Command* m_IKey;
		Command* m_JKey;
		Command* m_KKey;
		Command* m_LKey;
		Command* m_MKey;
		Command* m_NKey;
		Command* m_OKey;
		Command* m_PKey;
		Command* m_QKey;
		Command* m_RKey;
		Command* m_SKey;
		Command* m_TKey;
		Command* m_UKey;
		Command* m_VKey;
		Command* m_WKey;
		Command* m_XKey;
		Command* m_YKey;
		Command* m_ZKey;
		Command* m_SpaceBarKey;
		Command* m_EnterKey;

		Command* m_AButton;
		Command* m_XButton;
		Command* m_BButton;
		Command* m_YButton;

		Command* m_LastPressedButton;
	};
}
