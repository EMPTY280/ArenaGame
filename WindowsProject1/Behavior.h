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
	virtual void Update(Graphics* backGraphics, float delatTime) = 0;  // ������Ʈ 

	// �ö��̴� üũ
	bool Collider(MyVector2 aPos, float aRadius, MyVector2 bPos, float bRadius);
	bool ColliderPoint(MyVector2 aPos, float aRadius, long x, long y);
	void ShowCollider(Graphics* backGraphics, Color c = Color::Red);

	void SetLife(float time);

	// (Object Type) Getter / Setter
	void SetType(ObjType _type);
	ObjType GetType() const;

	void SetRadius(float r);

	bool IsDead();
	// false ��ȯ �� ��ü ���� ��û
	virtual bool Kill() = 0;
};