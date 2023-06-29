#include "Behavior.h"

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

bool Behavior::Collider(MyVector2 aPos, float aRadius, MyVector2 bPos, float bRadius)
{
	bool isEnter = false;

	float dist = sqrt(pow(aPos.xPos - bPos.xPos, 2) + pow(aPos.yPos - bPos.yPos, 2));

	if (dist <= aRadius + bRadius)
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

void Behavior::SetRadius(float r)
{
	radius = r;
}

bool Behavior::IsDead()
{
	return isDead;
}
