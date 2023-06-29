#pragma once
#include "SetMyImage.h"
#include "Player.h"
#include "SpriteZip.h"
#include "Bullet.h"

class GameWorld
{
private:
	//����
	Bitmap* memoryBitmap;
	Graphics* backGraphics;
	Graphics* mainGraphics;
	long mx = 0;
	long my = 0;
	Player player;
	SpriteZip spriteZip;

	std::vector<Behavior*> objList;

public:
	GameWorld();
	~GameWorld();
	void Awake(HWND& _hwnd, HDC& _hdc); // ���� ����.
	void ImageLoad();
	void Start(HWND& _hwnd);  // �ʱ�ȭ �۾�.
	void Update(HWND& _hwnd, float deltaTime); // ���� ������Ʈ ���� 
	void Render(); // �׸� �׸���
	void ReleaseMemory(HWND& _hwnd, HDC& _hdc); // ���� ������ �޸� ����.
	void GameOver(HWND& _hwnd, float deltaTime); // ���� ����
	void Input();
	void MouseEvnet(long x, long y);
};