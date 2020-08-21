#pragma once
#include <Command.h>
class ICommand : public engine::Command
{
public:
    ICommand() = default;
    ~ICommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

