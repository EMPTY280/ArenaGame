#include "Player.h"

Player::Player(MyVector2 pos) : Behavior(pos, ObjType::PLAYER)
	, aniCount(0), delay(0) { }

Player::~Player() { }

void Player::SetPosition(MyVector2 direction, bool relative)
{
	Behavior::SetPosition(direction, relative);
}

void Player::Start() { }

void Player::Update(Graphics* backGraphics, float deltaTime) 
{	
	delay += deltaTime;
	if (delay > 0.1f)
	{
		delay = 0.0f;
		aniCount++;
		if (aniCount > 3)
			aniCount = 0;
	}

	if (fireDelay > 0.0f)
		fireDelay -= deltaTime;

	if (direction.GetSize() <= 0.0f) aniCount = 1;

	SetPosition(direction * deltaTime * moveSpeed);
	myImage[walkSpriteIdx[aniCount]].Draw(backGraphics, position.xPos - 16, position.yPos - 16);
}

bool Player::Kill()
{
	return true;
}

std::vector<Behavior*> Player::Fire(MyVector2 dir)
{
	std::vector<Behavior*> result;

	if (fireDelay > 0.0f)
		return result;
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
			bulletSpeed -= rand() % multiShotVelocityVariance;
		b->SetSpeed(bulletSpeed);
		b->SetAccel(acceleration);
		b->SetLife(range);
		b->SetRadius(caliver);

		result.push_back((Behavior*)b);
	}
	return result;
}

bool Player::GetRight()
{
	return isRight;
}

void Player::SetRight(bool b)
{
	if (isRight == b)
		return;

	for (int ele : walkSpriteIdx)
		myImage[ele].FlipX(b);
	isRight = b;
}
