#include "Corpse.h"

Corpse::Corpse(MyVector2 pos) : Behavior(pos, ObjType::MISC)
{
	lifeTime = 2.0f;
}

Corpse::~Corpse()
{
}

void Corpse::Start()
{
}

void Corpse::Update(float delatTime)
{
	SetPosition(direction * speed * delatTime);

	speed -= friction * delatTime;
	if (speed < 0)
		speed = 0;

	lifeTime -= delatTime;
	if (lifeTime <= 0)
		KillSelf();
}

void Corpse::OnCollision(Behavior& collider, float deltaTime)
{
}

void Corpse::Render(Gdiplus::Graphics* backGraphics)
{
	if (myImage == nullptr)
		return;

	myImage[spriteIndex].FlipX(isRight);
	myImage[spriteIndex].Draw(backGraphics, position.xPos - 16, position.yPos + 8);
}

void Corpse::SetImage(SetMyImage* i)
{
	myImage = i;
}

void Corpse::SetRight(bool b)
{
	isRight = b;
}

void Corpse::SetMove(MyVector2 dir, float speed)
{
	direction = dir;
	this->speed = speed;
	if (this->speed > 3000.0f)
		this->speed = 3000.0f;
	friction = speed * 3.0f;
}
