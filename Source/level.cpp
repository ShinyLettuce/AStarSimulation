#include "level.h"

void Level::update()
{

}

std::vector<Node> Level::findPath(Vector2 startPosition, Vector2 goalPosition)
{
	//A* logic here?
}


void Level::render()
{
	for (float i = 0; i < gridSide + 1; i++)
	{
		DrawLineV
		(
			{ gridPosition.x + i * tilePixelSide, gridPosition.y },
			{ gridPosition.x + i * tilePixelSide, gridPosition.y + tilePixelSide * gridSide },
			WHITE
		);
	}
	for (float i = 0; i < gridSide + 1; i++)
	{
		DrawLineV
		(
			{ gridPosition.x, gridPosition.y + i * tilePixelSide },
			{ gridPosition.x + tilePixelSide * gridSide, gridPosition.y + i * tilePixelSide },
			WHITE
		);
	}

	for (float i = 0; i < gridSide; i++)
	{
		for (float j = 0; j < gridSide; j++)
		{
			if (grid[(int)(j + i * gridSide)].isBlocked)
			{
				DrawRectangleV
				(
					{ gridPosition.x + j * tilePixelSide, gridPosition.y + i * tilePixelSide },
					{ tilePixelSide, tilePixelSide },
					WHITE
				);
			}
		}
	}
}