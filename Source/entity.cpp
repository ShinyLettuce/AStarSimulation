#include "entity.h"

void StarChaser::update()
{

}

void StarChaser::render(Vector2 gridPos, float tileSide)
{
	DrawCircleV({ gridPos.x + pos.x * tileSide + 0.5f * tileSide, gridPos.y + pos.y * tileSide + 0.5f * tileSide }, 20, color);
}

void FallenStar::update()
{	 
	 
}	 
	 
void FallenStar::render(Vector2 gridPos, float tileSide)
{
	DrawCircleV({ gridPos.x + pos.x * tileSide + 0.5f * tileSide, gridPos.y + pos.y * tileSide + 0.5f * tileSide }, 20, color);
}

void SpaceShip::update()
{

}

void SpaceShip::render(Vector2 gridPos, float tileSide)
{
	DrawCircleV({ gridPos.x + pos.x * tileSide + 0.5f * tileSide, gridPos.y + pos.y * tileSide + 0.5f * tileSide }, 20, color);
}

void TradingPost::update()
{

}

void TradingPost::render(Vector2 gridPos, float tileSide)
{
	DrawCircleV({ gridPos.x + pos.x * tileSide + 0.5f * tileSide, gridPos.y + pos.y * tileSide + 0.5f * tileSide }, 20, color);
}