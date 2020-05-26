#pragma once
#include "BaseComponent.h"
#include "Texture2D.h"
#include "Vector3.h"

class TextureComponent : public BaseComponent
{
public:
	TextureComponent(const TextureComponent& other) = delete;
	TextureComponent(TextureComponent&& other) noexcept = delete;
	TextureComponent& operator=(const TextureComponent& other) = delete;
	TextureComponent& operator=(TextureComponent&& other) noexcept = delete;
	TextureComponent(const std::string& fileName);
	void SetTexture(const std::string& filename);
	void Render() override;
protected:
	void Update(float deltaTime) override;
private:
	std::shared_ptr<dae::Texture2D> m_Texture{};
};

