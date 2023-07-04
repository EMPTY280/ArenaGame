#include "Bullet.h"

Bullet::Bullet(MyVector2 pos) : Behavior(pos, ObjType::BULLET), MoveVector(0, 0) { radius = 12.0f; }

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

void Bullet::SetTargetVector(MyVector2 vec, float power)
{
	targetVector = vec;
	rotatePower = power;
}

void Bullet::Start() { }

void Bullet::Update(float delatTime)
{
	preVector = position;
	SetPosition(MoveVector * delatTime * velocity);

	if (lifeTime == -1.0f)
		return;

	lifeTime -= delatTime * MoveVector.GetSize() * velocity;
	if (lifeTime <= 0.0f)
		KillSelf();

	velocity += acceleration * delatTime;
	if (velocity < 0.0f && acceleration <= 0.0f)
		KillSelf();

	if (targetVector.GetSize() == 0.0f)
		return;
	MoveVector = MoveVector + targetVector * delatTime * rotatePower;
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
}

void Bullet::Render(Graphics* backGraphics)
{
	int spriteNum = 13;
	if (!isPlayerOwned)
		spriteNum = 17;
	myImage[spriteNum].Draw(backGraphics, position.xPos - 4, position.yPos - 4);

	MyVector2 startVec = position + (preVector - position).Normalize() * 4.0f;
	MyVector2 startVec2 = (position - MyVector2(1.0f, 1.0f)) + (preVector - position).Normalize() * 4.0f;
		
	Pen pen(Color(255, 255, 255));
	backGraphics->DrawLine(&pen, startVec.xPos, startVec.yPos, preVector.xPos, preVector.yPos);
	backGraphics->DrawLine(&pen, startVec2.xPos, startVec2.yPos, preVector.xPos, preVector.yPos);
}
