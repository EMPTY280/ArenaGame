#pragma once
#include <queue>

#include "SetMyImage.h"
#include "SpriteZip.h"

#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "Spawner.h"

struct LayerSort
{
	bool operator()(Behavior* a, Behavior* b)
	{
		if (b->GetType() == ObjType::SPAWNER)
			return false;
		if (a->GetType() == ObjType::SPAWNER)
			return true;

		if (a->GetPosition().yPos > b->GetPosition().yPos)
		{
			return true;
		}
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

	float spawnInterval = 0.0f;
	void SpawnEnemy(float deltaTime);
	float spawnDelay = 0.5f;
	std::vector<Behavior*> spawnBuffer;

	bool paused = false;
	bool mouseDown = false;
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

	void UpdateMousePos(long x, long y);
	void SetMouseDown(bool b);

	void PushObject(std::vector<Behavior*>& src);
	void PushObject(Behavior* src);

	void AddSpawnBuffer(Behavior* src);
	void ClearSpawnBuffer();
};