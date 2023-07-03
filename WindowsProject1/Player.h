#pragma once
#include <cmath>
#include <vector>

#include "Behavior.h"
#include "Bullet.h"

class Player :public Behavior
{
private:
	float moveSpeed = 150.0f;

	int walkSpriteIdx[4] = { 1, 0, 2, 0 };
	bool isRight = true;

	// 단위 : 초
	float fireDelay = 0.0f;
	float fireDelayMax = 0.1f;

	float velocity = 300.0f; // pixel/sec
	float acceleration = 100.0f; // pixel/sec^2

	float range = 600.0f; // pixel
	float caliver = 12.0f; // pixel radius

	float spread = 0.05f; // radian
	int multiShot = 1; // round

	float multiShotSpread = 0.025f; // radian
	int multiShotVelocityVariance = 0; // pixel/sec

	float targetVecSize = 0.0f;

public:
	Player(MyVector2 pos);
	virtual ~Player();
	SetMyImage *myImage;
	MyVector2 direction;
	
	int aniCount;
	float delay;

	virtual void SetPosition(MyVector2 direction, bool relative= true) override;

	virtual void Start() override;  // 초기화
	virtual void Update(float deltaTime) override; // 업데이트

	std::vector<Behavior*> Fire(MyVector2 dir);

	bool GetRight();
	void SetRight(bool b);

	virtual void OnCollision(Behavior& collider) override;
	virtual void Render(Graphics* backGraphics) override;
};

