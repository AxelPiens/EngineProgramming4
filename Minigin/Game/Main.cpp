#include "MiniginPCH.h"
#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include <SDL.h>
#include "Minigin.h"
#pragma comment(lib, "Minigin.lib")
int main(int argc, char* args[])
{
	std::cout << "RUN\n";
	dae::Minigin engine;
	std::cout << "RUN\n";
	engine.Run();
	return 0;
}