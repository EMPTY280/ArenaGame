#include "MyVector2.h"


MyVector2 MyVector2::operator+=(const MyVector2& vec2)
{
	*this = *this + vec2;
	return *this;
}

MyVector2 MyVector2::operator*=(float time)
{
	*this = *this * time;
	return *this;
}

MyVector2 MyVector2::operator*(float time)
{
	MyVector2 vec(this->xPos * time, this->yPos * time);
	return vec;
}

MyVector2 MyVector2::operator-(const MyVector2& vec2)
{
	MyVector2 vec(this->xPos - vec2.xPos, this->yPos - vec2.yPos);
	return vec;
}

MyVector2 MyVector2::operator+(const MyVector2& vec2)
{
	MyVector2 vec(this->xPos + vec2.xPos, this->yPos + vec2.yPos);
	return vec;
}

void MyVector2::SetDirection(float _xPos, float _yPos)
{
	this->xPos = _xPos;
	this->yPos = _yPos;
}

void MyVector2::Normalize()
{
	float dist = sqrt(powf(xPos, 2) + powf(yPos, 2));

	if (dist == 0.0f)
		return;

	xPos /= dist;
	yPos /= dist;
}

void MyVector2::MyNomalizedDirection(MyVector2 a, MyVector2 b)
{
	MyVector2 c = b - a;

	double d = sqrt((c.xPos * c.xPos) + (c.yPos * c.yPos));
	this->xPos = c.xPos / d;
	this->yPos = c.yPos / d;
}

float MyVector2::GetSize()
{
	return sqrt(powf(xPos, 2) + powf(yPos, 2));
}
