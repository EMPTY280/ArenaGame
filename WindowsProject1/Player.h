#pragma once
#include <cmath>
#include <vector>

#include "Behavior.h"
#include "Bullet.h"

class Player :	public Behavior
{
private:
	float moveSpeed = 150.0f;

	int walkSpriteIdx[4] = { 1, 0, 2, 0 };
	bool isRight = true;

	// 단위 : 초
	float fireDelay = 0.0f;
	float fireDelayMax = 0.1f;

	float velocity = 600.0f; // pixel/sec
	float acceleration = 0.0f; // pixel/sec^2

	float range = 600.0f; // pixel
	float caliver = 8.0f; // pixel radius

	float spread = 0.0f; // radian
	int multiShot = 5; // round

	float multiShotSpread = 0.025f; // radian
	int multiShotVelocityVariance = 0; // pixel/sec

public:
	Player(MyVector2 pos);
	virtual ~Player();
	SetMyImage *myImage;
	MyVector2 direction;
	
	int aniCount;
	float delay;

	virtual void SetPosition(MyVector2 direction, bool relative= true) override;

	virtual void Start() override;  // 초기화
	virtual void Update(Graphics* backGraphics, float deltaTime) override; // 업데이트
	virtual bool Kill();

	std::vector<Behavior*> Fire(MyVector2 dir);

	bool GetRight();
	void SetRight(bool b);
};

