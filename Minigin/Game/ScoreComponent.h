#pragma once
#include <BaseComponent.h>

class ScoreComponent : public BaseComponent
{
public:
	ScoreComponent(const ScoreComponent& other) = delete;
	ScoreComponent(ScoreComponent&& other) noexcept = delete;
	ScoreComponent& operator=(const ScoreComponent& other) = delete;
	ScoreComponent& operator=(ScoreComponent&& other) noexcept = delete;
	ScoreComponent();
	void AddScore(std::shared_ptr<engine::GameObject> pGameObject);
	int GetScore() { return m_TotalScore; };
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	int m_TotalScore = 0;
	int m_EmeraldsInARow = 0;
};

