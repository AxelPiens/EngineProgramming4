#pragma once
#include "Command.h"
#include <SDL_mixer.h>

 class TransformComponent;
namespace engine
{
    class GameObject;
    class JumpCommand : public Command
    {
    public:
        JumpCommand();
        ~JumpCommand() = default;
        virtual void Execute(GameObject* object);
        virtual void Dexecute(GameObject* object);
    private:
        Mix_Chunk* m_pSound;

    };
}

