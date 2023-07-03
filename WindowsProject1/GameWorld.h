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
	//버퍼
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
	void Awake(HWND& _hwnd, HDC& _hdc); // 버퍼 생성.
	void ImageLoad();
	void Start(HWND& _hwnd);  // 초기화 작업.
	void Update(HWND& _hwnd, float deltaTime); // 게임 업데이트 루프 
	void Render(); // 그림 그리기
	void ReleaseMemory(HWND& _hwnd, HDC& _hdc); // 게임 끝난후 메모리 해제.
	void GameOver(HWND& _hwnd, float deltaTime); // 게임 종료
	void Input();
	void MouseEvnet(long x, long y);

	void CreateObject(std::vector<Behavior*>& src);
	void CreateObject(Behavior* src);
};