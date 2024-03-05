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

std::vector<Node*> Level::getNeighborVector(Vector2 currentPosition)
{
	std::vector<Node*> neighborVector = {};
	if (currentPosition.x - 1 >= 0)
	{
		//left
		neighborVector.push_back(&grid[(int)(currentPosition.x - 1 + (currentPosition.y) * gridSide)]);
		if (currentPosition.y - 1 >= 0)
		{
			//left up
			neighborVector.push_back(&grid[(int)(currentPosition.x - 1 + (currentPosition.y - 1) * gridSide)]);
		}
		if (currentPosition.y + 1 < gridSide)
		{
			//left down
			neighborVector.push_back(&grid[(int)(currentPosition.x - 1 + (currentPosition.y + 1) * gridSide)]);
		}
	}
	if (currentPosition.x + 1 < gridSide)
	{
		//right
		neighborVector.push_back(&grid[(int)(currentPosition.x + 1 + (currentPosition.y) * gridSide)]);
		if (currentPosition.y - 1 >= 0)
		{
			//right up
			neighborVector.push_back(&grid[(int)(currentPosition.x + 1 + (currentPosition.y - 1) * gridSide)]);
		}
		if (currentPosition.y + 1 < gridSide)
		{
			//right down
			neighborVector.push_back(&grid[(int)(currentPosition.x + 1 + (currentPosition.y + 1) * gridSide)]);
		}
	}
	if (currentPosition.y + 1 < gridSide)
	{
		//down
		neighborVector.push_back(&grid[(int)(currentPosition.x + (currentPosition.y + 1) * gridSide)]);
	}
	if (currentPosition.y - 1 >= 0)
	{
		//up
		neighborVector.push_back(&grid[(int)(currentPosition.x + (currentPosition.y - 1) * gridSide)]);
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

std::vector<Node> Level::findPath(Node& startNode, Node& goalNode)
{
	// Code logic inspired by and translated from CodeMonkey's C# Unity scripts of the A* algorithm
	// provided as study material

	std::vector<Node*> openList = { &startNode };
	std::vector<Node*> closedList = {};

	for (int i = 0; i < gridSide; i++)
	{
		for (int j = 0, gridIndex = 0; j < gridSide; j++)
		{
			gridIndex = j + i * (int)gridSide;
			grid[gridIndex].gCost = INT16_MAX;
			grid[gridIndex].fCost = grid[gridIndex].gCost + grid[gridIndex].hCost;
			grid[gridIndex].cameFrom = nullptr;
		}
	}

	startNode.gCost = 0;
	startNode.hCost = distanceBetween(startNode.position, goalNode.position);
	startNode.fCost = startNode.gCost + startNode.hCost;


	//Add first visual here

	while (openList.size() > 0)
	{
		// make into function
		int lowestFCost = INT16_MAX;
		int lowFIndex = 0;
		for (int i = 0; i < openList.size(); i++)
		{
			if (openList[i]->fCost < lowestFCost)
			{
				lowestFCost = openList[i]->fCost;
				lowFIndex = i;
			}
		}
		Node* currentNode = openList[lowFIndex];

		if (currentNode == &goalNode)
		{
			return buildPath(goalNode);
		}

		openList.erase(
				std::remove_if(
					openList.begin(),
					openList.end(),
					[&currentNode](Node* n) {return n == currentNode; }),
				openList.end());

		closedList.push_back(currentNode);

		//go through neighboring nodes
		for (Node* v : getNeighborVector(currentNode->position)) //TODO: v is bad naming, change to neighbor
		{
			//Node neighbor = grid[static_cast<int>(v.x + v.y * gridSide)]; WAIT FOR NOW, COULD CAUSE COPY ISSUE

			bool isInClosed = std::any_of(closedList.begin(), closedList.end(), //ChatGPT used to help formulate lambda syntax
				[&v](Node* n) { 
					return n == v;
				});

			if (isInClosed)
			{
				continue;
			}

			if (v->isBlocked)
			{
				closedList.push_back(v);
				continue;
			}

			int prelimGCost = currentNode->gCost + distanceBetween(currentNode->position, v->position);
			if (prelimGCost < v->gCost)
			{
				v->cameFrom = currentNode;
				v->gCost = prelimGCost;
				v->hCost = distanceBetween(v->position, goalNode.position);
				v->fCost = v->gCost + v->hCost;

				bool isInOpen = std::any_of(openList.begin(), openList.end(), //ChatGPT used to help formulate lambda syntax
					[&v](Node* n) {
						return n == v;
					});
				if (!isInOpen)
				{
					openList.push_back(v);
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