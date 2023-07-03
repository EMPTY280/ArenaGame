#pragma once
#include "SetMyImage.h"
#include "MyVector2.h"

enum class ObjType
{
	MISC,
	PLAYER,
	ENEMY,
	BULLET
};

// ������Ʈ���� Bahavior�� ��ӹ޴´�.
class Behavior
{
protected:
	MyVector2 position;
	float radius;
	ObjType type = ObjType::MISC;

	float lifeTime;
	bool isDead;

public:
	Behavior(MyVector2 pos, ObjType type);
	virtual ~Behavior();

	MyVector2 GetPosition();
	// If relative is false, 'CHANGE' its position.
	virtual void SetPosition(MyVector2 direction, bool relative = true);

	virtual void Start() = 0;
	virtual void Update(float delatTime) = 0;  // ������Ʈ 

	// �ö��̴� üũ
	bool Collider(MyVector2 bPos, float bRadius);
	bool ColliderPoint(MyVector2 aPos, float aRadius, long x, long y);
	void ShowCollider(Graphics* backGraphics, Color c = Color::Red);

	float GetLife();
	void SetLife(float time);

	// (Object Type) Getter / Setter
	void SetType(ObjType _type);
	ObjType GetType() const;

	float GetRadius() const;
	void SetRadius(float r);

	bool IsDead();

	virtual void OnCollision(Behavior& collider) = 0;
	virtual void Render(Graphics* backGraphics) = 0;
};