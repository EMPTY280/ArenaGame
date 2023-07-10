#include "Spawner.h"
#include "GameWorld.h"

Spawner::Spawner(MyVector2 pos, Behavior* enemy) : Behavior(pos, ObjType::SPAWNER), enemy(enemy)
{
}

Spawner::~Spawner()
{
}

void Spawner::Start()
{
}

void Spawner::Update(float delatTime)
{
	spawnDelay += delatTime;

	if (spawnDelay >= spawnDelayMax)
		KillSelf();
}

void Spawner::OnCollision(Behavior& collider, float deltaTime)
{
}

void Spawner::Render(Graphics* backGraphics)
{
	float ratio = spawnDelay / spawnDelayMax;

	Pen pen(Color(150 + 105 * ratio, 255, 87, 87));
	Pen pen2(Color(150 * ratio, 255, 87, 87));

	SolidBrush brush(Color(150, 255, 87, 87));
	SolidBrush brush2(Color(150 + 105 * ratio, 255, 255 - 13 * ratio, 255 * (1.0f - ratio)));

	float edgeSize = radius * (1 + ratio * 0.5f);
	int edgeX = position.xPos - edgeSize;
	int edgeY = position.yPos - edgeSize;
	int edgeDiameter = edgeSize * 2;

	float edge2Size = radius * (2.0f - ratio * 0.5f);
	int edge2X = position.xPos - edge2Size;
	int edge2Y = position.yPos - edge2Size;
	int edge2Diameter = edge2Size * 2;

	float fillSize = radius * (ratio * 1.5f);
	int fillX = position.xPos - fillSize;
	int fillY = position.yPos - fillSize;
	int fillDiameter = fillSize * 2;

	backGraphics->DrawEllipse(&pen, edgeX, edgeY, edgeDiameter, edgeDiameter);
	backGraphics->DrawEllipse(&pen2, edge2X, edge2Y, edge2Diameter, edge2Diameter);
	backGraphics->FillEllipse(&brush, fillX, fillY, fillDiameter, fillDiameter);

	float exclamationSIze = (1 + ratio * 0.5f);
	if (spawnDelay >= spawnDelayMax * 0.75f)
		exclamationSIze = ((1.0f + 0.2f * ((int)(spawnDelay * 100) % 2)) + ratio * 0.5f);

	int xx = position.xPos - 3.5f * exclamationSIze;
	int yy = position.yPos - 12 * exclamationSIze;
	int w = 7 * exclamationSIze;
	int h = 16 * exclamationSIze;
	int doty = position.yPos + 6 * exclamationSIze;
	int doth = 7 * exclamationSIze;

	backGraphics->FillRectangle(&brush2, xx, yy, w, h);
	backGraphics->FillRectangle(&brush2, xx, doty, w, doth);
}

void Spawner::OnKill(GameWorld* world)
{
	dynamic_cast<Enemy*>(enemy)->SetHitCount();
	world->AddSpawnBuffer(enemy);
}
