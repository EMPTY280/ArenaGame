#pragma once
#include <cmath>

class MyVector2
{
public:
	float xPos = 0;
	float yPos = 0;
public:
	MyVector2(float _xPos = 0, float _yPos = 0) : xPos(_xPos), yPos(_yPos) {}  // ���۷���Ʈ.
	MyVector2 operator+=(const MyVector2& vec);
	MyVector2 operator*=(float time);
	MyVector2 operator*(float time);
	MyVector2 operator-(const MyVector2& vec2);
	MyVector2 operator+(const MyVector2& vec2);

	void SetDirection(float _xPos, float _yPos);
	MyVector2 Normalize();
	void MyNomalizedDirection(MyVector2 a, MyVector2 b);  // ���� �ΰ� �޾ƿ� ������ ���� �� ����ȭ.

	float GetSize();
};