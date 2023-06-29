
#include "SetMyImage.h"


SetMyImage::SetMyImage()
{
	_image = NULL;
}

SetMyImage::~SetMyImage()
{

}


void SetMyImage::Load(const char* lpstrFile)
{
	if (_image)
		delete _image;

	WCHAR file[MAX_PATH];
	MultiByteToWideChar(CP_ACP, NULL, lpstrFile, -1, file, MAX_PATH);



	_image = Image::FromFile(file);
}

void SetMyImage::Draw(Graphics* g, int x, int y)
{
	g->DrawImage(_image, x, y);
}

void SetMyImage::Draw(Graphics* g, int x, int y, int radius)
{
	g->DrawImage(_image, x - radius, y - radius);
}

void SetMyImage::Draw(Graphics* g, int dstX, int dstY, int width, int height)
{
	g->DrawImage(_image, dstX, dstY, width, height);
}

void SetMyImage::Release()
{
	if (_image)
		delete _image;

	_image = NULL;
}

void SetMyImage::FlipX(bool right)
{
	if (right != isFlippedX)
		return;

	isFlippedX = !right;
	_image->RotateFlip(Gdiplus::RotateNoneFlipX);
}
