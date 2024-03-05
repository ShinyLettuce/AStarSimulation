#include "entity.h"

void StarChaser::render(Vector2 gridPos, float tileSide)
{
	DrawCircleV({ gridPos.x + pos.x * tileSide + 0.5f * tileSide, gridPos.y + pos.y * tileSide + 0.5f * tileSide }, 20, color);
}
	 
void FallenStar::render(Vector2 gridPos, float tileSide)
{
	DrawCircleV({ gridPos.x + pos.x * tileSide + 0.5f * tileSide, gridPos.y + pos.y * tileSide + 0.5f * tileSide }, 20, color);
}

void SpaceShip::render(Vector2 gridPos, float tileSide)
{
	DrawCircleV({ gridPos.x + pos.x * tileSide + 0.5f * tileSide, gridPos.y + pos.y * tileSide + 0.5f * tileSide }, 20, color);
}

void TradingPost::render(Vector2 gridPos, float tileSide)
{
	DrawCircleV({ gridPos.x + pos.x * tileSide + 0.5f * tileSide, gridPos.y + pos.y * tileSide + 0.5f * tileSide }, 20, color);
}