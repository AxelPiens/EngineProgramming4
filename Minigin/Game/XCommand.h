#pragma once
#include <Command.h>
class XCommand : public engine::Command
{
public:
    XCommand() = default;
    ~XCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

