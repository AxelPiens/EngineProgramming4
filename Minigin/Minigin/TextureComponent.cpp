#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

TextureComponent::TextureComponent(const std::string& fileName)
{
	m_Texture = engine::ResourceManager::GetInstance().LoadTexture(fileName);
}

void TextureComponent::SetTexture(const std::string& filename)
{
	m_Texture = engine::ResourceManager::GetInstance().LoadTexture(filename);
}


void TextureComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
}

void TextureComponent::Render()
{
	engine::Vector3 pos = GetGameObject()->GetComponent<TransformComponent>()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}
