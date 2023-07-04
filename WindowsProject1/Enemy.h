#pragma once
#include "Behavior.h"
#include "Bullet.h"
#include "GameWorld.h"

class Enemy : public Behavior
{
private:
	Behavior* target;
	float moveSpeed = 75.0f;

	float hp = 3.0f;

	bool isRight = true;
	int walkSpriteIdx[4] = { 11, 10, 12, 10 };
	int hitSpriteIdx[4] = { 15, 14, 16, 14 };
	int aniCount;
	float delay;

	float hitCount = 0.0f;
	float hitCountMax = 0.05f;

public:
	SetMyImage* myImage;

	Enemy(MyVector2 pos, Behavior* target);
	virtual ~Enemy() override;

	virtual void Start() override;
	virtual void Update(float delatTime) override;
	virtual void OnCollision(Behavior& collider) override;
	virtual void Render(Graphics* backGraphics) override;

	void SetHitCount();
	void SetHitCount(float time);
};