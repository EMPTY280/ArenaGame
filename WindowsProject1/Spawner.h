#pragma once
#include "Behavior.h"

class GameWorld;

class Spawner : public Behavior
{
private:
	GameWorld* s = nullptr;
	Behavior* enemy = nullptr;

	float spawnDelay = 0.0f;
	float spawnDelayMax = 1.5f;
public:
	Spawner(MyVector2 pos, Behavior* enemy);
	virtual ~Spawner() override;

	// Behavior을(를) 통해 상속됨
	virtual void Start() override;
	virtual void Update(float delatTime) override;
	virtual void OnCollision(Behavior& collider) override;
	virtual void Render(Graphics* backGraphics) override;
	virtual void OnKill(GameWorld* world) override;
};

