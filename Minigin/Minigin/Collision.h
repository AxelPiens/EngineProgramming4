#pragma once
#include <SDL.h>
#include "ColliderComponent.h"
namespace engine
{
	class Collision
	{
	public:
		static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
		static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);
	};
}

