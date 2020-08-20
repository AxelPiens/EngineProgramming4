#include "MiniginPCH.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <SDL.h>
#include "Game.h"
#include "Digger.h"
#include "HighScoreScene.h"
#pragma comment(lib, "Minigin.lib")
int main(int argc, char* args[])
{

	//Digger engine;
	HighScoreScene engine{ true };
	engine.Run();

	return 0;
}