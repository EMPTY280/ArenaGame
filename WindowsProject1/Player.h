#pragma once
#include <cmath>
#include <vector>

#include "Behavior.h"
#include "Bullet.h"

class Player :public Behavior
{
private:
	MyVector2 moveVecBuffer = { 0.0f, 0.0f };
	float moveSpeed = 150.0f;
	bool isRight = true;

	int walkSpriteIdx[4] = { 1, 0, 2, 0 };
	int aniCount;
	float delay;

	MyVector2 fireVecBuffer = { 0.0f, 0.0f };
	std::vector<Behavior*> bullets;

	// ¥‹¿ß : √ 
	float fireDelay = 0.0f;
	float fireDelayMax = 0.1f;

	float velocity = 888800.0f; // pixel/sec
	float acceleration = 0.0f; // pixel/sec^2

	float range = 900.0f; // pixel
	float caliver = 4.0f; // pixel radius
	float damage = 0.0f;

	float spread = 0.1f; // radian
	int multiShot = 1; // round

	float multiShotSpread = 0.025f; // radian
	float multiShotVelocityVariance = 0.0f; // percentage

	float targetVecSize = 0.0f;

	void ResetMoveVector();
	void ResetFireVector();
public:
	Player(MyVector2 pos);
	virtual ~Player();
	SetMyImage *myImage;

	virtual void Start() override;
	virtual void Update(float deltaTime) override;
	virtual void Render(Graphics* backGraphics) override;
	virtual void OnCollision(Behavior& collider, float deltaTime) override;

	void Fire(MyVector2 dir);
	void SetRight(bool b);

	void SetMoveVector(float x, float y);
	void SetFireVector(float x, float y);

	int GetBulletsSize();
	std::vector<Behavior*>& GetBullets();
	void ClearBullets();

	void ShowRange(Graphics* backGraphics);
};

