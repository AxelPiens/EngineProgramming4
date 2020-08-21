#include "MiniginPCH.h"
#include "CCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void CCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("C");
}

void CCommand::Dexecute(engine::GameObject* object)
{
}
