#pragma once
#include "BaseComponent.h"
#include <SDL.h>
#include <string>
#include "Texture2D.h"
class TransformComponent;
class SpriteComponent : public BaseComponent
{
public:
	SpriteComponent(const SpriteComponent& other) = delete;
	SpriteComponent(SpriteComponent&& other) noexcept = delete;
	SpriteComponent& operator=(const SpriteComponent& other) = delete;
	SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

	SpriteComponent(const std::string path, int width, int height, int bottom, int left, int nrFrames, int delay, bool animated);
	~SpriteComponent() = default;

protected:
	void Update(float deltaTime) override;
	void Render() override;

private:
	SDL_Rect m_SrcRect, m_DestRect;
	std::shared_ptr<dae::Texture2D> m_Texture;
	TransformComponent* m_Transform;
	int m_Width, m_Height = 32;
	int m_Frames = 0;
	int m_Delay = 100; //delay between frames in ms
	bool m_IsAnimated = false;
};

