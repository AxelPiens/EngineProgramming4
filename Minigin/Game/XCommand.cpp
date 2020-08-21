#include "MiniginPCH.h"
#include "XCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void XCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("X");
}

void XCommand::Dexecute(engine::GameObject* object)
{
}
