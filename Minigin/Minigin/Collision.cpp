#include "MiniginPCH.h"
#include "Collision.h"

//recB is platforms
//recA is player

bool Collision::AABB(const SDL_Rect& recA, const SDL_Rect& recB)
{
	//left check of platform
	if (recA.x + recA.w >= recB.x &&
		recB.x + recB.w >= recA.x &&
		recA.y <= recB.y + recB.h &&
		recA.y + recA.h >= recB.y)
	{
		return true;
	}
	return false;
}

bool Collision::AABB(const ColliderComponent& colA, const ColliderComponent& colB)
{

	if (AABB(colA.GetCollider(), colB.GetCollider()))
	{
		return true;
	}
	return false;
}



