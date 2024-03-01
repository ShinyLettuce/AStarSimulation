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
		if (IsKeyPressed(KEY_ONE))
		{
			editState = EditState::BLOCK;
		}
		if (IsKeyPressed(KEY_TWO))
		{
			editState = EditState::STARCHASER;
		}
		if (IsKeyPressed(KEY_THREE))
		{
			editState = EditState::STAR;
		}
		if (IsKeyPressed(KEY_FOUR))
		{
			editState = EditState::TRADING;
		}
		if (IsKeyPressed(KEY_FIVE))
		{
			editState = EditState::SHIP;
		}
		if (IsKeyPressed(KEY_SPACE))
		{
			currentState = SimState::RUNNING;
		}

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
				level.grid[(int)hitPosition.x + (int)hitPosition.y * (int)level.gridSide].isBlocked = !level.grid[(int)hitPosition.x + (int)hitPosition.y * (int)level.gridSide].isBlocked;
			}
			break;
		case EditState::STARCHASER:
			if (hit)
			{
				bountyHunterRoy.pos = hitPosition;
			}
			break;
		case EditState::STAR:
			if (hit)
			{
				fallenStar.pos = hitPosition;
			}
			break;
		case EditState::SHIP:
			if (hit)
			{
				spaceShip.pos = hitPosition;
			}
			break;
		case EditState::TRADING:
			if (hit)
			{
				tradingPost.pos = hitPosition;
			}
			break;
		}
	}
	if (currentState == SimState::RUNNING)
	{

	}
}

void SimManager::render()
{
	if (currentState == SimState::EDIT)
	{
		DrawText("-Press space to start-", 200, 80, 36, WHITE);
		DrawText("1. Block", 20, 700, 32, WHITE);
		DrawText("2. Star Chaser", 20, 732, 32, bountyHunterRoy.color);
		DrawText("3. Fallen Star", 280, 700, 32, fallenStar.color);
		DrawText("4. Trading Post", 280, 732, 32, tradingPost.color);
		DrawText("5. Space Ship", 560, 700, 32, spaceShip.color);
	}

	level.render();
	spaceShip.render(level.gridPosition, level.tilePixelSide);
	tradingPost.render(level.gridPosition, level.tilePixelSide);
	fallenStar.render(level.gridPosition, level.tilePixelSide);
	bountyHunterRoy.render(level.gridPosition, level.tilePixelSide);
	//show graphically which states that are toggled
}