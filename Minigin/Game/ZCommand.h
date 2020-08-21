#pragma once
#include <Command.h>
class ZCommand : public engine::Command
{
public:
    ZCommand() = default;
    ~ZCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

