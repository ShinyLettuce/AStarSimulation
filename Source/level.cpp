#include "level.h"

void Level::update()
{

}

void Level::render()
{
	for (int i = 0; i < gridSide + 1; i++)
	{
		DrawLine
		(
			(int)gridPosition.x + i * tilePixelSide,
			(int)gridPosition.y,
			(int)gridPosition.x + i * tilePixelSide,
			(int)gridPosition.y + tilePixelSide * gridSide,
			WHITE
		);
	}
	for (int j = 0; j < gridSide + 1; j++)
	{
		DrawLine
		(
			(int)gridPosition.x,
			(int)gridPosition.y + j * tilePixelSide,
			(int)gridPosition.x + tilePixelSide * gridSide,
			(int)gridPosition.y + j * tilePixelSide,
			WHITE
		);
	}
}