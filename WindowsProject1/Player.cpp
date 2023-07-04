#include "Player.h"

Player::Player(MyVector2 pos) : Behavior(pos, ObjType::PLAYER)
, aniCount(0), delay(0) {
	radius = 8.0f;
}

Player::~Player() { }

void Player::Start() { }

void Player::Update(float deltaTime) 
{	
	// movement
	MyVector2 dir = moveVecBuffer.Normalize();
	SetPosition(dir * deltaTime * moveSpeed);
	ResetMoveVector();

	// attack
	if (fireDelay > 0.0f)
		fireDelay -= deltaTime;
	fireVecBuffer.Normalize();
	if (fireVecBuffer.GetSize() > 0.0f)
		Fire(fireVecBuffer);
	ResetFireVector();

	// animation
	delay += deltaTime;
	if (delay > 0.1f)
	{
		delay = 0.0f;
		aniCount++;
		if (aniCount > 3) aniCount = 0;
	}

	if (dir.GetSize() <= 0.0f) aniCount = 1;
}

void Player::Fire(MyVector2 dir)
{
	if (fireDelay > 0.0f)
		return;
	fireDelay += fireDelayMax;

	for (int i = 0; i < multiShot; i++)
	{
		Bullet* b = new Bullet(GetPosition());

		// spread 
		float sp = multiShotSpread * (- multiShot + 1 + 2 * i) * 0.5f;
		if (spread > 0.0f)
			sp += (float)(rand() % (int)(spread * 1000.0f)) * 0.001f - spread * 0.5f;
		sp *= 3.14159265358979f;

		float dir_rad = atan2f(dir.yPos, dir.xPos);
		dir_rad += sp;

		MyVector2 final(cos(dir_rad), sin(dir_rad));

		b->SetVector(final);

		float bulletSpeed = velocity;
		if (multiShotVelocityVariance > 0)
			bulletSpeed -= (rand() % (int)(multiShotVelocityVariance * 100) * 0.01) * bulletSpeed;
		b->SetSpeed(bulletSpeed);
		b->SetAccel(acceleration);
		b->SetLife(range);
		b->SetRadius(caliver);
		b->myImage = myImage;
		b->SetTargetVector(dir, targetVecSize);

		bullets.push_back((Behavior*)b);
	}
}

void Player::SetRight(bool b)
{
	isRight = b;
}

void Player::OnCollision(Behavior& collider)
{
	if (!Collider(collider.GetPosition(), collider.GetRadius()))
		return;

	switch (collider.GetType())
	{
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

void Player::Render(Graphics* backGraphics)
{
	myImage[walkSpriteIdx[aniCount]].FlipX(isRight);
	myImage[walkSpriteIdx[aniCount]].Draw(backGraphics, position.xPos - 16, position.yPos - 16);
}

void Player::SetMoveVector(float x, float y)
{
	moveVecBuffer += MyVector2(x, y);
	if (moveVecBuffer.xPos > 0)
		SetRight(true);
	else
		SetRight(false);
}

void Player::ResetMoveVector()
{
	moveVecBuffer = MyVector2(0.0f, 0.0f);
}

void Player::SetFireVector(float x, float y)
{
	fireVecBuffer += MyVector2(x, y);
	if (fireVecBuffer.xPos > 0)
		SetRight(true);
	else
		SetRight(false);
}

void Player::ResetFireVector()
{
	fireVecBuffer = MyVector2(0.0f, 0.0f);
}

int Player::GetBulletsSize()
{
	return bullets.size();
}

std::vector<Behavior*>& Player::GetBullets()
{
	return bullets;
}

void Player::ClearBullets()
{
	bullets.clear();
}
