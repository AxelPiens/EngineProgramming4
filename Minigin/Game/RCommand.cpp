#include "MiniginPCH.h"
#include "RCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void RCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("R");
}

void RCommand::Dexecute(engine::GameObject* object)
{
}
