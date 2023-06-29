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

// 오브젝트들은 Bahavior를 상속받는다.
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
	virtual void Update(Graphics* backGraphics, float delatTime) = 0;  // 업데이트 

	// 컬라이더 체크
	bool Collider(MyVector2 aPos, float aRadius, MyVector2 bPos, float bRadius);
	bool ColliderPoint(MyVector2 aPos, float aRadius, long x, long y);
	void ShowCollider(Graphics* backGraphics, Color c = Color::Red);

	void SetLife(float time);

	// (Object Type) Getter / Setter
	void SetType(ObjType _type);
	ObjType GetType() const;

	void SetRadius(float r);

	bool IsDead();
	// false 반환 시 객체 삭제 요청
	virtual bool Kill() = 0;
};