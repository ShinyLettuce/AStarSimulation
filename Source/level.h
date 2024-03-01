#pragma once
#include "raylib.h"

class Node {
public:
	Vector2 position = { 0,0 };

	int hCost = 0;
	int gCost = 0;
	int fCost = 0;

	bool isBlocked = false;
};

class Level {
public:

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

	void update();
	void render();
};