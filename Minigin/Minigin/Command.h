#pragma once
namespace dae
{
    class GameObject;
    class Command
    {
    public:
        Command() = default;
        virtual ~Command() = default;
        virtual void Execute(GameObject* object) = 0;
        virtual void Dexecute(GameObject* object) = 0;
    };
}

