#include "MiniginPCH.h"
#include "LCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void LCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("L");
}

void LCommand::Dexecute(engine::GameObject* object)
{
}
