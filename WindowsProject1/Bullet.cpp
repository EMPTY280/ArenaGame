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

void Bullet::SetTargetVector(MyVector2 vec)
{
	TargetVector = vec;
}

void Bullet::Start() { }

void Bullet::Update(float delatTime)
{
	SetPosition(MoveVector * delatTime * velocity);

	if (lifeTime == -1.0f)
		return;

	lifeTime -= delatTime * MoveVector.GetSize() * velocity;
	if (lifeTime <= 0.0f)
		isDead = true;

	velocity += acceleration * delatTime;
	if (velocity < 0.0f && acceleration <= 0.0f)
		isDead = true;

	if (TargetVector.GetSize() == 0.0f)
		return;
	MoveVector = MoveVector + TargetVector * delatTime;
	MoveVector.Normalize();
}

bool Bullet::IsOwnerPlayer()
{
	return isPlayerOwned;
}

void Bullet::SetOwnerPlayer(bool b)
{
	isPlayerOwned = b;
}

void Bullet::OnCollision(Behavior& collider)
{
	if (!Collider(collider.GetPosition(), collider.GetRadius()))
		return;

	switch (collider.GetType())
	{
	case ObjType::ENEMY:
	break;
	}
}

void Bullet::Render(Graphics* backGraphics)
{

	myImage[13].Draw(backGraphics, position.xPos - 4, position.yPos - 4);
}
