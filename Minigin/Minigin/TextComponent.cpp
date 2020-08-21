#include "MiniginPCH.h"
#include "TextComponent.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

TextComponent::TextComponent()
	:m_NeedsUpdate{false}
{
}

void TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void TextComponent::AddToText(const std::string& text)
{
	m_Text += text;
	m_NeedsUpdate = true;
}

void TextComponent::SetPosition(float x, float y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = 0;
	m_NeedsUpdate = true;
}

void TextComponent::SetFont(const std::shared_ptr<Font>& font)
{
	m_Font = font;
	m_NeedsUpdate = true;
}

void TextComponent::SetColor(std::vector<int> color)
{
	m_Color[0] = color[0];
	m_Color[1] = color[1];
	m_Color[2] = color[2];

}

void TextComponent::Render()
{
	if (m_Texture != nullptr)
	{
		const auto pos = m_Position;
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}


void TextComponent::Update(float deltaTime)
{
	UNREFERENCED_PARAMETER(deltaTime);
	if (m_NeedsUpdate)
	{
		const SDL_Color color = { Uint8(m_Color[0]), Uint8(m_Color[1]),Uint8(m_Color[2])}; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_Texture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

