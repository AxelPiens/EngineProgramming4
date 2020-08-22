#pragma once
#include "BaseComponent.h"
#include "Vector3.h"
	class Font;
	class Texture2D;
	class TextComponent : public BaseComponent
	{
	public:
		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) noexcept = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) noexcept = delete;

		TextComponent();
		void SetText(const std::string& text);
		void AddToText(const std::string& text);
		void SetPosition(float x, float y);
		void SetFont(const std::shared_ptr<Font>& font);
		void SetColor(std::vector<int> color);
		std::string GetText() { return m_Text; };
	protected:
		void Update(float deltaTime) override;
		void Render() override;
	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		engine::Vector3 m_Position;
		std::shared_ptr<Font> m_Font;
		std::shared_ptr<Texture2D> m_Texture;
		int m_Color[3];
	};

