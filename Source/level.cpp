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
	for (int i = 0; i < gridSide + 1; i++)
	{
		DrawLine
		(
			(int)gridPosition.x,
			(int)gridPosition.y + i * tilePixelSide,
			(int)gridPosition.x + tilePixelSide * gridSide,
			(int)gridPosition.y + i * tilePixelSide,
			WHITE
		);
	}

	for (int i = 0; i < gridSide; i++)
	{
		for (int j = 0; j < gridSide; j++)
		{
			if (grid[j + i * gridSide] == 1)
			{
				DrawRectangle((int)gridPosition.x + j * tilePixelSide, (int)gridPosition.y + i * tilePixelSide, tilePixelSide,tilePixelSide,WHITE);
			}
		}
	}
}