#include "MiniginPCH.h"
#include "gCommand.h"
#include "TextComponent.h"
#include "Scene.h"
#include "SceneManager.h"
void GCommand::Execute(engine::GameObject* object)
{
	auto scene = engine::SceneManager::GetInstance().GetScene("HighScore");
	auto objects = scene->GetObjects();
	objects[objects.size()-2]->GetComponent<TextComponent>()->AddToText("G");
}

void GCommand::Dexecute(engine::GameObject* object)
{
}
