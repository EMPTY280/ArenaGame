#pragma once
#include "Behavior.h"
class Corpse : public Behavior
{
private:
	int spriteIndex = 18;
	SetMyImage* myImage = nullptr;

	MyVector2 direction;
	float speed;
	float friction = 500.0f;

	bool isRight = true;
public:
	Corpse(MyVector2 pos);
	virtual ~Corpse();

	// Behavior을(를) 통해 상속됨
	virtual void Start();
	virtual void Update(float delatTime);
	virtual void OnCollision(Behavior& collider, float deltaTime);
	virtual void Render(Gdiplus::Graphics* backGraphics);

	void SetImage(SetMyImage* i);
	void SetRight(bool b);
	void SetMove(MyVector2 dir, float speed);
};