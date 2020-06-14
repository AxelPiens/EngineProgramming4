#include "MiniginPCH.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <SDL.h>
#include "Game.h"
#pragma comment(lib, "Minigin.lib")
int main(int argc, char* args[])
{
	Game engine;
	engine.Run();
	return 0;
}