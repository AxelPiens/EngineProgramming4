#include "MiniginPCH.h"
#include "JCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void JCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("J");
}

void JCommand::Dexecute(engine::GameObject* object)
{
}
