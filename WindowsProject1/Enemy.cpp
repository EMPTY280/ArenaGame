#include "Enemy.h"
#include "Corpse.h"

Enemy::Enemy(MyVector2 pos, Behavior* target, GameWorld* g) : Behavior(pos, ObjType::ENEMY), target(target), g(g) { radius = 8.0f; }

Enemy::~Enemy() { }

void Enemy::Start() { }

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
	BlockBoundary();
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
		BlockBoundary();
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

void Enemy::TakeDamage(float amount, Bullet damageSource)
{
	hp -= amount;
	SetHitCount();

	if (hp > 0.0f)
		return;
	
	MyVector2 dir = damageSource.GetDirection();

	Corpse* c = new Corpse(position);
	c->SetImage(this->myImage);
	c->SetRight(isRight);
	c->SetMove(dir, damageSource.GetSpeed() * 0.5f);
	g->PushObject(c);

	KillSelf();
}

float Enemy::GetHP()
{
	return hp;
}
