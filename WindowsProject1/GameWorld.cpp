#include "GameWorld.h"

#define ON_PRESS(X) (::GetAsyncKeyState(X) & 0x8000)
#define ON_TOGGLE(X) (::GetAsyncKeyState(X) & 0x0001)
// 우측 비트 8 = 호출 시점에서 누른 상태인가
// 좌특 비트 1 = 이전에 누른 적이 있는가

GameWorld::GameWorld() : player(MyVector2(200, 200), this) 
{
	PushObject(&player);
}

GameWorld::~GameWorld()
{ 

}

void GameWorld::Awake(HWND& _hwnd, HDC& _hdc) // 버퍼 만들기.
{
	ULONG_PTR gpToken;
	GdiplusStartupInput gpsi;
	GdiplusStartup(&gpToken, &gpsi, NULL);

	RECT windowRect;
	GetClientRect(_hwnd, &windowRect);

	memoryBitmap = new Bitmap(windowRect.right - windowRect.left, windowRect.bottom - windowRect.top);
	backGraphics = new Graphics(memoryBitmap);
	backGraphics->SetPageUnit(Gdiplus::Unit::UnitPixel);

	mainGraphics = new Graphics(_hdc);
	mainGraphics->SetPageUnit(Gdiplus::Unit::UnitPixel);
}

void GameWorld::ImageLoad()
{
	spriteZip.SetImage();
	player.myImage = spriteZip.playerImages;
}

void GameWorld::Start(HWND& _hwnd)  // 각종 오브젝트들 초기화
{
	player.Start();
}

void GameWorld::Update(HWND& _hwnd, float deltaTime) // 게임 업데이트.
{
	Graphics graphics(_hwnd);
	Input();

	if (paused)
		return;

	if (spawnBuffer.size() > 0)
	{
		PushObject(spawnBuffer);
		ClearSpawnBuffer();
	}

	for (int i = 0; i < objList.size(); i++)
	{
		Behavior* ele = objList[i];

		ele->Update(deltaTime);
	}

	// collision check
	for (int i = 0; i < objList.size(); i++)
	{
		Behavior* ele = objList[i];
		for (int r = 0; r < objList.size(); r++)
		{
			Behavior* ele2 = objList[r];
			ele->OnCollision(*ele2, deltaTime);
		}
	}

	for (int i = 0; i < objList.size(); i++)
	{
		Behavior* ele = objList[i];
		// kill check
		if (ele->IsDead())
		{
			ele->OnKill(this);
			delete ele;
			objList.erase(objList.begin() + i);
			i--;
			continue;
		}
		// push to draw queue
		layer.push(ele);
	}

	while (!layer.empty())
	{
		layer.top()->Render(backGraphics);
		layer.pop();
	}

	SpawnEnemy(deltaTime);
}

void GameWorld::Render()
{
	if (paused)
		return;

	Font F(L"Arial", 20, FontStyleRegular, UnitPixel);
	PointF P(10.0f, 10.0f);
	SolidBrush B(Color(0, 0, 255));
	backGraphics->DrawString(L"Test String", -1, &F, P, &B);

	mainGraphics->DrawImage(memoryBitmap, 0, 0);
	backGraphics->Clear(Color::Black);
}

void GameWorld::ReleaseMemory(HWND& _hwnd, HDC& _hdc)
{
	ReleaseDC(_hwnd, _hdc);

	delete memoryBitmap;
	delete backGraphics;
	delete mainGraphics;
}

void GameWorld::PushObject(std::vector<Behavior*>& src)
{
	if (src.size() <= 0)
		return;

	objList.insert(objList.end(), src.begin(), src.end());
}

void GameWorld::PushObject(Behavior* src)
{
	if (src == nullptr)
		return;

	objList.push_back(src);
}

void GameWorld::AddSpawnBuffer(Behavior* src)
{
	spawnBuffer.push_back(src);
}

void GameWorld::ClearSpawnBuffer()
{
	spawnBuffer.clear();
}

void GameWorld::SpawnEnemy(float deltaTime)
{
	spawnInterval += deltaTime;

	if (spawnDelay > spawnInterval)
		return;
	spawnInterval = 0.0f;

	MyVector2 pos = { (float)(rand() % 1280), (float)(rand() % 720) };

	Enemy* e = new Enemy(pos, &player, this);
	e->myImage = spriteZip.playerImages;
	Spawner* s = new Spawner(pos, e);
	PushObject(s);
}

void GameWorld::GameOver(HWND& _hwnd, float deltaTime)
{
	MessageBox(_hwnd, L"Over", L"Fail", MB_OK);
	PostQuitMessage(0);
}

void GameWorld::Input()
{
	if (ON_PRESS('W')) { player.SetMoveVector(0.0f, -1.0f); }
	if (ON_PRESS('A')) { player.SetMoveVector(-1.0f, 0.0f); }
	if (ON_PRESS('S')) { player.SetMoveVector(0.0f, 1.0f); }
	if (ON_PRESS('D')) { player.SetMoveVector(1.0f, 0.0f); }

	if (ON_PRESS(VK_UP)) player.SetFireVector(0.0f, -1.0f);
	if (ON_PRESS(VK_LEFT)) player.SetFireVector(-1.0f, 0.0f);
	if (ON_PRESS(VK_DOWN)) player.SetFireVector(0.0f, 1.0f);
	if (ON_PRESS(VK_RIGHT)) player.SetFireVector(1.0f, 0.0f);

	if (ON_TOGGLE(VK_SPACE)) paused = !paused;

	if (mouseDown)
	{
		MyVector2 v = MyVector2(mx, my) - player.GetPosition();
		player.SetFireVector(v.xPos, v.yPos);
	}
}

void GameWorld::UpdateMousePos(long x, long y)
{
	mx = x;
	my = y;
}

void GameWorld::SetMouseDown(bool b)
{
	mouseDown = b;
}
