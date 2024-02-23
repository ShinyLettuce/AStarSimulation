#pragma once
#include "raylib.h"

class Level {
public:

	int grid[64] = { 0,0,0,0,0,0,0,0,
					 0,0,0,1,0,0,1,0,
					 0,0,0,0,0,0,0,0, 
					 0,0,0,0,0,0,0,0,
					 0,0,0,1,0,0,1,0,
					 0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,0,
					 0,0,0,0,0,0,0,0 };

	Vector2 gridPosition = { 148,148 };
	int gridSide = 8;
	int tilePixelSide = 64;

	void update();
	void render();
};