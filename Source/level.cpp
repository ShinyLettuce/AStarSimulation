#include "level.h"

void Level::update()
{

}

int Level::distanceBetween(Vector2 pos1, Vector2 pos2)
{
	int distanceX = abs(static_cast<int>(pos1.x - pos2.x));
	int distanceY = abs(static_cast<int>(pos1.y - pos2.y));
	int remaining = abs(distanceX - distanceY);

	return std::min(distanceX, distanceY) * diagonalCost + remaining * straightCost;
}

std::vector<Vector2> Level::getNeighborVector(Vector2 currentPosition) //change to store positions instead. This simply copies data and not instances
{
	std::vector<Vector2> neighborVector = {};
	if (currentPosition.x - 1 >= 0)
	{
		//left
		neighborVector.push_back({ currentPosition.x - 1, currentPosition.y });
		if (currentPosition.y - 1 >= 0)
		{
			//left up
			neighborVector.push_back({ currentPosition.x - 1, currentPosition.y - 1 });
		}
		if (currentPosition.y + 1 <= gridSide)
		{
			//left down
			neighborVector.push_back({ currentPosition.x - 1, currentPosition.y + 1 });
		}
	}
	if (currentPosition.x + 1 <= gridSide)
	{
		//right
		neighborVector.push_back({ currentPosition.x + 1, currentPosition.y });
		if (currentPosition.y - 1 >= 0)
		{
			//right up
			neighborVector.push_back({ currentPosition.x + 1, currentPosition.y - 1 });
		}
		if (currentPosition.y + 1 <= gridSide)
		{
			//right down
			neighborVector.push_back({ currentPosition.x + 1, currentPosition.y + 1 });
		}
	}
	if (currentPosition.y + 1 <= gridSide)
	{
		//down
		neighborVector.push_back({ currentPosition.x, currentPosition.y + 1 });
	}
	if (currentPosition.y - 1 >= 0)
	{
		//up
		neighborVector.push_back({ currentPosition.x, currentPosition.y - 1 });
	}

	return neighborVector;
}

std::vector<Node> Level::findPath(Vector2 startPosition, Vector2 goalPosition)
{
	// Code logic inspired by CodeMonkey's Unity scripts of the A* algorithm
	// provided by the course responsible

	Node startNode;
	Node goalNode;
	startNode.position = startPosition;
	goalNode.position = goalPosition;


	std::vector<Node> openList = { startNode };
	std::vector<Node> closedList = {};

	for (int i = 0; i < gridSide; i++)
	{
		for (int j = 0, gridIndex = j + i * gridSide; j < gridSide; j++) // IF SOMETHING FUCKS UP, CHECK THIS
		{
			grid[gridIndex].gCost = INT16_MAX;
			grid[gridIndex].fCost = grid[gridIndex].gCost + grid[gridIndex].hCost;
			grid[gridIndex].cameFrom = nullptr;
		}
	}

	startNode.gCost = 0;
	startNode.hCost = distanceBetween(startPosition, goalPosition);
	startNode.fCost = startNode.gCost + startNode.hCost;

	//Add first visual here

	while (openList.size() > 0)
	{
		// make into function
		int lowestFCost = INT16_MAX;
		int lowFIndex = 0;
		for (int i = 0; i < gridSide; i++)
		{
			for (int j = 0, gridIndex = j + i * gridSide; j < gridSide; j++) // IF SOMETHING FUCKS UP, CHECK THIS
			{
				if (grid[gridIndex].fCost < lowestFCost)
				{
					lowestFCost = grid[gridIndex].fCost;
					lowFIndex = gridIndex;
				}
			}
		}
		Node currentNode = grid[lowFIndex];

		if (currentNode == goalNode)
		{
			//YAY WE DID IT
			//calcualtePath logic here
		}

		openList.erase(
				std::remove_if(
					openList.begin(),
					openList.end(),
					[&currentNode](Node n) {return n == currentNode; }),
				openList.end());

		closedList.push_back(currentNode);

		//go through neighboring nodes
		for (Vector2 n : getNeighborVector(currentNode.position))
		{

		}
	}

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