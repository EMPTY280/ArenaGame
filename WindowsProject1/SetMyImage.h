#pragma once

#include <Windows.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
#pragma comment(lib, "winmm")


using namespace Gdiplus;

class SetMyImage
{
protected:
	Image* _image;
	bool isFlippedX = false;
public:
	SetMyImage();
	virtual ~SetMyImage();


	void Load(const char* lpstrFile);
	void Draw(Graphics* g, int x, int y);
	void Draw(Graphics* g, int x, int y, int radius);
	void Draw(Graphics* g, int dstX, int dstY, int width, int height);
	void Release();

	void FlipX(bool right);
};

