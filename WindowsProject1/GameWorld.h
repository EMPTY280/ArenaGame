#pragma once
#include <queue>

#include "SetMyImage.h"
#include "Player.h"
#include "SpriteZip.h"
#include "Bullet.h"
#include "Enemy.h"

struct LayerSort
{
	bool operator()(Behavior* a, Behavior* b)
	{
		if (a->GetPosition().yPos > b->GetPosition().yPos)
			return true;
		return false;
	}
};

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
	std::priority_queue<Behavior*, std::vector<Behavior*>, LayerSort> layer;

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

	void CreateObject(std::vector<Behavior*>& src);
	void CreateObject(Behavior* src);
};