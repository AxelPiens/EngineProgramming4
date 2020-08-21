#include "MiniginPCH.h"
#include "YCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void YCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("Y");
}

void YCommand::Dexecute(engine::GameObject* object)
{
}
