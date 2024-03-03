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

std::vector<Node> Level::buildPath(Node goalNode)
{
	std::vector<Node> finalPath = {};
	finalPath.push_back(goalNode);
	Node currentNode = goalNode;
	while (currentNode.cameFrom != nullptr)
	{
		finalPath.insert(finalPath.begin(), *currentNode.cameFrom);
		currentNode = *currentNode.cameFrom;
	}
	return finalPath;
}

std::vector<Node> Level::findPath(Vector2 startPosition, Vector2 goalPosition)
{
	// Code logic inspired by and translated from CodeMonkey's C# Unity scripts of the A* algorithm
	// provided as study material

	Node startNode;
	Node goalNode;
	startNode.position = startPosition;
	goalNode.position = goalPosition;


	std::vector<Node> openList = { startNode };
	std::vector<Node> closedList = {};

	for (int i = 0; i < gridSide; i++)
	{
		for (int j = 0, gridIndex = j + i * (int)gridSide; j < gridSide; j++) // IF SOMETHING FUCKS UP, CHECK THIS
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
			for (int j = 0, gridIndex = j + i * (int)gridSide; j < gridSide; j++) // IF SOMETHING FUCKS UP, CHECK THIS
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
			return buildPath(goalNode);
		}

		openList.erase(
				std::remove_if(
					openList.begin(),
					openList.end(),
					[&currentNode](Node n) {return n == currentNode; }),
				openList.end());

		closedList.push_back(currentNode);

		//go through neighboring nodes
		for (Vector2 v : getNeighborVector(currentNode.position)) //TODO: v is bad naming, change to neighbor
		{
			//Node neighbor = grid[static_cast<int>(v.x + v.y * gridSide)]; WAIT FOR NOW, COULD CAUSE COPY ISSUE

			bool isInClosed = std::any_of(closedList.begin(), closedList.end(), //ChatGPT used to help formulate lambda syntax
				[&v](Node& n) { 
					return n.position.x == v.x && n.position.y == v.y;
				});

			if (isInClosed)
			{
				continue;
			}

			if (grid[static_cast<int>(v.x + v.y * gridSide)].isBlocked)
			{
				closedList.push_back(grid[static_cast<int>(v.x + v.y * gridSide)]);
				continue;
			}

			int prelimGCost = currentNode.gCost + distanceBetween(currentNode.position, v);
			if (prelimGCost < grid[static_cast<int>(v.x + v.y * gridSide)].gCost)
			{
				grid[static_cast<int>(v.x + v.y * gridSide)].cameFrom = &currentNode;
				grid[static_cast<int>(v.x + v.y * gridSide)].gCost = prelimGCost;
				grid[static_cast<int>(v.x + v.y * gridSide)].hCost = distanceBetween(v, goalPosition);
				grid[static_cast<int>(v.x + v.y * gridSide)].fCost = grid[static_cast<int>(v.x + v.y * gridSide)].gCost + grid[static_cast<int>(v.x + v.y * gridSide)].hCost;

				bool isInOpen = std::any_of(openList.begin(), openList.end(), //ChatGPT used to help formulate lambda syntax
					[&v](Node& n) {
						return n.position.x == v.x && n.position.y == v.y;
					});
				if (!isInOpen)
				{
					openList.push_back(grid[static_cast<int>(v.x + v.y * gridSide)]);
				}
			}
		}
	}
	return {}; //NOTHING, NO MORE NODES IN OPEN LIST
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