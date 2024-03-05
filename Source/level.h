#pragma once
#include "raylib.h"
#include "utils.h"
#include <cmath>
#include <algorithm>
#include <vector>

class Node {
public:
	Vector2 position = { 0,0 };

	int hCost = 0;
	int gCost = 0;
	int fCost = 0;

	bool isBlocked = false;

	Node* cameFrom = nullptr;
};

class Level {
public:
	int straightCost = 10;
	int diagonalCost = 14;

	Node grid[64];

	Vector2 gridPosition = { 148,148 };
	float gridSide = 8;
	float tilePixelSide = 64;

	Level() {
		for (float i = 0; i < gridSide; i++)
		{
			for (float j = 0; j < gridSide; j++)
			{
				grid[static_cast<int>(j + i * gridSide)].position = { j,i };
			}
		}
	}

	std::vector<Node*> getNeighborVector(Vector2 currentPosition);
	int distanceBetween(Vector2 pos1, Vector2 pos2);
	std::vector<Node> buildPath(Node endNode);
	std::vector<Node> findPath(Node& startNode, Node& goalNode);

	void render();
};