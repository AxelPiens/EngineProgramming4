#include "MiniginPCH.h"
#include "VCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void VCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("V");
}

void VCommand::Dexecute(engine::GameObject* object)
{
}
