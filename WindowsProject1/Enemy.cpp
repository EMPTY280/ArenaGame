#include "Enemy.h"

Enemy::Enemy(MyVector2 pos, Behavior* target) : Behavior(pos, ObjType::ENEMY), target(target) { radius = 8.0f; }

Enemy::~Enemy()
{
}

void Enemy::Start()
{
}

void Enemy::Update(float delatTime)
{
	delay += delatTime;
	if (delay > 0.1f)
	{
		delay = 0.0f;
		aniCount++;
		if (aniCount > 3)
			aniCount = 0;
	}

	if (hitCount > 0.0f)
		hitCount -= delatTime;

	MyVector2 dir = target->GetPosition() - position;
	dir.Normalize();

	if (dir.xPos < 0.0f)
		isRight = false;
	else if (dir.xPos > 0.0f)
		isRight = true;

	SetPosition(dir * moveSpeed * delatTime);
}

void Enemy::OnCollision(Behavior& collider, float deltaTime)
{
	if (!Collider(collider.GetPosition(), collider.GetRadius()))
		return;

	if (&collider == this)
		return;

	switch (collider.GetType())
	{
	case ObjType::PLAYER:
	case ObjType::ENEMY:
	{
		MyVector2 dir = position - collider.GetPosition();
		float len = radius - (dir.GetSize()) * 0.5f;
		dir.Normalize();

		SetPosition(dir * len);
	}
		break;
	}
}

void Enemy::Render(Graphics* backGraphics)
{
	if (hitCount > 0.0f)
	{
		myImage[hitSpriteIdx[aniCount]].FlipX(isRight);
		myImage[hitSpriteIdx[aniCount]].Draw(backGraphics, position.xPos - 16, position.yPos - 16);
		return;
	}

	myImage[walkSpriteIdx[aniCount]].FlipX(isRight);
	myImage[walkSpriteIdx[aniCount]].Draw(backGraphics, position.xPos - 16, position.yPos - 16);
}

void Enemy::SetHitCount()
{
	hitCount = hitCountMax;
}

void Enemy::SetHitCount(float time)
{
	hitCount = time;
}

void Enemy::TakeDamage(float amount)
{
	hp -= amount;
	SetHitCount();

	if (hp <= 0.0f)
		KillSelf();
}

float Enemy::GetHP()
{
	return hp;
}
