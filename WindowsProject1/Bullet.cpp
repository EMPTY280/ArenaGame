#include <cstdlib>

#include "Bullet.h"
#include "Enemy.h"

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

void Bullet::SetDamage(float dam)
{
	damage = dam;
}

void Bullet::SetRange(float range)
{
	this->range = range;
	lifeTime = range;
}

MyVector2 Bullet::GetDirection()
{
	return MoveVector;
}

float Bullet::GetSpeed()
{
	return velocity;
}

void Bullet::Start() { }

void Bullet::Update(float delatTime)
{
	if (velocity * delatTime > range)
		velocity = range / delatTime - 0.1f;

	preVectors.push(position);

	if (preVectors.size() >= 5)
		preVectors.pop();

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

void Bullet::OnCollision(Behavior& collider, float deltaTime)
{
	if (&collider == this)
		return;
	if (collider.GetType() != ObjType::ENEMY)
		return;

	MyVector2 prePos;
	float projection;

	if (abs(velocity) <= 1)
	{
		if (!Collider(collider.GetPosition(), collider.GetRadius()))
			return;
	}
	else
	{
		float dist = 0;

		prePos = position - MoveVector * velocity * deltaTime;

		MyVector2 bulletVec(MoveVector * velocity * deltaTime); // 총알의 이동 궤적 선분
		MyVector2 toTarget(collider.GetPosition() - prePos); // 목표 까지의 상대 거리
		projection = (bulletVec.xPos * toTarget.xPos + bulletVec.yPos * toTarget.yPos) / bulletVec.GetSize();

		if (projection <= 0)
			dist = toTarget.GetSize();
		else if (projection < bulletVec.GetSize())
			dist = sqrt(powf(toTarget.GetSize(), 2.0f) - powf(projection, 2.0f));
		else
			dist = MyVector2(collider.GetPosition() - (position)).GetSize();

		if (dist > radius + collider.GetRadius())
			return;
	}
	switch (collider.GetType())
	{
	case ObjType::ENEMY:
		if (GetLife() <= 0.0f) break;
		if (!IsOwnerPlayer()) break;

		Enemy* e = dynamic_cast<Enemy*>(&collider);
		e->TakeDamage(damage, Bullet(*this));

		position = prePos + MoveVector * projection;

		SetLife(0.0f);

		break;
	}
}

void Bullet::Render(Graphics* backGraphics)
{
	Color bulletColor(255, 255, 255);
	if (!isPlayerOwned)
		bulletColor = Color(255, 0, 0);

	int size = radius * 0.5f;
		
	float rightAngle = 3.14159265358979f * 0.5f;
	float rightRad = atan2f(MoveVector.yPos, MoveVector.xPos);

	MyVector2 rightVec1(cos(rightRad + rightAngle), sin(rightRad + rightAngle));
	MyVector2 rightVec2(cos(rightRad - rightAngle), sin(rightRad - rightAngle));

	Point p1(position.xPos + rightVec1.xPos * size, position.yPos + rightVec1.yPos * size);
	Point p2(preVectors.front().xPos, preVectors.front().yPos);
	Point p3(position.xPos + rightVec2.xPos * size, position.yPos + rightVec2.yPos * size);

	GraphicsPath p;
	p.AddLine(p1, p2);
	p.AddLine(p2, p3);
	p.AddLine(p3, p1);

	PathGradientBrush b(&p);
	Color colors[] = { Color(255, 255, 255), Color(0, 255, 255, 255), Color(255, 255, 255) };
	int count = 3;
	b.SetCenterPoint(p1);
	b.SetSurroundColors(colors, &count);

	backGraphics->FillPath(&b, &p);

	int xx = position.xPos - size;
	int yy = position.yPos - size;

	SolidBrush brush(bulletColor);
	backGraphics->FillEllipse(&brush, xx, yy, (int)radius, (int)radius);
}
