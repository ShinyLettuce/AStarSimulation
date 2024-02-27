#include "simManager.h"

float SimManager::random_float01()
{
	return rand() / static_cast<float>(RAND_MAX);
}

float SimManager::random_float_in_range(float min, float max)
{
	return random_float01() * (max - min) + min;
}

Vector2 SimManager::mouseTileCollision()
{
	for (int i = 0; i < level.gridSide; i++)
	{
		for (int j = 0; j < level.gridSide; j++)
		{
			if (GetMousePosition().x >= level.gridPosition.x + j * level.tilePixelSide &&
				GetMousePosition().x <= level.gridPosition.x + (j + 1) * level.tilePixelSide &&
				GetMousePosition().y >= level.gridPosition.y + i * level.tilePixelSide &&
				GetMousePosition().y <= level.gridPosition.y + (i + 1) * level.tilePixelSide)
			{
				return { (float)j, (float)i };
			}
		}
	}
	throw;
}

void SimManager::update()
{
	if (currentState == SimState::EDIT)
	{
		bool hit = false;
		Vector2 hitPosition = { 0,0 };

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) &&
			GetMousePosition().x < level.gridPosition.x + level.gridSide * level.tilePixelSide &&
			GetMousePosition().x > level.gridPosition.x &&
			GetMousePosition().y > level.gridPosition.y &&
			GetMousePosition().y < level.gridPosition.y + level.gridSide * level.tilePixelSide)
		{
			hit = true;
			hitPosition = mouseTileCollision();
		}

		switch (editState)
		{
		case EditState::BLOCK:
			if (hit)
			{
				level.grid[(int)hitPosition.x + (int)hitPosition.y * (int)level.gridSide] = (level.grid[(int)hitPosition.x + (int)hitPosition.y * (int)level.gridSide] + 1) % 2;
			}
			break;
		case EditState::STARCHASER:
			break;
		case EditState::STAR:
			break;
		case EditState::SHIP:
			break;
		case EditState::TRADING:
			break;
		}
	}
}

void SimManager::render()
{
	level.render();
	spaceShip.render(level.gridPosition, level.tilePixelSide);
	tradingPost.render(level.gridPosition, level.tilePixelSide);
	fallenStar.render(level.gridPosition, level.tilePixelSide);
	bountyHunterRoy.render(level.gridPosition, level.tilePixelSide);
	//show graphically which states that are toggled
}