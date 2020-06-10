#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <SDL.h>
SpriteComponent::SpriteComponent(const std::string path, int width, int height, int bottom, int left, int nrFrames, int delay, bool animated)
	: m_Width{width}
	, m_Height{height}
	, m_Transform{nullptr}
	, m_SrcRect{0}
	, m_DestRect{0}
	, m_Frames{nrFrames}
	, m_Delay{delay}
	, m_IsAnimated{animated}
{
	if(m_pGameObject)
		m_Transform = m_pGameObject->GetComponent<TransformComponent>();

	m_SrcRect.x = left;
	m_SrcRect.y = bottom;
	m_SrcRect.w = m_Width/2;
	m_SrcRect.h = m_Height/2;
	m_Texture = dae::ResourceManager::GetInstance().LoadTexture(path);
}

void SpriteComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);

	if (m_pGameObject)
		m_Transform = m_pGameObject->GetComponent<TransformComponent>();
	if(m_IsAnimated)
		m_SrcRect.x = (m_SrcRect.w * static_cast<int>((SDL_GetTicks()/ m_Delay)% m_Frames));

	if (m_Transform)
	{
		m_DestRect.x = static_cast<int>(m_Transform->GetPosition().x);
		m_DestRect.y = static_cast<int>(m_Transform->GetPosition().y);
		m_DestRect.w = m_Width * static_cast<int>(m_Transform->GetScale().x);
		m_DestRect.h = m_Height * static_cast<int>(m_Transform->GetScale().y);
	}


}

void SpriteComponent::Render()
{
	dae::Renderer::GetInstance().RenderTexture(*m_Texture, m_SrcRect , m_DestRect);

	//dae::Renderer::GetInstance().RenderTexture(*m_Texture, static_cast<float>(m_DestRect.x) , static_cast<float>(m_DestRect.y));
}
