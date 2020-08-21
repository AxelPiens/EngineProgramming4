#include "MiniginPCH.h"
#include "PCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void PCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("P");
}

void PCommand::Dexecute(engine::GameObject* object)
{
}
