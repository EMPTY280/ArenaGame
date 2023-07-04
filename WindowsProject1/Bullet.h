#pragma once
#include "Behavior.h"

class Bullet : public Behavior
{
private:
	MyVector2 MoveVector;
	float velocity = 1.0f;
	float acceleration = 0.0f;

	bool isPlayerOwned = true;

	MyVector2 targetVector = { 0.0f, 0.0f };
	float rotatePower = 0.0f;

	MyVector2 preVector;

public:
	SetMyImage* myImage;

	Bullet(MyVector2 pos);
	virtual ~Bullet() override;

	void SetVector(MyVector2 vec);
	void SetDirection(MyVector2 dir);
	void SetSpeed(float time);
	void SetAccel(float accel);
	void SetTargetVector(MyVector2 vec, float power);

	virtual void Start() override;
	virtual void Update(float delatTime) override;

	bool IsOwnerPlayer();
	void SetOwnerPlayer(bool b);

	virtual void OnCollision(Behavior& collider) override;
	virtual void Render(Graphics* backGraphics) override;
};