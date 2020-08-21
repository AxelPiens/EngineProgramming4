#include "MiniginPCH.h"
#include "DCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void DCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("D");
}

void DCommand::Dexecute(engine::GameObject* object)
{
}
