#include "Bullet.h"

Bullet::Bullet(MyVector2 pos) : Behavior(pos, ObjType::BULLET), MoveVector(0, 0) { }

Bullet::~Bullet() { }

void Bullet::SetVector(MyVector2 vec)
{
	MoveVector = vec;
}

void Bullet::SetDirection(MyVector2 dir)
{
	MoveVector = dir;
	MoveVector.Normalize();
}

void Bullet::SetSpeed(float time)
{
	velocity = time;
}

void Bullet::SetAccel(float accel)
{
	acceleration = accel;
}

void Bullet::Start() { }

void Bullet::Update(Graphics* backGraphics, float delatTime)
{
	SetPosition(MoveVector * delatTime * velocity);

	if (lifeTime == -1.0f)
		return;

	lifeTime -= delatTime * MoveVector.GetSize() * velocity;
	if (lifeTime <= 0.0f)
		isDead = true;

	velocity += acceleration * delatTime;
	if (velocity < 0.0f)
		isDead = true;
}

bool Bullet::Kill()
{
	return false;
}
