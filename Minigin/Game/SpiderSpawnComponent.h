#pragma once
#include <BaseComponent.h>
class SpiderSpawnComponent : public BaseComponent
{
public:
	SpiderSpawnComponent(const SpiderSpawnComponent& other) = delete;
	SpiderSpawnComponent(SpiderSpawnComponent&& other) noexcept = delete;
	SpiderSpawnComponent& operator=(const SpiderSpawnComponent& other) = delete;
	SpiderSpawnComponent& operator=(SpiderSpawnComponent&& other) noexcept = delete;
	SpiderSpawnComponent(int amountOfSpawns, float spawnTime);
protected:
	void Update(float deltaTime) override;
	void Render() override;
private:
	float m_ElapsedTime = 0.0f;
	float m_SpawnTime = 0.0f;
	int m_AmountOfSpawns = 0;
	int m_Number = 0;
};

