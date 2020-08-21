#pragma once
#include <Command.h>
class YCommand : public engine::Command
{
public:
    YCommand() = default;
    ~YCommand() = default;
    virtual void Execute(engine::GameObject* object);
    virtual void Dexecute(engine::GameObject* object);
};

