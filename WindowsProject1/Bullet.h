#pragma once
#include "Behavior.h"

class Bullet : public Behavior
{
private:
	MyVector2 MoveVector;
	float velocity = 1.0f;
	float acceleration = 0.0f;

public:
	Bullet(MyVector2 pos);
	virtual ~Bullet() override;

	void SetVector(MyVector2 vec);
	void SetDirection(MyVector2 dir);
	void SetSpeed(float time);
	void SetAccel(float accel);

	virtual void Start() override;
	virtual void Update(Graphics* backGraphics, float delatTime) override;
	virtual bool Kill() override;
};