#pragma once
#include "Command.h"
namespace dae
{
	class GameObject;

	class ShootCommand : public Command
	{
	public:
		ShootCommand() = default;
		~ShootCommand() = default;
		virtual void Execute(GameObject* object);
		virtual void Dexecute(GameObject* object);

	private:
		bool m_CanShoot = true;
		int m_Number = 0;
	};
}

