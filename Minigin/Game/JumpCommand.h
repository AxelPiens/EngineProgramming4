#pragma once
#include "Command.h"
#include <SDL_mixer.h>
class TransformComponent;
class engine::GameObject;

class JumpCommand : public engine::Command
{
 public:
        JumpCommand();
        ~JumpCommand() = default;
        virtual void Execute(engine::GameObject* object);
        virtual void Dexecute(engine::GameObject* object);
 private:
         Mix_Chunk* m_pSound;
};

