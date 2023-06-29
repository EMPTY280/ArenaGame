#include "GameWorld.h"

#define ON_PRESS(X) (::GetAsyncKeyState(X) & 0x8000f)

GameWorld::GameWorld() : player(MyVector2(20, 20)) { }

GameWorld::~GameWorld() { }

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

	player.Update(backGraphics, deltaTime);

	int size = objList.size();
	for (int i = 0; i < size; i++)
	{
		Behavior* ele = objList[i];

		ele->Update(backGraphics, deltaTime);

		if (ele->IsDead())
		{
			if (ele->Kill())
				continue;
			objList.erase(objList.begin() + i);
			i--;
			size--;
		}
	}
}

void GameWorld::Render()
{
	player.ShowCollider(backGraphics);
	for (Behavior* ele : objList)
	{
		ele->ShowCollider(backGraphics, Color::White);
	}

	mainGraphics->DrawImage(memoryBitmap, 00, 0);

	backGraphics->Clear(Color::Black);
}

void GameWorld::ReleaseMemory(HWND& _hwnd, HDC& _hdc)
{
	ReleaseDC(_hwnd, _hdc);

	delete memoryBitmap;
	delete backGraphics;
	delete mainGraphics;
}

void GameWorld::MouseEvnet(long x, long y)
{
	mx = x;
	my = y;
}

void GameWorld::GameOver(HWND& _hwnd, float deltaTime)
{
	MessageBox(_hwnd, L"Over", L"Fail", MB_OK);
	PostQuitMessage(0);
}

void GameWorld::Input()
{
	float hor = 0.0f;
	float ver = 0.0f;
	bool right = player.GetRight();

	if (ON_PRESS('W')) ver -= 1.0f;
	if (ON_PRESS('A')) { hor -= 1.0f; right = false; }
	if (ON_PRESS('S')) ver += 1.0f;
	if (ON_PRESS('D')) { hor += 1.0f; right = true; }

	bool fire = false;
	MyVector2 bulletVec = { 0.0f, 0.0f };

	if (ON_PRESS(VK_UP)) { fire = true; bulletVec.yPos = -1.0f; }
	if (ON_PRESS(VK_LEFT)) { right = false; fire = true; bulletVec.xPos = -1.0f; }
	if (ON_PRESS(VK_DOWN)) { fire = true; bulletVec.yPos = 1.0f; }
	if (ON_PRESS(VK_RIGHT)) { right = true; fire = true; bulletVec.xPos = +1.0f; }

	if (fire)
	{
		bulletVec.Normalize();
		std::vector<Behavior*> bullets = player.Fire(bulletVec);

		int a = 0;

		if (bullets.size() > 0)
			objList.insert(objList.end(), bullets.begin(), bullets.end());
	}

	player.SetRight(right);

	player.direction.Normalize();
	player.direction.SetDirection(hor, ver);
}
