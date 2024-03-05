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

void SimManager::initNewPath(Vector2 goal)
{
	aStarPath = level.findPath(level.grid[static_cast<int>(bountyHunterRoy.pos.x + bountyHunterRoy.pos.y * level.gridSide)],
							   level.grid[static_cast<int>(goal.x + goal.y * level.gridSide)]);
	pathCalculated = true;
	bountyHunterRoy.pathTraversalIndex = 1;

	if (aStarPath.size() == 0)
	{
		victory = false;
		currentState = SimState::FINISHED;
	}
}

void SimManager::starChaserMove(Vector2 goal, StarChaser::ChaserState newState)
{
	bountyHunterRoy.timer++;

	if (bountyHunterRoy.timer != 31)
	{
		return;
	}

	if (bountyHunterRoy.holdingStar && aStarPath.size() > 1)
	{
		bountyHunterRoy.currentStamina -= level.distanceBetween(bountyHunterRoy.pos, aStarPath[bountyHunterRoy.pathTraversalIndex].position);

	}
	if (bountyHunterRoy.currentStamina <= 0 && bountyHunterRoy.holdingStar)
	{
		bountyHunterRoy.currentState = StarChaser::ChaserState::SHIP;
		bountyHunterRoy.holdingStar = false;
		pathCalculated = false;
		bountyHunterRoy.timer = 0;
		return;
	}

	if (aStarPath.size() > 1)
	{
		bountyHunterRoy.pos = aStarPath[bountyHunterRoy.pathTraversalIndex].position;
	}
	if (bountyHunterRoy.holdingStar)
	{
		fallenStar.pos = bountyHunterRoy.pos;
	}

	if (bountyHunterRoy.pos.x == goal.x && bountyHunterRoy.pos.y == goal.y)
	{
		if (bountyHunterRoy.currentState == StarChaser::ChaserState::TRADING)
		{
			bountyHunterRoy.holdingStar = false;
			bountyHunterRoy.starSold = true;
		}
		if (bountyHunterRoy.currentState == StarChaser::ChaserState::STAR)
		{
			bountyHunterRoy.holdingStar = true;
		}
		if (bountyHunterRoy.currentState == StarChaser::ChaserState::SHIP)
		{
			bountyHunterRoy.currentStamina = bountyHunterRoy.maxStamina;
		}

		bountyHunterRoy.currentState = newState;
		pathCalculated = false;
	}
	else
	{
		bountyHunterRoy.pathTraversalIndex++;
	}

	bountyHunterRoy.timer = 0;
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
			victory = true;
			pathCalculated = false;
			bountyHunterRoy.starSold = false;
			bountyHunterRoy.currentStamina = bountyHunterRoy.maxStamina;
			bountyHunterRoy.currentState = StarChaser::ChaserState::STAR;
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

		if (hit)
		{
			switch (editState)
			{
			case EditState::BLOCK:
				level.grid[(int)hitPosition.x + (int)hitPosition.y * (int)level.gridSide].isBlocked = !level.grid[(int)hitPosition.x + (int)hitPosition.y * (int)level.gridSide].isBlocked;
				break;

			case EditState::STARCHASER:
				bountyHunterRoy.pos = hitPosition;
				break;

			case EditState::STAR:
				fallenStar.pos = hitPosition;
				break;

			case EditState::SHIP:
				spaceShip.pos = hitPosition;
				break;

			case EditState::TRADING:
				tradingPost.pos = hitPosition;
				break;
			}
		}
	}
	if (currentState == SimState::RUNNING)
	{
		switch (bountyHunterRoy.currentState)
		{
		case StarChaser::ChaserState::STAR:
			if (!pathCalculated)
			{
				initNewPath(fallenStar.pos);
			}
			else
			{
				starChaserMove(fallenStar.pos, StarChaser::ChaserState::TRADING);
			}
			break;

		case StarChaser::ChaserState::TRADING:
			if (!pathCalculated)
			{
				initNewPath(tradingPost.pos);
			}
			else
			{
				starChaserMove(tradingPost.pos, StarChaser::ChaserState::SHIP);
			}
			break;

		case StarChaser::ChaserState::SHIP:
			if (!pathCalculated)
			{
				initNewPath(spaceShip.pos);
			}
			else
			{
				if (bountyHunterRoy.starSold)
				{
					starChaserMove(spaceShip.pos, StarChaser::ChaserState::FINISHED);
				}
				else
				{
					starChaserMove(spaceShip.pos, StarChaser::ChaserState::STAR);
				}
			}
			break;

		case StarChaser::ChaserState::FINISHED:
			currentState = SimState::FINISHED;
			break;
		}

	}
	if (currentState == SimState::FINISHED)
	{
		if (IsKeyPressed(KEY_R))
		{
			currentState = SimState::EDIT;
		}
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
	if (currentState == SimState::RUNNING)
	{
		for (Node& n : aStarPath)
		{
			DrawRectangleV
			(
				{ level.gridPosition.x + n.position.x * level.tilePixelSide, level.gridPosition.y + n.position.y * level.tilePixelSide },
				{ level.tilePixelSide, level.tilePixelSide },
				GREEN
			);
		}
	}
	if (currentState == SimState::FINISHED && victory)
	{
		DrawText("- Bounty hunter Roy prevails! -", 122, 80, 36, WHITE);
		DrawText("Press R to return", 245, 700, 36, WHITE);
	}
	else if (currentState == SimState::FINISHED && !victory)
	{
		DrawText("- Bounty hunter Roy could not feed -", 60, 40, 36, WHITE);
		DrawText("- his family! -", 290, 80, 36, WHITE);
		DrawText("Press R to return", 245, 700, 36, WHITE);
	}
	level.render();
	spaceShip.render(level.gridPosition, level.tilePixelSide);
	fallenStar.render(level.gridPosition, level.tilePixelSide);
	tradingPost.render(level.gridPosition, level.tilePixelSide);
	bountyHunterRoy.render(level.gridPosition, level.tilePixelSide);
}