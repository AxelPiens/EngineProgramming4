#pragma once
#include "Command.h"
class engine::GameObject;

	class ShootCommand : public engine::Command
	{
	public:
		ShootCommand() = default;
		~ShootCommand() = default;
		virtual void Execute(engine::GameObject* object);
		virtual void Dexecute(engine::GameObject* object);

	private:
		bool m_CanShoot = true;
		int m_Number = 0;
	};

