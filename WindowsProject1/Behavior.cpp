#include "Behavior.h"

void Behavior::KillSelf()
{
	isDead = true;
}

Behavior::Behavior(MyVector2 pos, ObjType type) : position(pos), type(type)
	, radius(16.0f), lifeTime(-1.0f), isDead(false) { }

Behavior::~Behavior() { }

MyVector2 Behavior::GetPosition()
{
	return position;
}

void Behavior::SetPosition(MyVector2 direction, bool relative)
{
	if (relative)
	{
		position += direction;
		return;
	}

	position = direction;
}

void Behavior::OnKill(GameWorld* world)
{
}

bool Behavior::Collider(MyVector2 bPos, float bRadius)
{
	bool isEnter = false;

	float xx = position.xPos - bPos.xPos;
	float yy = position.yPos - bPos.yPos;

	float dist = xx * xx + yy * yy;

	float tt = radius + bRadius;

	if (dist <= tt * tt)
	{
		isEnter = true;
	}
	return isEnter;
}

bool Behavior::ColliderPoint(MyVector2 aPos, float aRadius, long x, long y)
{
	bool isEnter = false;

	float dist = sqrt(pow(aPos.xPos - x, 2) + pow(aPos.yPos - y, 2));

	if (dist <= aRadius)
	{
		isEnter = true;
	}
	return isEnter;
}

void Behavior::ShowCollider(Graphics* backGraphics, Color c)
{
	Pen pen(c);

	int xx = position.xPos - radius;
	int yy = position.yPos - radius;
	int diameter = radius * 2;

	backGraphics->DrawEllipse(&pen, xx, yy, diameter, diameter);
	backGraphics->DrawRectangle(&pen, (int)position.xPos, (int)position.yPos, 1, 1);
}

float Behavior::GetLife()
{
	return lifeTime;
}

void Behavior::SetLife(float time)
{
	lifeTime = time;
}

void Behavior::SetType(ObjType _type)
{
	this->type = _type;
}

ObjType Behavior::GetType() const
{
	return type;
}

float Behavior::GetRadius() const
{
	return radius;
}

void Behavior::SetRadius(float r)
{
	radius = r;
}

bool Behavior::IsDead()
{
	return isDead;
}