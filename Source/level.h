#pragma once
#include "raylib.h"
#include <cmath>
#include <vector>

class Node {
public:
	Vector2 position = { 0,0 };

	int hCost = 0;
	int gCost = 0;
	int fCost = 0;

	bool isBlocked = false;

	Node* cameFrom = nullptr;

	bool operator==(const Node& other) const {
		return position.x == other.position.x && position.y == other.position.y;
	}
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
				//randomize block positions here?
			}
		}
	}

	std::vector<Vector2> getNeighborVector(Vector2 currentPosition);
	int distanceBetween(Vector2 pos1, Vector2 pos2);
	std::vector<Node> findPath(Vector2 startPosition, Vector2 goalPosition);

	void update();
	void render();
};